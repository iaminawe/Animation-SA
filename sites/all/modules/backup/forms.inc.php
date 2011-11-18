<?php
/**
* This file is part of the backup module for Drupal.
*
* It contains all form-related functions.
*
* My reason for having this file is because, unlike some other modules I
*	have seen, I am NOT going to create a single monolithic file that's
*	thousands of lines long.
*
*/


/**
* This function creates the "backup this installation" button.
*
* @return array An array for the form element(s).
*/
function backup_form_backup() {

	$form = array();

	//
	// Javascript to process the click on the form, followed by out
	// button to start the backup.
	//
	$javascript = "this.value=\"" 
		. t("Creating the backup.  Please stand by.") . "\"; "
		. "this.disabled=1; ";
	$form["#type"] = "submit";
	$form["#value"] = t("Backup this Drupal installation.");
	//
	// Note that having this handler to disable the form button means that
	// setting a custom #name field will not work.  So the form handling code
	// will, by default, assume that any form submission is a backup
	// unless finds a variable for a different action.
	//
	$form["#attributes"]["onClick"] = $javascript;
	$form["#weight"] = 1;

	return($form);

} // End of backup_form_backup()


/**
* Text that goes under our backup button.
*
* @return array An array for the form element(s).
*/
function backup_form_backup_text() {

	$form = array();

	$form["#type"] = "markup";
	$form["#value"] = "<p>" 
		. t("NOTE: It may take some time for the backup to complete.");
	$form["#weight"] = 2;

	return($form);

} // End of backup_form_backup_text()


/**
* Creates the debugging section of our backup form.
*
* @param string $error This value is passed in by reference.  If set to true,
*	it tellls the parent that there was an error in this section.
*
* @return array An array for the form element(s).
*/
function backup_form_debugging(&$error) {

	$form = array();

	$form["#type"] = "fieldset";
	$form["#title"] = t("Help and Debugging Information");
	$form["#collapsible"] = TRUE;
	$form["#collapsed"] = TRUE;
	//$form["#collapsed"] = FALSE; // Debugging
	$form["#weight"] = -1;
	$form["#description"] = l(t("Click me to run phpinfo()"), 
		"admin/content/backup/phpinfo"
		) . "<p>\n"
		. "Having problems?  Finding bugs?  Seeing red? "
		. l(t("Click here for the backup project webpage"), 
			"http://drupal.org/project/backup")
		;

	$content .= backup_get_path();
	$form["path"]["#type"] = "fieldset";
	$form["path"]["#title"] = t("System Path");
	$form["path"]["#collapsible"] = TRUE;
	$form["path"]["#description"] = $content;

	$programs = backup_get_programs();
	$content = backup_get_programs_html($programs, $error);
	$form["programs"]["#type"] = "fieldset";
	$form["programs"]["#title"] = t("Programs that will be used");
	$form["programs"]["#collapsible"] = TRUE;
	$form["programs"]["#description"] = $content;



	return($form);

} // End of backup_form_debugging()


/**
* Create our configuration dialogue.
*
* @return array An array for the form element(s).
*/
function backup_form_config() {

	$form = array();

	$form["#type"] = "fieldset";
	$form["#title"] = t("Configuration");
	$form["#collapsible"] = TRUE;
	$form["#collapsed"] = FALSE;

	$form["target"]["#type"] = "textfield";
	$form["target"]["#title"] = t("Backup location");
	$form["target"]["#description"] = 
		t("The directory where the backup will be written. ")
		. t("This is relative to Drupal's root directory (%dir). ",
			array("%dir" => getcwd())
		)
		. t("If not specified, the default will be Drupal's root directory.")
		;

	$form["target"]["#default_value"] = 
		variable_get("backup_target", "");

	$form["capture_errors"]["#type"] = "checkbox";
	$form["capture_errors"]["#title"] = t("Capture errors from backup run?");
	$form["capture_errors"]["#description"] = t("Save the contents of stderr. ")
		. t("Only check this if you know what you are doing. ") 
		. t("It may cause errors when performing a backup!");
	$form["capture_errors"]["#default_value"] = 
		variable_get("backup_capture_errors", "");

	$form["from_parent"]["#type"] = "checkbox";
	$form["from_parent"]["#title"] = t("Backup from parent directory?");
	$form["from_parent"]["#description"] = 
		t("Some users prefer to have files in the backup be in a directory under the root directory. ")
		. t("If this option is used, when a backup is opened, you will see only a single directory, which contains all of your files and the database dump.");
	$form["from_parent"]["#default_value"] = 
		variable_get("backup_from_parent", "");

	$form["save"]["#type"] = "submit";
	$form["save"]["#value"] = t("Save Config");

	return($form);

} // End of backup_form_config()


/**
* Create a list of our current backups.
*
* @return array An array for the form elements.
*/
function backup_form_files() {

	include_once("functions.inc.php");

	$form = array();

	$form["#type"] = "fieldset";
	$form["#title"] = t("Backups");
	$form["#description"] = t("Past backups that have been made: ");
	$form["#collapsible"] = TRUE;
	$form["#collapsed"] = FALSE;

	$form["files"] = array();
	$error = backup_get_backups($files);

	//
	// If no backups have been made, then stop here and return null.
	// There is no need to display any of this form element at all.
	//
	if (empty($files)) {
		return(null);
	}
    
	if (!empty($error)) {
		drupal_set_message($error, "error");
	}

	foreach ($files as $key => $value) {
		$size = $value["size"];
		$date = $value["date"];
		$name = basename($value["filename"]);
		//
		// Replace periods with proper hex codes.
		// Why?  Because Drupal's form function tries to be clever and 
		// replace periods with underscores, which causes the key names not
		// to match when the form is submitted.
		//
		// The safest way to do filename translation without corrupting
		// the string is to encode the period so that all I will have to do
		// on form submission is call rawurldecode() on the key.
		//
		$name = str_replace(".", "%2E", $name);

		$file = array();
		$file["#description"] = t("Backup from ") . $date;

		$delete = array();
		$delete["#type"] = "checkbox";
		$delete["#name"] = $name;

		$row = array();
		$row["file"] = $file;
		$row["size"] = array();
		$row["size"]["#description"] = $size . t(" bytes");
		$row["delete"][$delete["#name"]] = $delete;
		
		$form["files"][] = $row;
	}

	//
	// Specify a custom theme function for displaying these files.
	//
	$form["files"]["#theme"] = "form_files";

	//
	// The delete button
	//
	$form["delete"] = array();
	$form["delete"]["#type"] = "submit";
	$form["delete"]["#value"] = t("Delete Selected Backups");

	return($form);

} // End of backup_form_files()


/**
* Theming function for the list of currently existing backup files.
*
* @param array $form Associative array of form data.
*
* @return string Rendered HTML with a table and form elements.
*/
function theme_form_files($form) {

	$retval = "";
	$rows = array();

	$target = variable_get("backup_target", "");
	if (empty($target)) {
		$target = ".";
	}

	//
	// Loop through all of the children elements from this form.
	//
	foreach (element_children($form) as $key) {

		//
		// Get the first key in the delete array, which is the filename, 
		// then urldecode it and preprend the target directory.
		//
		$filename = key($form[$key]["delete"]);
		$filename = $target . "/" . rawurldecode($filename);

		$row = array();
		$row[] = l(
			$form[$key]["file"]["#description"],
			$filename
			);
		$row[] = $form[$key]["size"]["#description"];
		$row[] = drupal_render($form[$key]["delete"]);

		$rows[] = $row;

	}

	//
	// Generate the table
	//
	$header = array(t("Backup (click to download)"), t("Size"), t("Delete?"));
	$retval = theme("table", $header, $rows);

	//$retval = drupal_render($form);
	return($retval);

} // End of theme_form_files()

?>
