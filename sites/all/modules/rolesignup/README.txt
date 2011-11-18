Role Signup

This module allows admins to select roles that users can register for.  

IE, a user will go to /user/register/ and get redirected to a role select page.  This page sets session['role'] to the rid that the user selected and redirects to the normal user form.

When the form is submited, the user will get added to the role from the session.  

By default no roles are added to the allowed role list.  This means that installing this module and doing nothing else will stop any users using the site.  

You should go to admin > access control and select the roles you would like users to be able to sign up to.