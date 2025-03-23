package com.example.cote.PGMRS;

import java.util.*;
import java.util.stream.Collectors;

public class 소수_찾기 {

  private boolean isPrime(int n) {
    if (n <= 1) return false;

    for (int i = 2; i <= Math.sqrt(n); i++) if (n % i == 0) return false;

    return true;
  }

  private Set<Integer> getPrimes(int acc, List<Integer> numbers, Set<Integer> primes) {

    if (isPrime(acc)) primes.add(acc);

    for (int i = 0; i < numbers.size(); i++) {
      int nextAcc = acc * 10 + numbers.get(i);
      List<Integer> nextNumbers = new ArrayList<>(numbers);
      nextNumbers.remove(i);
      primes.addAll(getPrimes(nextAcc, nextNumbers, primes));
    }

    return primes;
  }

  private int solution(String number) {
    Set<Integer> primes = new HashSet<>();
    List<Integer> numbers = number.chars().map(c -> c - '0').boxed().collect(Collectors.toList());
    getPrimes(0, numbers, primes);
    return primes.size();
  }

  public static void main(String... args) {

    return;
  }
}
