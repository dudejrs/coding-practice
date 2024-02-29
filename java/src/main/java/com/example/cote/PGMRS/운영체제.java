package com.example.cote.PGMRS;

import java.util.*;
import java.io.*;
import java.nio.file.*;
import java.util.stream.Collectors;

public class 운영체제 {
	private static final int MAX_PROGRAMS_LENGTH = 100000;
	private static final int MAX_PRIORITY = 10;
	private static final int MAX_TIMES = 10000000;
	private static final int MAX_RUNTIMES = 1000;

	private static class Result{

		public int completedTime;
		public int[] totalWaitedTimes = new int[10];

		Result(){}

		Result(int completedTime, int[] totalWaitedTimes) {
			this.completedTime = completedTime;
			this.totalWaitedTimes = totalWaitedTimes;
		}

		@Override 
		public String toString() {
			return String.format("(%d) %s", completedTime, Arrays.toString(totalWaitedTimes));
		}
	}
	private static record Program( 
		int priority,
		int calledAt,
		int executionTime
	){}


	private static Result solve(int[][] programs) {
		Queue<Program> queue = Arrays.stream(programs)
			.map(p -> new Program(p[0], p[1], p[2]))
			.sorted(Comparator.comparingInt(Program::calledAt))
			.collect(Collectors.toCollection(LinkedList::new));

		PriorityQueue<Program> pq = new PriorityQueue<>((a, b) -> {
			if (a.priority() != b.priority()) {
				return a.priority() - b.priority();
			}
			return a.calledAt() - b.calledAt();
		});

		Result ret = new Result();
		int time = 0;

		while (!queue.isEmpty() || !pq.isEmpty()) {
			while (!queue.isEmpty() && time >= queue.peek().calledAt()) {
				pq.add(queue.poll());
			}

			if (pq.isEmpty()) {
				time = queue.peek().calledAt();
				continue;
			}

			Program p = pq.poll();
			ret.totalWaitedTimes[p.priority()] += time - p.calledAt();
			time += p.executionTime();
		}
		ret.completedTime = time;
			
		return ret;
	}

	public static void main(String... args) throws IOException {
		Path p = Paths.get(System.getProperty("user.dir") + "/data/운영체제.txt");
		BufferedReader reader = Files.newBufferedReader(p);

		int testCases = Integer.parseInt(reader.readLine());

		while (testCases > 0) {
			int numPrograms = Integer.parseInt(reader.readLine());


			int[][] programs = new int[numPrograms][3];

			int[] priorities = Arrays.stream(reader.readLine().split(" "))
					.mapToInt(Integer::parseInt)
					.toArray();

			int[] times = Arrays.stream(reader.readLine().split(" "))
					.mapToInt(Integer::parseInt)
					.toArray();

			int[] runtimes = Arrays.stream(reader.readLine().split(" "))
					.mapToInt(Integer::parseInt)
					.toArray();

			for (int i = 0; i < numPrograms; i++) {
				programs[i][0] = priorities[i] - 1; 
				programs[i][1] = times[i]; 
				programs[i][2] = runtimes[i]; 
			}

			Result answer = new Result();

			answer.completedTime = Integer.parseInt(reader.readLine());
			answer.totalWaitedTimes = Arrays.stream(reader.readLine().split(" "))
				.mapToInt(Integer::parseInt)
				.toArray();

			Result solved = solve(programs);

			System.out.println("answer : " + answer);
			System.out.println("solved : " + solved);

			testCases--;
		}
	}
}