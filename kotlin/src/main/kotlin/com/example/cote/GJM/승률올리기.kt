package com.example.cote.GJM

import java.io.*
import java.nio.file.*


fun decision(n: Long, k: Long, ratio: Int): Boolean {
	return Math.floorDiv(k * 100, n) > ratio
}

fun solve(n: Long, k: Long): Long {
	var lo = 0L
	var hi = n
	val ratio = Math.floorDiv(k * 100, n).toInt()

	if (ratio == 100) {
		return -1
	}

	while (lo + 1 < hi) {
		val mid = Math.floorDiv(lo + hi, 2)

		if (decision(n + mid, k + mid, ratio)) {
			hi = mid
		} else {
			lo = mid
		}
	}

	return hi
}

fun main() {

	val p = Paths.get(System.getProperty("user.dir") + "/data/승률올리기.txt")
	val reader = Files.newBufferedReader(p)

	repeat(reader.readLine().toInt()) {
		val numbers = reader.readLine().split(" ")
			.map{
				it.toLong()
			}

		println(solve(numbers[0], numbers[1]))
	}
}