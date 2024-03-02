package com.example.cote.LTCD

import kotlin.random.*

val N = 15
val MAX_VALUE = 100
val TEST_CASE = 10

val random = Random(43)

fun dfs(nums: List<Int>, cur: Int, path: MutableList<Int>, ret: MutableList<List<Int>>) {
	
	ret.add(path.toList())

	for (i in cur..nums.size - 1) {
		path.add(nums[cur])
		dfs(nums, i + 1, path, ret)
		path.remove(nums[cur])
	}

}

fun solve(nums: List<Int>) : List<List<Int>> {
	val ret = mutableListOf<List<Int>>()
	val path = mutableListOf<Int>()

	dfs(nums, 0, path, ret)

	return ret
}

fun main() {
	
	repeat(TEST_CASE) {
		val n = random.nextInt(1, N)
		val nums = List(n) {
			random.nextInt(MAX_VALUE)
		}

		println(solve(nums))
	}
}