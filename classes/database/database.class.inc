<?php

class db_connection {
  protected $db_string;
  protected $connection;

  public function __construct($db_string = NULL) {
    $this->connect(empty($db_string)?DEFAULT_DB:$db_string);
  }

  private function connect($db_string) {
    $this->db_string = $db_string;
    $parts = explode(':', $db_string);
    $db_type = $parts[0];

    require_once('./classes/database/' . $db_type . '.class.inc');
    $this->connection = new $db_type;

    $this->connection->connect($this->db_string);
  }

  public function select($table) {
    $select = $this->connection->select();
    $select->table($table);
    return $select;
  }

  public function insert($table) {
    $insert = $this->connection->insert();
    $insert->table($table);
    return $insert;
  }
}
