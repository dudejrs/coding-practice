package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*
import kotlin.random.*

object 단속_카메라 {
    val MAX_CARS = 10000
    val MIN_ENTRY = -30000
    val MAX_ENTRY = 30000
    val TEST_CASES = 10

    val random = Random(43)

    fun solve(routes: Array<Array<Int>>): Int {

        routes.sortBy { it[1] }

        var last = 0
        var count = 0

        for (route in routes) {
            if (route[0] <= last && last <= route[1]) {
                continue
            }
            last = route[1]
            count++
        }

        return count
    }

    fun main() {
        val p = Paths.get(System.getProperty("user.dir") + "/data/단속_카메라.txt")
        val reader = Files.newBufferedReader(p)

        repeat(reader.readLine().toInt()) {
            val n = reader.readLine().toInt()
            val routes =
                IntRange(1, n)
                    .map {
                        reader
                            .readLine()
                            .split(" ")
                            .map(String::toInt)
                            .toTypedArray()
                    }
                    .toTypedArray()

            val answer = reader.readLine().toInt()
            println("$answer ${solve(routes)}")
        }

        repeat(TEST_CASES) {
            val n = random.nextInt(MAX_CARS)
            val routes =
                IntRange(1, n)
                    .map {
                        val end =
                            random.nextInt(MAX_ENTRY - MIN_ENTRY) + MIN_ENTRY
                        val start = random.nextInt(end - MIN_ENTRY) + MIN_ENTRY
                        arrayOf(start, end)
                    }
                    .toTypedArray()
            println(solve(routes))
        }
    }
}

fun main() {
    단속_카메라.main()
}
