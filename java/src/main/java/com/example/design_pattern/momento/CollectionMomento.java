package com.example.design_pattern.momento;

import java.util.*;

public class CollectionMomento {

  static record Momento(int balance) {}

  static class BankAccount {
    private int balance = 0;
    private Stack<Momento> changes = new Stack<>();

    BankAccount() {
      changes.add(new Momento(balance));
    }

    Momento deposit(int amount) {
      balance += amount;

      changes.push(new Momento(balance));

      return changes.peek();
    }

    void restore(Momento m) {
      if (m == null) {
        return;
      }
      changes.push(m);
    }

    Optional<Momento> undo() {
      if (changes.size() == 0) {
        return Optional.empty();
      }

      return Optional.of(changes.pop());
    }

    @Override
    public String toString() {
      return String.format("Account : %d", balance);
    }
  }

  public static void main(String... args) {
    BankAccount account = new BankAccount();
    Momento m1 = account.deposit(3000);
    account.undo();
    account.restore(m1);

    System.out.println(account);
  }
}
