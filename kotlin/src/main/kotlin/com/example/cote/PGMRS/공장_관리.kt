package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*

val BENFIT_PER_ONE = 10000

fun totalProduces(durations: List<Int>, time: Int): Int 
	= durations.map{
		time / it
	}.sum()

fun searchFinishedTime(goal: Int, durations: List<Int>): Int {
	val maxDuration = durations.max();
	var lo = 0
	var hi = maxDuration * goal

	while (lo + 1 < hi) {
		val mid: Int = (lo + hi) / 2

		if (goal <= totalProduces(durations, mid)) {
			hi = mid
		} else {
			lo = mid
		}
	}

	return hi
}

fun calcBenefitAmount(durations:List<Int>, finishedTime: Int): Int {
	val min = finishedTime / durations.max() 

	return durations.map {
		finishedTime / it - min 
	}.sum() * BENFIT_PER_ONE
}

// 목표 생산 수와 하나를 생산하는데 걸리는 시간이 주어졌을 때, 준비해야 하는 성과금 금액을 반환
fun solve(goal: Int, durations: List<Int>): Int {
	val time = searchFinishedTime(goal, durations)
	println(time)
	return calcBenefitAmount(durations, time)
} 

fun main() {
	val p = Paths.get(System.getProperty("user.dir") + "/data/공장_관리.txt")
	val reader = Files.newBufferedReader(p)

	repeat(reader.readLine().toInt()) {
		val goal = reader.readLine().toInt()
		val durations = reader.readLine().split(" ")
			.map(String::toInt)
		val answer = reader.readLine().toInt()
		println("$answer ${solve(goal, durations)}")	
	}
}