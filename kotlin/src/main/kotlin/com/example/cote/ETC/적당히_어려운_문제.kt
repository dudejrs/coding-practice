package com.example.cote.ETC

import java.util.*
import kotlin.random.*

object 적당히_어려운_문제 {

    val TEST_CASES = 10
    val N = 20
    val MAX_LEVEL = N * 2

    val random = Random(43)

    fun solve(levels: List<Int>): Int {
        if (levels.size < 4) {
            return -1
        }

        val minHeap = PriorityQueue<Int>()
        val maxHeap = PriorityQueue<Int>(reverseOrder<Int>())

        /*
        	1. maxHeap.size >= minHeap.size * 3
        	2. maxHeap.top <= minQueue.top
        */
        for (level in levels) {
            if (maxHeap.size <= minHeap.size * 3) {
                maxHeap.offer(level)
            } else {
                minHeap.offer(level)
            }

            if (maxHeap.isEmpty() || minHeap.isEmpty()) {
                continue
            }

            if (maxHeap.peek() > minHeap.peek()) {
                val a = maxHeap.poll()
                val b = minHeap.poll()

                minHeap.offer(a)
                maxHeap.offer(b)
            }
        }

        return minHeap.peek()
    }

    fun main() {
        repeat(TEST_CASES) {
            val levels =
                with(random.nextInt(N - 1) + 1) {
                    List(this) { random.nextInt(MAX_LEVEL) }
                }

            println("${levels.sorted()} ${solve(levels)}")
        }
    }
}

fun main() {
    적당히_어려운_문제.main()
}
