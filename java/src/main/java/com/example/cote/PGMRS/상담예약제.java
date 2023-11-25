package com.example.cote.PGMRS;

import java.util.*;
import java.nio.file.*;
import java.io.*;

public class 상담예약제{

	private static class Customer {
		final int arrivedAt;
		final String name;

		Customer(String name, String arrivedAt){
			this.name = name;
			this.arrivedAt = parseTime(arrivedAt);
		}

		private static int parseTime(String time){
			String[] s = time.split(":");
			return Integer.parseInt(s[0]) * 60 + Integer.parseInt(s[1]);
		}
	}

	private static String[] solve(String[][] booked, String[][] unbooked){

		Queue<Customer> bookedCustomers = new LinkedList<>();
		Queue<Customer> unbookedCustomers = new LinkedList<>();

		for(String[] b : booked){
			bookedCustomers.offer(new Customer(b[1], b[0]));
		}

		for (String[] b : unbooked){
			unbookedCustomers.offer(new Customer(b[1], b[0]));
		}

		List<String> result = new LinkedList<>();

		int currentTime = Math.min(bookedCustomers.peek().arrivedAt, unbookedCustomers.peek().arrivedAt);

		while(!bookedCustomers.isEmpty() || !unbookedCustomers.isEmpty()){
			if(bookedCustomers.isEmpty()){
				for(Customer c : unbookedCustomers){
					result.add(c.name);
				}
				break;
			}

			if(unbookedCustomers.isEmpty()){
				for(Customer c : bookedCustomers){
					result.add(c.name);
				}
				break;
			}

			final Customer bookedCustomer = bookedCustomers.peek();
			final Customer unbookedCustomer = unbookedCustomers.peek();

			if(bookedCustomer.arrivedAt <= currentTime){
				result.add(bookedCustomer.name);
				bookedCustomers.poll();
				currentTime += 10;
				continue;
			}

			if(unbookedCustomer.arrivedAt <= currentTime){
				result.add(unbookedCustomer.name);
				unbookedCustomers.poll();
				currentTime += 10;
				continue;
			}

			Customer c;

			if(bookedCustomer.arrivedAt <= unbookedCustomer.arrivedAt){
				c = bookedCustomers.poll();
			}else {
				c = unbookedCustomers.poll();
			}
			result.add(c.name);
			currentTime = c.arrivedAt + 10;

		}

		return result.toArray(String[]::new);
	}
	
	public static void main(String... args) throws IOException{
		Path p = Paths.get(System.getProperty("user.dir")+"/data/상담예약제.txt");
		BufferedReader rd = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(rd.readLine());
		while(testCases > 0){

			int numBooked = Integer.parseInt(rd.readLine());

			String[][] booked = new String[numBooked][2];

			for(int i =0; i< numBooked; i++){
				booked[i] = rd.readLine().split(" ");
			}

			int numUnbooked= Integer.parseInt(rd.readLine());
			String[][] unbooked = new String[numUnbooked][2];

			for(int i =0; i< numUnbooked; i++){
				unbooked[i] = rd.readLine().split(" ");
			}
			String[] answer = rd.readLine().split(" ");

			System.out.println(Arrays.toString(solve(booked, unbooked)));
			System.out.println(Arrays.toString(answer));

			testCases--;
		}
	}
}