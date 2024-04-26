package com.example.design_pattern.visitor;

import java.io.*;

public class ConventionalVisitor {
	
	private static interface Expression {
		void accept(ExpressionVisitor visitor);
	}

	private static interface ExpressionVisitor {
		void visit(Expression e);
		void visit(AdditionalExpression ae);
		void visit(DoubleExpression de);
	}

	private static class AdditionalExpression implements Expression {
		private Expression left;
		private Expression right;

		AdditionalExpression(Expression left, Expression right) {
			this.left = left;
			this.right = right;
		}

		@Override 
		public void accept(ExpressionVisitor visitor) {
			visitor.visit(this);
		}


		// public double evaluate() {
		// 	return left.evaluate() + right.evaluate();
		// }
	}

	private static class DoubleExpression implements Expression{
		private final double value;

		DoubleExpression(double value) {
			this.value = value;
		}
		
		@Override 
		public void accept(ExpressionVisitor visitor) {
			visitor.visit(this);
		}
	}

	private static class ExpressionPrinter implements ExpressionVisitor {

		PrintStream out;

		ExpressionPrinter(PrintStream out) {
			this.out = out;
		}

		@Override
		public void visit(Expression e) {
			if (e instanceof AdditionalExpression){
				visit((AdditionalExpression) e);
			}

			if (e instanceof DoubleExpression){
				visit((DoubleExpression) e);
			}
		}

		@Override
		public void visit(AdditionalExpression ae){
			out.print("(");
			ae.left.accept(this);
			out.print("+");
			ae.right.accept(this);
			out.print(")");
		}

		@Override
		public void visit(DoubleExpression de){
			out.print(de.value);
		}

	}

	private static class ExpressionEvaluator implements ExpressionVisitor {

		public double result;

		@Override
		public void visit(Expression e){
			if (e instanceof AdditionalExpression){
				visit((AdditionalExpression) e);
			}

			if (e instanceof DoubleExpression){
				visit((DoubleExpression) e);
			}
		}

		@Override
		public void visit(AdditionalExpression ae){
			ae.left.accept(this);
			double tmp = result;
			ae.right.accept(this);
			result += tmp;
		}

		@Override
		public void visit(DoubleExpression de){
			result = de.value;
		}

		@Override
		public String toString() {
			return Double.toString(result);
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

		ExpressionPrinter printer = new ExpressionPrinter(System.out);
		ExpressionEvaluator evaluator = new ExpressionEvaluator();

		printer.visit(e);
		evaluator.visit(e);
		System.out.printf("= %s\n", evaluator);
	}
}