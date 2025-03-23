package com.example.design_pattern.null_object;

public class NullObject {

  public static interface Logger {
    void info(final String s);

    void warn(final String s);
  }

  public static class BankAccount {
    private String name;
    private int balance;
    private Logger logger;

    BankAccount(final String name, final int balance, final Logger logger) {
      this.name = name;
      this.balance = balance;
      this.logger = logger;
    }

    public void deposit(int amount) {
      balance += amount;
      logger.info(String.format("Deposited $%d to %s, balance is now $%d", amount, name, balance));
    }
  }

  public static class NullLogger implements Logger {
    @Override
    public void info(final String s) {
      /* do nothing */
    }
    ;

    public void warn(final String s) {
      /* do nothing */
    }
    ;
  }

  public static void main(String... args) {
    NullLogger logger = new NullLogger();
    BankAccount ba1 = new BankAccount("John", 10000, logger);
    ba1.deposit(5000);
  }
}
