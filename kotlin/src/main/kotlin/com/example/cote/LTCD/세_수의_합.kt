package com.example.cote.LTCD

import java.util.*

object 세_수의_합 {

    val TEST_CASE = 10
    val N = 10000
    val random = Random(43)

    fun search(target: Int, nums: List<Int>): List<List<Int>> {
        val ret = mutableListOf<List<Int>>()

        var left = target + 1
        var right = nums.size - 1

        while (left < right) {
            val sum = nums[target] + nums[left] + nums[right]

            when {
                sum > 0 -> right--
                sum < 0 -> left++
                else -> {
                    ret.add(listOf(nums[target], nums[left], nums[right]))

                    while (left < right && nums[left] == nums[left + 1]) {
                        left++
                    }

                    while (left < right && nums[right] == nums[right - 1]) {
                        right--
                    }
                    left++
                    right--
                }
            }
        }

        return ret
    }

    fun solve(nums: List<Int>): List<List<Int>> {
        val ret = mutableListOf<List<Int>>()

        for (target in 1..nums.size - 2) {
            if (target > 0 && nums[target] == nums[target - 1]) {
                continue
            }

            if (nums[target] >= 0) {
                break
            }

            val searched = search(target, nums)

            ret.addAll(searched)
        }

        return ret
    }

    fun main() {
        for (it in 1..TEST_CASE) {
            val n = random.nextInt(N - 1) + 1
            val nums =
                List(n) { random.nextInt(N) - Math.floorDiv(N, 2) }
                    .distinct()
                    .sorted()
            println(solve(nums))
        }
    }
}

fun main() {
    세_수의_합.main()
}
