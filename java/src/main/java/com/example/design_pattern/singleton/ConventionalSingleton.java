package com.example.design_pattern.singleton;

public class ConventionalSingleton {

  private static class Database {
    private static Database db;

    private Database() {}

    public static Database getInstance() {
      if (db == null) {
        db = new Database();
      }
      return db;
    }
  }

  public static void main(String... args) {
    Database db1 = Database.getInstance();
    Database db2 = Database.getInstance();

    assert db1 == db2;
  }
}
