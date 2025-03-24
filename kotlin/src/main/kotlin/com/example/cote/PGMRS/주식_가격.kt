package com.example.cote.PGMRS

import java.util.*
import kotlin.random.*

object 주식_가격 {

    val TEST_CASES = 10
    val MAX_PRICES_LENGTH = 10000
    val MAX_PRICES_VALUE = 10000

    val random = Random(43)

    // 가격이 떨어지지 않은 기간을 남은 배열을 반환
    fun solve(prices: List<Int>): List<Int> {
        val ret = MutableList<Int>(prices.size) { 0 }
        val stack = Stack<Int>()

        for ((i, price) in prices.withIndex()) {

            while (!stack.isEmpty()) {
                val top = stack.peek()
                if (prices[top] <= price) {
                    break
                }
                ret[top] = i - top
                stack.pop()
            }
            stack.push(i)
        }

        while (!stack.isEmpty()) {
            val top = stack.pop()
            ret[top] = prices.size - 1 - top
        }

        return ret
    }

    fun main() {
        repeat(TEST_CASES) {
            val prices =
                List(random.nextInt(MAX_PRICES_LENGTH)) {
                    random.nextInt(MAX_PRICES_VALUE)
                }
            println(solve(prices))
        }
    }
}

fun main() {
    주식_가격.main()
}
