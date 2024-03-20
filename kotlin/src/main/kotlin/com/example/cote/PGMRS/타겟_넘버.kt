package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*
import kotlin.collections.*
import kotlin.random.*

val MAX_NUMBERS_LENTH = 20
val MAX_NUMBER_VALUE = 50
val MAX_TARGET_VALUE = 100

val TEST_CASES = 10
val random = Random(43)

data class State (
	val idx: Int,
	val acc: Int
	) {
}

fun solve(numbers: List<Int>, target: Int): Int {
	val stack = ArrayDeque<State>()
	stack.addLast(State(0, 0))

	var count = 0;
	while (stack.size > 0) {
		val (idx, acc) = stack.removeLast()

		if (idx == numbers.size) {
			if (acc == target) {
				count++ 
			}
			continue;
		} 
				
		stack.addLast(State(idx + 1, acc + numbers[idx]))
		stack.addLast(State(idx + 1, acc - numbers[idx]))
	}

	return count
}

fun main() {
	val p = Paths.get(System.getProperty("user.dir") + "/data/타겟_넘버.txt");
	val reader = Files.newBufferedReader(p);

	repeat(reader.readLine().toInt()) {
		val numbers = reader.readLine().split(" ")
			.map(String::toInt)
		val target = reader.readLine().toInt()
		val answer = reader.readLine().toInt()
		val solved = solve(numbers, target)

		if (solved != answer) {
			println("$answer $solved")
			return
		}
	}

	repeat(TEST_CASES) {
		val numbers = IntRange(1, random.nextInt(MAX_NUMBERS_LENTH - 1) + 1)
			.map{
				random.nextInt(MAX_NUMBER_VALUE)
			}
		val target = random.nextInt(MAX_TARGET_VALUE)
		println("${solve(numbers, target)}")
	}
}