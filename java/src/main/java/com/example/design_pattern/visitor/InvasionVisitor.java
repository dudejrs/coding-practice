package com.example.design_pattern.visitor;

import java.io.*;

public class InvasionVisitor {

	private static interface Expression {
		void print(PrintStream out);
	}

	private static class AdditionalExpression implements Expression {
		private Expression left;
		private Expression right;

		AdditionalExpression(Expression left, Expression right) {
			this.left = left;
			this.right = right;
		}

		@Override 
		public void print(PrintStream out) {
			out.print("(");
			left.print(out);
			out.print("+");
			right.print(out);
			out.print(")");
		}
	}

	private static class DoubleExpression implements Expression{
		private final double value;

		DoubleExpression(double value) {
			this.value = value;
		}

		@Override 
		public void print(PrintStream out) {
			out.print(value);
		}
	}
	
	public static void main(String... args) {
		Expression e = new AdditionalExpression (
			new DoubleExpression(1),
			new AdditionalExpression(
				new DoubleExpression(2),
				new DoubleExpression(3)
			)
		);

		e.print(System.out);
		System.out.println();
	}
}