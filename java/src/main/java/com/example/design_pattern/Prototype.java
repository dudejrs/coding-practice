package com.example.design_pattern;

import java.util.*;

public class Prototype {
	
 	private static class Prototype1{

 		private static class Address implements Cloneable{
 			private String street;
 			private String city;
 			private int suite;

 			Address(String street, String city, int suite){
 				this.street = street;
 				this.city = city;
 				this.suite = suite;
 			}

 			public void setSuite(int suite){
 				this.suite = suite;
 			}

 			@Override
 			public Address clone(){
 				try{
 					return (Address) super.clone();
 				}catch(CloneNotSupportedException e){
 					return null;
 				}
 			}

 			@Override
 			public String toString(){
 				return String.format("%s %s %d", street, city, suite);
 			}
 		}

 		private static class Contact implements Cloneable{
 			private String name;
 			private Address address;

 			Contact(String name, Address address) {
 				this.name = name;
 				this.address = address;
 			}

 			public void setName(String name){
 				this.name = name;
 			}

 			public void setSuite(int suite){
 				address.setSuite(suite);
 			}

 			private void setAddress(Address address){
 				this.address = address;
 			}

 			@Override
 			public Contact clone(){
 				try{
 					Address clonedAddress = address.clone();
 					Contact contact = (Contact) super.clone();
 					contact.setAddress(clonedAddress);
 					return contact;
 				}catch(CloneNotSupportedException e){
 					return null;
 				}
 			}

 			@Override
 			public String toString(){
 				return String.format("%s %s", name , address);
 			}
 		}

 		public static void main(String... args){
 			Address workerAddress = new Address("123 East Dr", "London", 0);
 			Contact workerEntry = new Contact("worker", workerAddress);

 			Contact johnEntry = workerEntry.clone();
 			johnEntry.setName("John Doe");
 			johnEntry.setSuite(10);

 			Contact janeEntry = workerEntry.clone();
 			janeEntry.setName("Jane Doe");
 			janeEntry.setSuite(11);

 			System.out.println(johnEntry);
 			System.out.println(janeEntry);
 		}
 	}

 	private static class PrototypeFactory{

 		 private static class Address implements Cloneable{
 			private String street;
 			private String city;
 			private int suite;

 			Address(String street, String city, int suite){
 				this.street = street;
 				this.city = city;
 				this.suite = suite;
 			}

 			public void setSuite(int suite){
 				this.suite = suite;
 			}

 			@Override 
 			public Address clone(){
 				try{
 					return (Address) super.clone();
 				}catch (CloneNotSupportedException e){
 					return null;
 				}
 			}

 			@Override
 			public String toString(){
 				return String.format("%s %s %d", street, city, suite);
 			}
 		}

 		private static class Contact implements Cloneable{
 			private String name;
 			private Address address;

 			Contact(String name, Address address) {
 				this.name = name;
 				this.address = address;
 			}
 			Contact(String name, String street, String city, int suite){
 				this.name = name; 
 				this.address = new Address(street, city, suite);
 			}

 			public void setSuite(int suite){
 				address.setSuite(suite);
 			}

 			public void setName(String name){
 				this.name = name;
 			}

 			@Override
 			public Contact clone(){
 				try {
 					Address clonedAddress = address.clone();
 					Contact contact = (Contact) super.clone();
 					return contact;

 				}catch( CloneNotSupportedException e){
 					return null;
 				}
 			}

 			@Override
 			public String toString(){
 				return String.format("%s %s", name, address);
 			}
 		}

 		private static class EmploymentFactory{
 			private static Contact main = new Contact("main employee", "123 East Dr", "London", 0);
 			private static Contact aux = new Contact("aux employee", "1238 East Dr", "London", 0);

 			private EmploymentFactory(){
 			}

 			public static Contact newMainEmployee(String name, int suite){
 				return newEmployee(main, name, suite);
 			}

 			public static Contact newAuxEmployee(String name, int suite){
 				return newEmployee(aux, name, suite);
 			}

 			private static Contact newEmployee(Contact proto, String name, int suite){
 				Contact employee = proto.clone();
 				employee.setName(name);
 				employee.setSuite(suite);
 				return employee;
 			}
 		}


 		public static void main(String... args){
 			System.out.println(EmploymentFactory.newMainEmployee("john doe", 10));
 			System.out.println(EmploymentFactory.newAuxEmployee("jane doe", 11));
 		}
 	}

 	private static class PrototypeRegistery{

		private static enum Color {
			RED, GREEN, BLUE;
		}

 		private static class Button implements Cloneable{
 			private int x;
 			private int y;
 			private Color color;


 			Button(int x, int y, Color color){
 				this.x = x;
 				this.y = y;
 				this.color = color;
 			}

 			@Override
 			public Button clone(){
 				try {
 					return (Button) super.clone();
 				} catch(CloneNotSupportedException ex){
 					return null;
 				}
 			}
 		}

 		private static class ButtonRegistery {
 			Map<Color, Button> items;

 			ButtonRegistery(){
 				items = new HashMap<>();
 			}

 			void addItem(Color color, Button button){
 				items.put(color, button);
 			}

 			Button getByColor(Color color){
 				Button button = items.get(color);
 				return button.clone();
 			}
 		}

 		public static void main(String... args){
 			Button button = new Button(10, 40, Color.RED);

 			ButtonRegistery registry = new ButtonRegistery();
 			registry.addItem(Color.RED, button);
 			Button button2 = registry.getByColor(Color.RED);

 			assert( button != button2);
 		}
 	}


	public static void main(String... args){
		Prototype1.main();
		PrototypeFactory.main();
		PrototypeRegistery.main();
	}
}