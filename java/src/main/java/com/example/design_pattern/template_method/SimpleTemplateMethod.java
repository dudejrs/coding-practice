package com.example.design_pattern.template_method;

public class SimpleTemplateMethod {

	private static abstract class Game {
		
		protected int numberOfPlayers;

		Game(int numberOfPlayers) {
			this.numberOfPlayers = numberOfPlayers;
		}

		abstract void start();

		abstract boolean isFinished();

		abstract void takeTurns();

		abstract int getWinner();

		public final void run() {
			start();

			while (!isFinished()) {
				takeTurns();
			}

			System.out.printf("Player%d wins\n", getWinner());
		}

	}

	private static class Chess extends Game{
		private int currentPlayer = 0;
		private int turns = 0; 
		private final int maxTurns;

		Chess(int maxTurns) {
			super(2);
			this.maxTurns = maxTurns;
		}

		protected void start() {
			System.out.println("Game started");
		}

		protected boolean isFinished() {
			return turns == maxTurns;
		}

		protected void takeTurns() {
			System.out.printf("Turns %d taken by Player%d.\n", turns, currentPlayer);
			turns++;
			currentPlayer = (currentPlayer + 1) % numberOfPlayers;			
		}

		protected int getWinner() {
			return currentPlayer;
		}
	}

	public static void main(String... args) {
		Game game = new Chess(10);
		game.run();
	}	
}