package com.example.cote.GJM

import kotlin.random.*
import kotlin.Comparator

val MAX_LENGTH = 100
val MIN_LENGTH = 10

val TEST_CASE = 10

class Comp(
	val group: List<Int>,
	val t: Int
	) : Comparator<Int> {

	override fun compare(a: Int, b: Int): Int {
		if (group[a] != group[b]) {
			return group[a] - group[b]
		}
		return group[a + t] - group[b + t]
	} 
}


fun Random.nextChar(): Char = Char(nextInt('a'.code, 'c'.code))

fun initialize(random: Random): String {

	val n = random.nextInt(MAX_LENGTH - MIN_LENGTH) + MIN_LENGTH

	return buildString {
		repeat(n) {
			append(random.nextChar())
		}
	}
}

fun getSuffixArray(target: String): List<Int> {
	var n = target.length
	var t = 1
	var group = MutableList(n) {target[it].code} .apply {
		add(-1)
	}
	val perm = MutableList(n) {it}

	while (t < n) {
		val comp = Comp(group, t)
		perm.sortWith(comp)
		
		t *= 2
		val newgroup = MutableList(n) {0} .apply {
			repeat(t) {
				add(-1)
			}
		}

		for (i in 1..n-1) {
			if (comp.compare(i, i-1) < 0) {
				newgroup[perm[i]] = newgroup[perm[i - 1]] + 1
			} else {
				newgroup[perm[i]] = newgroup[perm[i - 1]]
			}
		}

		group = newgroup

	} 

	return perm
}

// 원형 문자열으로 만들 수 있는 문자열 중 사전순으로 가장 앞에 오는 문자열을 반환
fun solve(target: String): String {
	val newTarget = target + target
	val perm = getSuffixArray(newTarget)

	for (i in perm) {
		if (i < target.length) {
			return newTarget.substring(i, i + target.length)
		}
	}

	return ""
}

fun main() {
	val random = Random(43)

	repeat(TEST_CASE) {
		val target = initialize(random)
		println("${solve(target)}")
	}
}