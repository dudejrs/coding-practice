package com.example.cote.KK;

import java.nio.file.*;
import java.io.*;
import java.util.*;

public class 주사위_게임_이기는_방법 {

    private static final int MAX_DICE = 10;
    private static final int MAX_NUMBER = 100;

    private static Set<Integer> maxComb;
    private static Map<Set<Integer>, Integer> cache;

    private static Set<Integer> getDisjointSet(Set<Integer> current, int n){
        
        Set<Integer> disjointSet = new HashSet<>();

        for(int i=0; i<n; i++){
            disjointSet.add(i);
        }

        disjointSet.removeAll(current);

        return disjointSet;
    }

    
    private static void search(Set<Integer> target, int[][] dice, List<Integer> outcomes ,int acc){
        if(target.isEmpty()){
            outcomes.add(acc);
            return;
        }

         int t = target.stream().findFirst().get();
         target.remove(t);
         int[] d = dice[t];

         for(int number : d){
             search(target,dice,outcomes,acc + number);
         }
         target.add(t);
    }
    
    
    private static List<Integer> getOutcomes(Set<Integer> current, int[][] dice){
        
        List<Integer> outcomes = new LinkedList<>();
        Set<Integer> target = new HashSet(current);

        search(target, dice, outcomes, 0);
        Collections.sort(outcomes);
        return outcomes;
    }

    private static int calcTotalWins(List<Integer> current, List<Integer> other){
        int total = 0;

        for(final int cur : current){
            int tmp = 0;
            for(int o : other){
                if(o >= cur) break;
                tmp++;
            }
            total += tmp;
        }

        return total;
    }

    private static int count(Set<Integer> current, int[][] dice){
        if(current.isEmpty()) return -1;

        if(cache.containsKey(current)){
            return cache.get(current);
        }

        Set<Integer> other = getDisjointSet(current, dice.length);
        List<Integer> currentOutcomes = getOutcomes(current, dice);
        List<Integer> otherOutcomes = getOutcomes(other, dice);

        int result = calcTotalWins(currentOutcomes, otherOutcomes);

        cache.put(current, result);
        cache.put(other, calcTotalWins(otherOutcomes, currentOutcomes));
        

        return result;
    }
    private static void search(Set<Integer> current ,int[][] dice){
        if(current.size() == dice.length/2){
            if(count(current, dice) > count(maxComb, dice)){
                maxComb = new HashSet(current);
            }
            return;
        }

        for(int i=0; i<dice.length; i++){
            if(current.contains(i)) continue;
            current.add(i);
            search(current, dice);
            current.remove(i);
        }

        return;
    }
    
    private static int[] solution(int[][] dice) {
        maxComb = new HashSet<>();
        cache = new HashMap<>();
        int[] answer = {};

        Set<Integer> current = new HashSet<>();
        search(current, dice);

        return maxComb.stream()
                    .mapToInt(v->v+1)
                    .toArray();
    }

    public static void main(String... args) throws IOException{
        Path p = Paths.get(System.getProperty("user.dir")+ "/data/주사위_게임_이기는_방법.txt");
        BufferedReader rd = Files.newBufferedReader(p);

        int testCases = Integer.parseInt(rd.readLine());

        while(testCases > 0){
            int diceNum = Integer.parseInt(rd.readLine());
            int[][] dice = new int[diceNum][6];

            for(int i=0; i<diceNum; i++){
                dice[i] = Arrays.stream(rd.readLine().split(" "))
                                .mapToInt(Integer::parseInt)
                                .toArray();
            }

            int[] answer = Arrays.stream(rd.readLine().split(" "))
                                .mapToInt(Integer::parseInt)
                                .toArray();

            System.out.println("[Solved] : "+Arrays.toString(solution(dice)));
            System.out.println("[Answer] : "+ Arrays.toString(answer));

            testCases --;
        }
    }
}