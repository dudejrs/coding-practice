package com.example.cote.GJM;


import java.util.*;

public class 전세금_균등상환 {

	public static final Random random = new Random(43);
	public static final int TEST_CASES =10;
	public static final int MAX_DURATION = 120;
	public static final int MAX_AMOUNT = 10000;


	private static double balance(int amount, int duration, double rate, double monthlyAmount){
		double balance = amount;

		for(int i=0; i< duration; i++){
			balance *= (1 + (rate/12));
			balance -= monthlyAmount;
		}

		return balance;
	}

	private static double payment(int amount, int duration, double rate){
		
		double lo = 0, hi = amount * (1.0 + (rate/12.0));


		// lo < x  <= hi;

		for(int i=0; i<100; i++){
			double mid = (lo+hi)/2;
			if(balance(amount, duration, rate, mid) <= 0){
				hi = mid;
			}else {
				lo = mid;
			}
		}

		return hi;
	}

	public static void main(String... args){
		int testCases = TEST_CASES;

		while(testCases > 0){
			int amount = random.nextInt(MAX_AMOUNT-1)+1;
			int duration = random.nextInt(MAX_DURATION -1) +1;
			double rate = random.nextDouble();

			System.out.println(String.format("%d만(원)을 %d개월동안 %.2f 연이율로 상환하기 위해서는 월 %.2f만원씩 상환해야한다.\n", amount, duration, rate, payment(amount,duration,rate)));

			testCases--;
		}
	}
}