package com.example.design_pattern;


import java.util.*;

public class Command {

	private static class CommandImplementation{

		private static interface Command_{
			void execute();
		}

		private static class CommandReciever{
			public void doSomething(String message){
				System.out.println("Reciever : "+ message);
			}
		}

		private static class ComplexCommand implements Command_ {
			CommandReciever receiver;
			String firstMessage;
			String secondMessage;

			ComplexCommand(CommandReciever receiver, String firstMessage, String secondMessage){
				this. receiver = receiver;
				this.firstMessage =firstMessage;
				this.secondMessage = secondMessage;
			}

			@Override
			public void execute(){
				receiver.doSomething(firstMessage);
				receiver.doSomething(secondMessage);
			}
		}
		
		private static class Command1 implements Command_ {
			
			@Override
			public void execute(){
				System.out.println("execute Command1" );
			}
		}

		private static class Command2 implements Command_ {
			
			@Override
			public void execute(){
				System.out.println("execute Command2" );
			}
		}

		private static class CommandHistory {
			private Stack<Command_> history = new Stack<>();

			public void add(Command_ cmd){
				history.add(cmd);
			}

			public Command_ pop() {
				return history.pop();
			}
		}

		private static class CommandInvoker {

			private Command_ onStart;
			private Command_ onFinish;
			private CommandHistory history = new CommandHistory();

			CommandInvoker(Command_ onStart, Command_ onFinish){
				this.onStart = onStart;
				this.onFinish = onFinish;
			}

			public void doSomething(Command_ cmd){
				onStart.execute();
				history.add(cmd);
				cmd.execute();
				onFinish.execute();
			}
		}

		public static void main(){
			CommandInvoker invocker = new CommandInvoker(new Command1(), new Command2());
			CommandReciever receiver = new CommandReciever();
			invocker.doSomething(new ComplexCommand(receiver, " Hello ", " World "));

		}
	}

	private static class CommandImplementation2{

		private static class BankAccount{
			private int balance = 0;
			private int overdraftLimit = -500;

			public void deposit(int amount){
				balance += amount;
				System.out.println(String.format("[deposit] %d, balance is now %d.", amount, balance));
			}
			public void withdraw(int amount){
				if(balance - amount > overdraftLimit){
					balance -= amount;
					System.out.println(String.format("[withdraw] %d, balance is now %d.", amount, balance ));	
				}
			}
		}

		private static interface Command_ {
			void call();
		}

		private static class BankAccountCommand implements Command_{
			private final BankAccount account;
			private final int amount;
			private final Action action;
			
			public static enum Action{
				DEPOSIT, WITHDRAW
			};


			BankAccountCommand(BankAccount account, Action action, int amount){
				this.account = account;
				this.amount = amount;
				this.action = action;
			}

			@Override
			public void call(){
				switch(action){
					case DEPOSIT -> account.deposit(amount);
					case WITHDRAW -> account.withdraw(amount);
				}
			}
		}

		public static void main(){
			BankAccount account = new BankAccount();
			Command_ command = new BankAccountCommand(account, BankAccountCommand.Action.DEPOSIT, 10000);
			command.call();
		}
	}

	private static class CommandWithUndo{

		private static class BankAccount{
			private int balance = 0;
			private int overdraftLimit = -500;

			public boolean deposit(int amount){
				balance += amount;
				System.out.println(String.format("[deposit] %d, balance is now %d.", amount, balance));
				return true;
			}
			public boolean withdraw(int amount){
				if(balance - amount > overdraftLimit){
					balance -= amount;
					System.out.println(String.format("[withdraw] %d, balance is now %d.", amount, balance ));	
					return true;
				}
				return false;
			}
		}

		private static interface Command_ {
			void call();
			void undo();

		}

		private static class BankAccountCommand implements Command_{

			private final BankAccount account;
			private final Action action;
			private final int amount;
			private boolean succeeded = false;

			public static enum Action {
				DEPOSIT, WITHDRAW;
			}

			BankAccountCommand(BankAccount account, Action action, int amount){
				this.account = account;
				this.action = action;
				this.amount = amount;
			}

			@Override
			public void call(){
				switch (action) {
					case DEPOSIT -> {
						succeeded = account.deposit(amount);
					}
					case WITHDRAW -> {
						succeeded = account.withdraw(amount);
					}
				}
			}

			@Override
			public void undo(){
				if(!succeeded) return;

				switch (action) {
					case DEPOSIT -> account.withdraw(amount);
					case WITHDRAW -> account.deposit(amount);
				}
				succeeded = false;
			}
		}

		public static void main(){
			BankAccount account = new BankAccount();
			Command_ command = new BankAccountCommand(account, BankAccountCommand.Action.DEPOSIT, 10000);
			command.call();
			command.undo();
		}
	}

	private static class CompositeCommand {

		private static class BankAccount{
			private int balance = 0;
			private int overdraftLimit = -500;

			public boolean deposit(int amount){
				balance += amount;
				System.out.println(String.format("[deposit] %d, balance is now %d.", amount, balance));
				return true;
			}
			public boolean withdraw(int amount){
				if(balance - amount > overdraftLimit){
					balance -= amount;
					System.out.println(String.format("[withdraw] %d, balance is now %d.", amount, balance ));	
					return true;
				}
				return false;
			}
		}

		private static interface Command_ {
			void call();
			void undo();
		}

		private static class BankAccountCommand implements Command_ {

			private final BankAccount account;
			private final Action action;
			private final int amount;
			public boolean succeeded = false;

			public static enum Action {
				DEPOSIT, WITHDRAW;
			}

			BankAccountCommand(BankAccount account, Action action, int amount){
				this.account = account;
				this.action = action;
				this.amount = amount;
			}

			@Override
			public void call(){
				switch (action){
					case DEPOSIT -> {
						succeeded = account.deposit(amount);
					}
					case WITHDRAW -> {
						succeeded = account.withdraw(amount);
					} 
				}
			}

			@Override
			public void undo(){
				if(!succeeded) return;

				switch (action) {
					case DEPOSIT -> account.withdraw(amount);
					case WITHDRAW -> account.deposit(amount);
				}
			}
		}

		private static class CompositeBankAccountCommand implements Command_ {

			private List<BankAccountCommand> commands;

			CompositeBankAccountCommand(List<BankAccountCommand> commands){
				this.commands = commands;
			}

			public static CompositeBankAccountCommand of(BankAccountCommand... commands){
				return new CompositeBankAccountCommand(List.of(commands));
			}

			@Override
			public void call(){
				boolean ok = true; 

				for(BankAccountCommand command : commands){
					if(!ok) continue;
					command.call();
					ok = command.succeeded;
				}

			}

			@Override
			public void undo(){
				ListIterator<BankAccountCommand> iter = commands.listIterator();
				while(iter.hasPrevious()){
					BankAccountCommand command = iter.previous();
					command.undo();
				}
			}
		}

		public static void main(){
			BankAccount account = new BankAccount();
			Command_ command = CompositeBankAccountCommand.of(
				new BankAccountCommand(account, BankAccountCommand.Action.DEPOSIT, 10000),
				new BankAccountCommand(account, BankAccountCommand.Action.WITHDRAW, 10000),
				new BankAccountCommand(account, BankAccountCommand.Action.WITHDRAW, 10000),
				new BankAccountCommand(account, BankAccountCommand.Action.DEPOSIT, 10000)
			);
			command.call();
		}
	}

	private static class CommandQuerySeperation {

		private static class Creature {
			private int strength;
			private int agility;

			public int processQuery(CreatureQuery query){
				switch (query.ability){
					case STRENGTH : return strength;
					case AGILITY : return agility;
				}
				return -1;
			}

			public void processCommand(CreatureCommand command){
				
				int tmp = 0;
				switch (command.ability){
					case STRENGTH -> {
						tmp = strength;
					}
					case AGILITY -> {
						tmp = agility;
					}
				}

				switch (command.action){
					case INCREASE_BY -> tmp += command.amount;
					case DECREASE_BY -> tmp -= command.amount;
					case SET -> tmp = command.amount;
				}

				switch (command.ability){
					case STRENGTH -> {
						strength = tmp;
					}
					case AGILITY -> {
						agility = tmp;
					}
				}
			}

			@Override
			public String toString(){
				return String.format("[Creature] str : %d, agility : %d", strength, agility);
			}
		}

		public static enum CreatureAbility{
			STRENGTH, AGILITY
		}

		private static class CreatureQuery {
			public final CreatureAbility ability;
			CreatureQuery(CreatureAbility ability){
				this.ability = ability;
			}
		}

		private static class CreatureCommand {
			public final CreatureAbility ability;
			public final Action action;
			public final int amount;

			public static enum Action {
				INCREASE_BY, DECREASE_BY, SET
			}

			CreatureCommand(CreatureAbility ability, Action action, int amount){
				this.ability = ability;
				this.action = action;
				this.amount = amount;
			}
		}


		public static void main(){


			Creature creature = new Creature();
			System.out.println(creature.processQuery(new CreatureQuery(CreatureAbility.STRENGTH)));
			creature.processCommand(new CreatureCommand(CreatureAbility.STRENGTH, CreatureCommand.Action.SET, 10));
			creature.processCommand(new CreatureCommand(CreatureAbility.AGILITY, CreatureCommand.Action.INCREASE_BY, 10));
			System.out.println(creature);
		}
	}

	public static void main(String... args){
		CommandImplementation.main();
		CommandImplementation2.main();
		CommandWithUndo.main();
		CompositeCommand.main();
		CommandQuerySeperation.main();

	}
}