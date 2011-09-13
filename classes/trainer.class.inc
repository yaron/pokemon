<?php

class trainer {
  protected $name;
  protected $exists;

  public function __construct($name) {
    $this->name = $name;
    $this->load_trainer();
  }

  protected function load_trainer() {
    global $db;
    $result = $db->select('trainer')
      ->column('name', $this->name)
      ->where('name', $this->name)
      ->query();

    if (!$result) {
      var_dump($result);
      $this->exists = FALSE;
      return FALSE;
    }
    $this->exists = TRUE;
  }

  public function doesExist() {
    return $this->exists;
  }

  public function create() {
    global $db;

    $db->insert('trainer')
      ->column('name', $this->name)
      ->query();
    $this->exists = TRUE;
  }
}
