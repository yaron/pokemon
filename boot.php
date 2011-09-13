<?php
require_once('./boot.php');
require_once('./classes/trainer.class.inc');

require_once('./classes/database/database.class.inc');
$db = new db_connection();

if (isset($_SESSION['username'])) {
  $pokemaster = new trainer($_SESSION['username']);
}
elseif(isset($_POST['username'])) {
  $_SESSION['username'] = $_POST['username'];
  $pokemaster = new trainer($_SESSION['username']);
}
else {
  echo <<<FORM
Enter the name of your trainer:
<form method="post">
<input type="text" name="username" />
<input type="submit" value="Submit" />
</form>
FORM;
  exit;
}

if (!$pokemaster->doesExist()) {
  $pokemaster->create();
  echo 'No such trainer found. A new trainer was created.';
}
