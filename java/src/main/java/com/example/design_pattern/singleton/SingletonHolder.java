package com.example.design_pattern.singleton;

public class SingletonHolder {
	private static class Database {
		private Database(){}

		private static class DatabaseHolder{
			public static final Database db = new Database();
		}

		public static Database getInstance(){
			return DatabaseHolder.db;
		}
	}

	public static void main(String... args){
		Database db1 = Database.getInstance();
		Database db2 = Database.getInstance();

		assert db1 == db2;
	}
}