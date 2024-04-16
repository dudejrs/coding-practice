package com.example.cote.PGMRS;

import kotlin.math.*
import kotlin.random.Random

val MAX_QUERIES_LENGTH = 5
val MAX_GENEATION = 16

val TEST_CASES = 10
val random = Random(43)

fun gen(n: Int) = (4.0).pow(n - 1).toInt()

fun Random.nextQueryLength(): Int 
	= nextInt(MAX_QUERIES_LENGTH - 1) + 1

fun Random.nextQuery(): Pair<Int, Int> {
	val generation = nextInt(MAX_GENEATION - 2) + 2
	val number = nextInt(gen(generation))
	return Pair(generation, number)
}

fun find(generation: Int,  number: Int): String {
	if (generation == 1) {
		return "Rr"
	}

	val chunk = gen(generation - 1)

	return when (number / chunk) {
		0 -> "RR"
		3 -> "rr"
		else -> find(generation - 1, number % chunk)
	}
}

fun solve(queries: List<Pair<Int, Int>>): List<String> {
	return queries.map{(generation, number) -> 
		find(generation, number)
	}
}

fun main() {

	repeat(TEST_CASES) {
		val queries = List(random.nextQueryLength()) {
			random.nextQuery()
		}
		println(solve(queries))
	}
}