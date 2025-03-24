package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*
import kotlin.random.*

object 체육복 {
    val MAX_N = 30
    val TEST_CASES = 10

    val random = Random(43)

    fun solve(n: Int, lost: List<Int>, reserve: List<Int>): Int {

        val lostAndReserve = lost.toSet().run { intersect(reserve.toSet()) }

        val lostAndNotReserve = lost.toSet().run { subtract(reserve.toSet()) }

        val helpee = ArrayDeque<Int>(lostAndNotReserve)

        var borrower = 0

        for (helper in reserve) {
            if (lostAndReserve.contains(helper)) {
                continue
            }

            while (!helpee.isEmpty() && helpee.first() < helper - 1) {
                helpee.removeFirst()
            }

            if (helpee.isEmpty()) {
                break
            }

            if (helpee.first() <= helper + 1) {
                helpee.removeFirst()
                borrower++
            }
        }

        return n - lost.size + borrower
    }

    fun main() {
        val reader =
            with(Paths.get(System.getProperty("user.dir") + "/data/체육복.txt")) {
                Files.newBufferedReader(this)
            }

        repeat(reader.readLine().toInt()) {
            val n = reader.readLine().toInt()
            val lost = reader.readLine().split(" ").map(String::toInt)
            val reserve = reader.readLine().split(" ").map(String::toInt)
            val answer = reader.readLine().toInt()

            println("$answer ${solve(n, lost, reserve)}")
        }

        repeat(TEST_CASES) {
            val n = random.nextInt(MAX_N - 2) + 2
            val lost = IntRange(1, n).filter { random.nextFloat() < 0.5 }
            val reserve = IntRange(1, n).filter { random.nextFloat() < 0.2 }
            println("$n ${solve(n, lost, reserve)}")
        }
    }
}

fun main() {
    체육복.main()
}
