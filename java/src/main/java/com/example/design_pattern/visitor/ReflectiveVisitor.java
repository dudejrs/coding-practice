package com.example.design_pattern.visitor;

import java.io.*;

public class ReflectiveVisitor {

  private static interface Expression {}

  private static class AdditionalExpression implements Expression {
    public Expression left;
    public Expression right;

    AdditionalExpression(Expression left, Expression right) {
      this.left = left;
      this.right = right;
    }
  }

  private static class DoubleExpression implements Expression {
    public final double value;

    DoubleExpression(double value) {
      this.value = value;
    }
  }

  private static class ExpressionPrinter {
    private PrintStream out;

    ExpressionPrinter(PrintStream out) {
      this.out = out;
    }

    void print(Expression e) {
      if (e instanceof AdditionalExpression) {
        AdditionalExpression ae = (AdditionalExpression) e;
        out.print("(");
        print(ae.left);
        out.print("+");
        print(ae.right);
        out.print(")");
      }
      if (e instanceof DoubleExpression) {
        DoubleExpression de = (DoubleExpression) e;
        out.print(de.value);
      }
    }
  }

  public static void main(String... args) {
    ExpressionPrinter printer = new ExpressionPrinter(System.out);

    Expression e =
        new AdditionalExpression(
            new DoubleExpression(1),
            new AdditionalExpression(new DoubleExpression(2), new DoubleExpression(3)));

    printer.print(e);
  }
}
