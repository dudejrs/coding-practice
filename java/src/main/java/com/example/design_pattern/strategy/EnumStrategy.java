package com.example.design_pattern.strategy;

public class EnumStrategy {
  enum PayrollDay {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY(PayType.WEEKEND),
    SUNDAY(PayType.WEEKEND);

    private final PayType payType;

    PayrollDay() {
      this.payType = PayType.WEEKDAY;
    }

    PayrollDay(PayType payType) {
      this.payType = payType;
    }

    int pay(int minutesWorked, int payRate) {
      return payType.pay(minutesWorked, payRate);
    }

    enum PayType {
      WEEKDAY {
        int overtimePay(int minsWorked, int payRate) {
          return minsWorked <= MINS_PER_SHIFT ? 0 : (minsWorked - MINS_PER_SHIFT) * payRate / 2;
        }
      },
      WEEKEND {
        int overtimePay(int minsWorked, int payRate) {
          return minsWorked * payRate / 2;
        }
      };

      abstract int overtimePay(int minsWorked, int payRate);

      private static final int MINS_PER_SHIFT = 8 * 60;

      int pay(int minutesWorked, int payRate) {
        int basePay = minutesWorked * payRate;
        return basePay + overtimePay(minutesWorked, payRate);
      }
    }
  }

  public static void main(String... args) {
    PayrollDay today = PayrollDay.SUNDAY;
    PayrollDay tommorrow = PayrollDay.MONDAY;
    System.out.println(today.pay(600, 1000));
    System.out.println(tommorrow.pay(600, 1000));
  }
}
