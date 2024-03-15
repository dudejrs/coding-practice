package com.example.design_pattern.momento;

import java.util.*;

public class HierarchicalMomento {
	
	private static class CareTaker {
		private Stack<Momento> stack = new Stack<>();

		public void undo() {
			Momento m = stack.pop();
			m.restore();
		}
		public void save(Momento m){
			stack.push(m);
		}
	}

	private static interface Originator {
		void save();
	}

	private static interface Momento {
		void restore();
	}

	private static class ConcreteOriginatorA implements Originator{

		private static record MomentoA(
			ConcreteOriginatorA origin,
			int value
		) implements Momento {

			@Override
			public void restore() {
				origin().setValue(value);
			}
		}

		private int value = 0;
		private CareTaker careTaker;

		ConcreteOriginatorA(int value, CareTaker careTaker) {
			this.value = value;
			this.careTaker = careTaker;
		}

		@Override
		public void save() {
			careTaker.save(new MomentoA(this, value));
		}

		@Override
		public String toString(){
			return Integer.toString(value);
		}
		public void setValue(int value){
			this.value = value;
		}
	}

	private static class ConcreteOriginatorB implements Originator {

		private static record MomentoB(
			ConcreteOriginatorB origin,
			String value
		) implements Momento {

			@Override
			public void restore() {
				origin().setValue(value);
			}
		}

		private String value;
		private CareTaker careTaker;

		ConcreteOriginatorB(String value, CareTaker careTaker) {
			this.value = value;
			this.careTaker = careTaker;
		}
		@Override
		public void save() {
			careTaker.save(new MomentoB(this, value));
		}

		@Override
		public String toString(){
			return value;
		}
		public void setValue(String value) {
			this.value = value;
		}
	}

	public static void main(String... args) {

		CareTaker careTaker = new CareTaker();

		ConcreteOriginatorA a = new ConcreteOriginatorA(0, careTaker);
		ConcreteOriginatorB b = new ConcreteOriginatorB("B", careTaker);
		a.save();
		b.save();

		a.setValue(1);
		b.setValue("A");

		careTaker.undo();

		System.out.println(a); // 1
		System.out.println(b); // B

	}
}