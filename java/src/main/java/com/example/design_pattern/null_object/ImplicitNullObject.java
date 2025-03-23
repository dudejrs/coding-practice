package com.example.design_pattern.null_object;

public class ImplicitNullObject {

  public static interface Logger {
    void info(final String s);

    void warn(final String s);
  }

  public static class OptionalLogger implements Logger {

    private Logger logger;

    OptionalLogger(Logger logger) {
      this.logger = logger;
    }

    @Override
    public void info(final String s) {
      if (logger != null) {
        logger.info(s);
      }
    }

    @Override
    public void warn(final String s) {
      if (logger != null) {
        logger.warn(s);
      }
    }
  }

  public static class BankAccount {
    private String name;
    private int balance;
    private Logger logger;

    BankAccount(final String name, final int balance, final Logger logger) {
      this.name = name;
      this.balance = balance;
      this.logger = new OptionalLogger(logger);
    }

    BankAccount(final String name, final int balance) {
      this(name, balance, null);
    }

    public void deposit(int amount) {
      balance += amount;
      logger.info(String.format("Deposited $%d to %s, balance is now $%d", amount, name, balance));
    }
  }

  public static void main(String... args) {
    BankAccount ba1 = new BankAccount("John", 10000);
    ba1.deposit(5000);
  }
}
