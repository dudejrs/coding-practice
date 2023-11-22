package com.example.design_pattern;

import java.util.*;
import java.util.concurrent.*;

public class Singleton{

	private static class ConventionalSingleton {

		private static class Database{
			private static Database db;

			private Database(){}

			public static Database getInstance(){
				if( db == null){
					db = new Database();
				}
				return db;
			}

		}

		public static void main(){
			Database db1 = Database.getInstance();
			Database db2 = Database.getInstance();

			assert db1 == db2;
		}
	}

	private static class SingletonWithSyncronization {

		private static class Database {
			private static Database db;
			private Database(){}

			public static Database getInstance(){
				if(db ==null){
					synchronized(Database.class){
						if(db == null){
							db = new Database();
						}
					}
				}
				return db;
			}
		}

		public static void main(){
			Database db1 = Database.getInstance();
			Database db2 = Database.getInstance();

			assert db1 == db2;
		}
	}

	private static class SingletonHolder {
		private static class Database {
			private Database(){}

			private static class DatabaseHolder{
				public static final Database db = new Database();
			}

			public static Database getInstance(){
				return DatabaseHolder.db;
			}
		}

		public static void main(){
			Database db1 = Database.getInstance();
			Database db2 = Database.getInstance();

			assert db1 == db2;
		}
	}

	private static class ThreadSingleton {

		private static class Database {
			private static final ConcurrentHashMap<Long, Database> instances  = new ConcurrentHashMap<>();
			private Database(){}

			public static Database getInstance(){
				Long concurrentThreadId = Thread.currentThread().getId();
				instances.putIfAbsent(concurrentThreadId, new Database());
				return instances.get(concurrentThreadId);
			}
		}

		public static void main() {
			ExecutorService service = Executors.newFixedThreadPool(2);
			try {
				Callable<Database> task = () -> Database.getInstance();
				Future<Database> db1 = service.submit(task);
				Future<Database> db2 = service.submit(task);
				
				assert(db1.get() != db2.get());

			} catch (InterruptedException | ExecutionException e){
				System.out.println("exception occurs");
			} finally {
				service.shutdown();
			}

		}
	}

	public static void main(String... args){
		ConventionalSingleton.main();
		SingletonWithSyncronization.main();
		SingletonHolder.main();
		ThreadSingleton.main();
	}
}