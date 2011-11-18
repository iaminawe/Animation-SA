<?php
/**
* This file contains a function library for both the backup module and
*	the backup script.
*
*/


/**
* This function backs up our database.
*
* @param string $db_file This is set to the name of the file which holds
*	the database.
*
* @param string $prefix_dir The directory name to prefix to the backup.
* 
* @return mixed NULL is returned on success.  Otherwise an error is returned.
*/
function backup_database(&$db_file, $prefix_dir = "") {

	//
	// Parse our database URL into credentials and remove the leading
	// slash from the path as well.
	//
	$db_data = parse_url($GLOBALS["db_url"]);
	$db_data["path"][0] = " ";

	//
	// Create our database temp file
	//
	$db_file_tmp = tempnam("/tmp", "drupal-backup-db-");

	//
	// Create our date string for filenames
	//
	$date_string = date("YmdHis");

	//
	// The name of our final db file.
	// This includes a random number to keep attackers from guessing 
	// the filename.
	//
	$db_file = "drupal-backup-db-" . $date_string 
		. "-" . mt_rand(0, 999999999) . ".sql.gz";

	if (empty($db_file_tmp)) {
		$error = "Call to tempnam() failed";
		return($error);
	}

	//
	// Now dump our database to the temp file
	//
	$cmd = "mysqldump -u " . $db_data["user"]
		. " -h "  . $db_data["host"]
		. " -p"  . $db_data["pass"]
		. " "  . $db_data["path"]
		//. " |gzip.TEST.debug >$db_file_tmp "
		. " |gzip >$db_file_tmp "
		;

	//$cmd = "exit 3"; // Debugging exit values

	$fp = popen($cmd, "r");

	if (empty($fp)) {
		$error = "Unable to run command '$cmd'";
		return($error);
	}

	$retval = pclose($fp);

	if ($retval != 0) {
		$error = "Command '$cmd' returned value: $retval";
		return($error);
	}

	//
	// Move the temp file into the current directory (with a new name)
	// so that it can be included in the tarball.
	//
	if (!rename($db_file_tmp, $db_file)) {
		$error = "Renaming file '$db_file_tmp' to '$db_file' failed";
		return($error);
	}

	// Assume success
	return(null);

} // End of backup_database() 


/**
* This function gets a list of files to back up.  Any files that are 
*	already backups are excluded.
*
* @param array $files This is set to a list of filenames to be backed up.
*
* @param string $prefix_dir The directory the backup will be going in
*
* @return mixed NULL is returned on success.  Otherwise an error is returned.
*/
function backup_get_files(&$file_list, $prefix_dir) {

	//
	// Get a list of all files in the current directory, filter out the 
	// current and parent directories, and any existing backup files.
	// Trying to make GNU tar's --exclude switch actually work for me
	// was like trying to herd housecats that were hopped up on crack.
	// It just wasn't going to happen. :-)  Plus, this approach is
	// more portable.
	//
	$file_list = "";

	$fp = opendir(".");

	if (empty($fp)) {
		$error = "Unable to open directory: '$dir'";
		return($error);
	}

	//
	// If we are making the backup from the parent directory get the name
	// of the current directory and prepend it onto the filenames.
	//
	$parent_dir = "";

	$from_parent = variable_get("backup_from_parent", "");
	if (!empty($from_parent)) {
		$parent_dir = backup_get_dirname() ."/";
	}

	while ($file = readdir($fp)) {
		//
		// Skip the current and parent directory
		//
		if ($file == "." || $file == "..") {
			continue;
		}

		//
		// If we have a prefix directory, skip the entire thing.
		// There is logic in backup_form_validate() to keep from designating
		// a directory holding valid data as a backup directory
		//
		if ($file == $prefix_dir) {
			continue;
		}

		//
		// Skip any backup files
		//
		if (backup_is_backup($file)) {
			continue;
		}

		$file_list .= $parent_dir . $file . " ";

	}

	if (!$fp) {
		$error = "Unable to open current directory";
		return($error);
	}

	closedir($fp);

	// Assume success
	return(null);

} // End of backup_get_files()


/**
* This function backs up our file system under DOCUMENT_ROOT, which also
*	includes the database dump.
*
* @param string $db_file The name of our database dump
*
* @param string $backup_file This is set to the name of the main backup
*	file which is created.
*
* @param string $prefix_dir The directory name to prefix to the backup.
* 
* @return mixed NULL is returned on success.  Otherwise an error is returned.
*/
function backup_files($db_file, &$backup_file, $prefix_dir = "") {

	$error = backup_get_files($file_list, $prefix_dir);
	if (!empty($error)) {
		$error = "backup_get_files(): " . $error;
		return($error);
	}

	//
	// If we are mkaing the backup from the parent directory, preprend the
	// current directory name onto the database file.
	//
	$parent_dir = "";
	$from_parent = variable_get("backup_from_parent", "");
	if (!empty($from_parent)) {
		$parent_dir = backup_get_dirname() . "/";
	}

	//
	// Finally, add in our database backup.  It's excluded since it's
	// a backup file just in case there's multiple database dumps lying 
	// around from previous backups that were aborted.  But we want to
	// explicitly add in the dump from *this* run of backup.
	//
	$file_list .= $parent_dir . $db_file;

	//
	// Now tar up the contents of this directory.  
	// Make sure that the temp file is not readable by others.
	//
	$backup_tmp = tempnam("/tmp", "backup-htdocs-");
	if (!chmod($backup_tmp, 0600)) {
		$error = "Unable to chmod() file '$backup_tmp'";
		return($error);
	}

	//
	// This includes a random number to keep attackers from guessing 
	// the filename.
	//
	$date_string = date("YmdHis");
	$backup_file = "drupal-backup-" . $date_string 
		. "-" . mt_rand(0, 999999999) . ".tar.gz";

	//
	// Pre-pend our prefix if it's present.
	//
	if (!empty($prefix_dir)) {
		$backup_file = $prefix_dir . "/" . $backup_file;
	}

	//
	// Create our tar command, and optionally try to capture errors
	//
	$cmd = "tar cfz $backup_tmp $file_list ";

	$capture_errors = variable_get("backup_capture_errors", "");
	if (!empty($capture_errors)) {
		$cmd .= " 2&>1";
	}

	$from_parent = variable_get("backup_from_parent", "");
	if (!empty($from_parent)) {
		$tmp = chdir("..");
		if (empty($tmp)) {
			$error = t("Unable to chdir() to parent directory");
			return($error);
		}
	}

	$fp = popen($cmd, "r");

	if (empty($fp)) {
		$error = "Unable to run command '$cmd'";
		return($error);
	}

	//
	// We might get errors reading older backups, because I had to set their
	// permissions to 000 to keep them from being included in this backup
	// when the directory where the backups are being written is not the same
	// as Drupal's root directory.
	//
	// So, if any returned lines have the names of errors in them, we can just
	// ignore those lines.
	//
	while ($line = fgets($fp)) {
		if (!backup_is_backup($line)) {
			form_set_error("", $line);
		}
	}

	$retval = pclose($fp);

	if ($retval != 0) {
		$error = "Command '$cmd' returned value: $retval";
		return($error);
	}

	if (!empty($from_parent)) {
		$tmp = chdir($parent_dir);
		if (empty($tmp)) {
			$error = t("Unable to chdir() back into directory '$parent_dir'");
			return($error);
		}
	}

	//
	// Now remove the database file, we don't need it anymore.
	//
	if (!unlink($db_file)) {
		$error = "Unable to delete file '$db_file'";
		return($error);
	}

	//
	// Finally, move the tarball into this directory so the user can grab it
	//
	if (!rename($backup_tmp, $backup_file)) {
		$error = "Renaming file '$backup_tmp' to '$backup_file' failed";
		return($error);
	}

	//
	// Make our backup file world-readable.
	//
	if (!chmod($backup_file, 0644)) {
		$error = "chmod() failed";
		return($error);
	}
  
	// Assume success
	return(null);

} // End of backup_files()


/**
* This function gets the name of the current directory, as seen from the parent
*
* @return string The name of the current directory
*/
function backup_get_dirname() {

	$path = getcwd();
	$path = explode("/", $path);

	$retval = $path[(count($path) - 1)];

	return($retval);

} // End of backup_get_dirname()


/**
* Make the determination if a given file is a backup or not.
*
* @param string $file The name of the file. 
*
* @return boolean TRUE if this is a backup file, FALSE otherwise.
*/
function backup_is_backup($file) {

	if (strstr($file, "drupal-backup-")) {
		return(TRUE);
	}

	return(FALSE);

} // End of backup_is_backup()


/**
* This function gets a list of all backups that are in the backup directory.
*
* @param array $files This is set to a  sorted associative array where the 
*	key is the filename and the value is another associative array that has 
*	more details about the file.
*
* @return mixed NULL is returned on success, otherwise a string is returned.
*/
function backup_get_backups(&$files) {

	//
	// Get our target directory, defaulting to the current directory.
	//
	$files = array();
	$dir = variable_get("backup_target", "");

	//$dir .= "BOGUS"; // Debugging
	if (empty($dir)) {
		$dir = ".";
	}

	//
	// Open the directory and read all of the files from it.
	//
	$fp = opendir($dir);

	if (empty($fp)) {
		$error = "Unable to open backup directory: '$dir'";
		$error = "backup_get_backups(): $error";
		return($error);
	}

	//
	// Only pull backup files froom the directory, stat() each file, and 
	// store some of its details in the array which we will return.
	//
	while ($file = readdir($fp)) {
		if (!backup_is_backup($file)) {
			continue;
		}

		$file = $dir . "/" . $file;
		$file_data = stat($file);
		$tmp = array();
		$tmp["size"] = $file_data["size"];
		$tmp["date"] = date("M jS, Y H:i:s", $file_data["mtime"]);
		$tmp["filename"] = $file;

		$files[$file] = $tmp;
	}

	closedir($fp);

	ksort($files);

	// Assume success
	return(null);

} // End of backup_get_backups()

/**
* This function sets the permission for previously written backups to 000.
* 	The reason why this is done is because if a backup is being done in a 
*	directory other than the root that Drupal is installed in, it is difficult
*	to exclude those files.  So instead, the permissions are set to 000 so 
*	that tar cannot read those files, and therefore not include them in
*	the backup.
*
*	No, I cannot use the --exclude flag that tar offers, as this doesn't seem
*	to be present/work right in all versions of tar.  Case in point, it acts
*	oddly on Mac OS/X, which I am developing this module on.
*
* @return mixed NULL is returned on success, otherwise a string is returned.
*/
function backup_permission_null(&$files) {

	foreach ($files as $key => $value) {
		$file = $value["filename"];
		if (!chmod($file, 0000)) {
			$error = "Unable to chmod file '$file'";
			return("backup_permission_null(): " . $error);
		}
	}

	// Assume success
	return(null);

} // End of backup_permission_null()


/**
* Restore the permissions on our backup files.
*
* @return mixed NULL is returned on success, otherwise a string is returned.
*/
function backup_permission_rw(&$files) {

	foreach ($files as $key => $value) {
		$file = $value["filename"];
		if (!chmod($file, 0644)) {
			$error = "Unable to chmod file '$file'";
			return("backup_permission_rw(): " . $error);
		}
	}

	// Assume success
	return(null);

} // End of backup_permission_rw()


/**
* This is the main function which does all of our work.
*
* @return mixed NULL is returned on success, otherwise an error is returned.
* 	This allows us to "catch" errors and let them bubble up the call stack,
*	not unlike exceptions in PHP 5.
*/
function main() {


} // End of main()

/*
if ($error = main()) {
	print $argv[0] . ": Error: $error\n";
	exit (1);
}
*/


?>
