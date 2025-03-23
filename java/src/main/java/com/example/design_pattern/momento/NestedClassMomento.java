package com.example.design_pattern.momento;

import java.util.*;

public class NestedClassMomento {

  public static class Originator {

    private static record Momento(int value) {}

    private int value;

    Originator(int value) {
      this.value = value;
    }

    public int getValue() {
      return this.value;
    }

    public void setValue(int value) {
      this.value = value;
    }

    public Momento save() {
      return new Momento(value);
    }

    public void restore(Momento m) {
      this.value = m.value;
    }

    @Override
    public String toString() {
      return String.format("value : %d", value);
    }
  }

  public static class Caretaker {
    private Originator originator;
    private Stack<Originator.Momento> history = new Stack<>();

    Caretaker(Originator originator) {
      this.originator = originator;
    }

    public void save() {
      Originator.Momento m = originator.save();
      history.push(m);
    }

    public void undo() {
      if (history.isEmpty()) {
        return;
      }
      Originator.Momento m = history.pop();
      originator.restore(m);
    }
  }

  public static void main(String... args) {
    Originator origin = new Originator(0);
    Caretaker ct = new Caretaker(origin);
    ct.save();
    origin.setValue(1);
    origin.setValue(2);
    ct.undo();

    System.out.println(origin);
  }
}
