package com.example.cote.GJM.삼각형_위의_최대_경로의_개수

import kotlin.random.*

val TEST_CASES = 10
val MAX_VALUE = 13
val MAX_N = 15

val random = Random(43)

fun solve(nums: List<List<Int>>): Int {
	val n = nums.size
	val cache = List(n) {List(n) {-1}}

	fun maximum(y: Int, x: Int): Int {
		if (y == n - 1) {
			return nums[y][x]
		}

		var ret = cache[y][x]

		if (ret != -1) {
			return ret
		}

		return Math.max(maximum(y + 1, x), maximum(y + 1, x + 1)) + nums[y][x]
	}

	fun count(y: Int, x: Int): Int{
		if (y == n - 1) {
			return 1
		}

		val left = maximum(y + 1, x)
		val right = maximum(y + 1, x + 1)

		if (left < right) {
			return count(y + 1, x + 1)
		} else if (right < left) {
			return count(y + 1, x)
		}

		return count(y + 1, x) + count(y + 1, x + 1)
	}

	return count(0, 0)
}

fun main() {
	repeat(TEST_CASES) {
		val n = random.nextInt(MAX_N - 2) + 2
		val nums = List(n) { i -> List(i + 1) {random.nextInt(MAX_VALUE)}}
		println(solve(nums))
	}
}