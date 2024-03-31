package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*

data class State( 
	val word: String,
	val step : Int
	){}

fun isConvertable(word: String, next: String): Boolean =
	IntRange(0, word.length - 1)
		.count{i -> word[i] != next[i]} == 1

fun solve(begin: String, target: String, words: List<String>): Int {
	val visited = MutableList(words.size) {false}
	val queue = ArrayDeque<State>()
	queue.add(State(begin, 0))

	while (!queue.isEmpty()) {
		val (word, step) = queue.removeFirst()

		if (word.equals(target)) {
			return step
		}

		for ((i, next) in words.withIndex()) {
			if (visited[i]) continue;
			if (isConvertable(word, next)) {
				visited[i] = true
				queue.add(State(next, step + 1))
			}
		}
	}

	return 0
}

fun main() {
	val p = Paths.get(System.getProperty("user.dir" )+ "/data/단어_변환.txt");
	val reader = Files.newBufferedReader(p);

	repeat (reader.readLine().toInt()) {
		val begin = reader.readLine()
		val target = reader.readLine()
		val words = reader.readLine().split(" ")
		val answer = reader.readLine().toInt()

		println("$answer ${solve(begin, target, words)}")
	}
}