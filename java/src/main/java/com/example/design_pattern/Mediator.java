package com.example.design_pattern;


public class Mediator {

	private static class BasicMediator {

		private static class ComponenetA {
			private Mediator_ mediator;

			public void setMeidator(Mediator_ mediator){
				this.mediator = mediator;
			}

			public void operationA(){
				System.out.println("A does OperationA");
				mediator.notify("A", "B");
			}

			public void receive(String message){
				System.out.println("A recive message: "+ message);
			}
		}
		private static class ComponentB {
			private Mediator_ mediator;

			public void setMeidator(Mediator_ mediator){
				this.mediator = mediator;
			}

			public void operationB(){
				System.out.println("B does OperationB");
				mediator.notify("B", "A");
			}
			public void receive(String message){
				System.out.println("B recive message: "+ message);
			}
		}

		private static class Mediator_ {

			private ComponenetA a;
			private ComponentB b;

			Mediator_(ComponenetA a, ComponentB b){
				this.a = a;
				this.b = b;
				a.setMeidator(this);
				b.setMeidator(this);
			}

			public void notify(String sender, String reciever){
				if("A".equals(sender)){
					System.out.println(String.format("Mediator react to A and Send Message to %s", reciever));
					a.receive("Hello World!");
				}


				if("B".equals(sender)){
					System.out.println(String.format("Mediator react to B and Send Message to %s", reciever));
					b.receive("Hello World!");
				}
			}
		}


		public static void main(){
			ComponenetA a = new ComponenetA();
			ComponentB b = new ComponentB();

			Mediator_ mediator = new Mediator_(a,b);
			a.operationA();
			b.operationB();
		}
	}

	private static class CollectionMediator {
		public static void main(){

		}
	}

	private static class MediatorWithHierarchicalComponent {
		public static void main(){

		}
	}
	
	public static void main(String... args){
		BasicMediator.main();
		CollectionMediator.main();
		MediatorWithHierarchicalComponent.main();
	}
}