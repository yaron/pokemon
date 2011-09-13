<?php

class mysql {
  private $connection;

  function connect ($db_string) {
    $db = parse_url($db_string);

    $this->connection = new mysqli($db['host'], $db['user'], $db['pass'], trim($db['path'], '/'));
  }

  function select() {
    return new mysql_select_query($this->connection);
  }

  function insert() {
    return new mysql_insert_query($this->connection);
  }
}

class mysql_select_query {
  protected $table = array();
  protected $where = array();
  protected $column = array();

  protected $connection;

  function __construct($connection) {
    $this->connection = $connection;
  }

  function column($column) {
    $this->column[] = $column;

    return $this;
  }

  function table($table) {
    $this->table[] = $table;

    return $this;
  }

  function where($column, $where, $statement = '=') {
    $this->where[] = array(
      'where' => $where,
      'statement' => $statement,
      'column' => $column,
    );

    return $this;
  }

  function query() {
    $sql =
      'SELECT ' . implode(' ,', $this->column)
      . ' FROM ' . reset($this->table);

    if (count($this->where)) {
      $sql .= ' WHERE ';
      $first = TRUE;
      foreach ($this->where as $where) {
        if (!$first) {
          $sql .= ' AND ';
          $first = FALSE;
        }
        $sql .= $where['column'] . $where['statement'] . "'" . $where['where'] . "'";
      }
    }

    return $this->connection->query($sql);
  }
}


class mysql_insert_query {
  protected $table = array();
  protected $column = array();

  protected $connection;

  function __construct($connection) {
    $this->connection = $connection;
  }

  function column($name, $value) {
    $this->column[$name][] = $value;

    return $this;
  }

  function table($table) {
    $this->table[] = $table;

    return $this;
  }

  function query() {
    $sql =
      'INSERT INTO ' . reset($this->table);

      $sql .= '(' . implode(', ', array_keys($this->column)) . ')  VALUES ';

      $first_column = reset($this->column);

      for ($i = count($first_column)-1; $i >= 0; --$i) {
        $row = array();
        foreach ($this->column as $column) {
          $row[] = $column[$i];
        }

        $sql .= "('" . implode("', '", $row) . "')";
      }

    return $this->connection->query($sql);
  }
}
