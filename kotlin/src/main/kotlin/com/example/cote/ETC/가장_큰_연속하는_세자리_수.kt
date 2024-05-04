package com.example.cote.ETC

import kotlin.random.*

val TEST_CASES = 10
val random = Random(43)
val N = 1000


fun Random.numberString(): String {
	val n = nextInt(N - 1) + 1
	return List(n) {
		nextInt(9) + 1
	}.joinToString("")
}

fun find(s: String, i: Int): Boolean = s.indexOf("$i$i$i") != -1

fun solve(s: String): Int {

	if (s.length < 3) {
		return -1
	}

	for (i in 9 downTo 1) {
		if (find(s, i)) {
			return "$i$i$i".toInt()
		}
	}

	if (find(s, 0)) {
		return 0
	}

	return -1
}

fun main() {
	repeat(TEST_CASES) {
		println(solve(random.numberString()))
	}
}