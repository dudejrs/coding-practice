package com.example.design_pattern.template_method;

import java.util.*;
import java.util.function.*;

public class FunctionalTemplateMethod {

  private static class Customer {
    public int id;
    public String name = "Unknown";
    public int balance = 0;

    Customer(int id) {
      this.id = id;
    }
  }

  private static class Database {
    private static Map<Integer, Customer> customers = new HashMap<>();

    private Database() {}

    public static Customer getCustomenr(int id) {

      if (customers.get(id) == null) {
        customers.put(id, new Customer(id));
      }

      return customers.get(id);
    }
  }

  private static class OnlineBanking {

    private Consumer<Customer> makeCustomerHappy;

    OnlineBanking(Consumer<Customer> makeCustomerHappy) {
      this.makeCustomerHappy = makeCustomerHappy;
    }

    final void processCustomer(int id) {
      Customer c = Database.getCustomenr(id);
      makeCustomerHappy.accept(c);
    }
  }

  public static void main(String... args) {
    OnlineBanking hello =
        new OnlineBanking(
            (Customer c) -> {
              System.out.printf("Hello %s!\n", c.name);
            });
    hello.processCustomer(1234);
    OnlineBanking deposit =
        new OnlineBanking(
            (Customer c) -> {
              c.balance += 100_0000;
              System.out.printf("Your Balance is %d.\n", c.balance);
            });
    deposit.processCustomer(1234);
  }
}
