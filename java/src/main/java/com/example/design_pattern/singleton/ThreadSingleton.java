package com.example.design_pattern.singleton;

import java.util.*;
import java.util.concurrent.*;


public class ThreadSingleton {

	private static class Database {
		private static final ConcurrentHashMap<Long, Database> instances  = new ConcurrentHashMap<>();
		private Database(){}

		public static Database getInstance(){
			Long concurrentThreadId = Thread.currentThread().getId();
			instances.putIfAbsent(concurrentThreadId, new Database());
			return instances.get(concurrentThreadId);
		}
	}

	public static void main(String... args) {
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
