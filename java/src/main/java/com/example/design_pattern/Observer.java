package com.example.design_pattern;


import java.util.*;

public class Observer {

	public static class Observer1 {

		public static interface Observer_<T> {
			void fieldChange(T source, String fieldName);
		}

		public static class Observable<T> {
			private List<Observer_<T>> observers;

			Observable(){
				observers = new LinkedList<>();
			}

			void subscribe(Observer_<T> observer){
				synchronized(observers){
					observers.add(observer);
				}
			}

			void unsubscribe(Observer_<T> observer){
				synchronized(observers) {
					observers.remove(observer);
				}
			}

			void notify(T source, String fieldName){
				for(Observer_<T> ob : observers)
					ob.fieldChange(source, fieldName);
			}
		}

		public static class Person extends Observable<Person>{
			private int age;

			Person(int age){
				this.age = age;
			}

			int getAge() { return age;}
			void setAge(int age){
				this.age = age;
				notify(this, "age");
			}
		}

		public static class ConsolePersonObserver implements Observer_<Person>{
			
			@Override
			public void fieldChange(Person person, String fieldName){
				if("age".equals(fieldName)){
					System.out.println(String.format("Person's %s has changed to %s.", fieldName, person.getAge()));
				}
			}
		}


		public static void main(){
			Person p = new Person(20);
			ConsolePersonObserver observer = new ConsolePersonObserver();
			p.subscribe(observer);
			p.setAge(21);
			p.unsubscribe(observer);
			p.setAge(22);
		}
	}

	public static void main(String... args){
		Observer1.main();
	}
}