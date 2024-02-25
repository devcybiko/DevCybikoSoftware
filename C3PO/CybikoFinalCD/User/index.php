<html>
<body>
<h1>Cybiko Upload (2MB max)</h1>
<!-- The data encoding type, enctype, MUST be specified as below -->
<form enctype="multipart/form-data" action="index.php" method="POST">
    <!-- MAX_FILE_SIZE must precede the file input field -->
    <input type="hidden" name="MAX_FILE_SIZE" value="2000000" />
    <!-- Name of input element determines name in $_FILES array -->
    Send this file: <input name="userfile" type="file" />
    <input type="submit" value="Send File" />
</form>
<?php
if ($_FILES['userfile']['name'] != "") {
// In PHP versions earlier than 4.1.0, $HTTP_POST_FILES should be used instead
// of $_FILES.

$uploadfile = basename($_FILES['userfile']['name']);

echo '<pre>';
if (move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile)) {
echo "File is valid, and was successfully uploaded.\n";
} else {
echo "Possible file upload attack!\n";
}
?>
<br>Full &nbsp;URL='http://devcybiko.us/Cybiko/User/<?=$_FILES['userfile']['name']?>'
<br>Short URL='Cybiko/User/<?=$_FILES['userfile']['name']?>'
<?

//echo 'Here is some more debugging info:';
//print_r($_FILES);

print "</pre>";
}
?> 

</body>
</html>