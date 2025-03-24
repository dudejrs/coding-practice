package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*

object 자전거_공장 {
    val MAX_COST_LENGTH = 1000
    val MAX_ORDER_LENGTH = 1000
    val MAX_COST_USAGE = 1000
    val MAX_COST_VALUE = 1000
    val MAX_ORDER_LIMIT = 1000
    val MAX_NUMBER_OF_ORDER = 1000

    fun solve(cost: List<List<Int>>, order: List<List<Int>>): Int {

        val maxMonth = order.maxOf { it[0] }
        val monthlyOrder = MutableList(maxMonth) { 0 }

        var need = 0
        var made = 0
        var ret = 0

        for (o in order) {
            monthlyOrder[o[0] - 1] = o[1]
            need += o[1]
        }

        repeat(cost.size - 1) {
            val limit = cost[it + 1][0] - cost[it][0]
            val price = cost[it][1]

            for ((i, mo) in monthlyOrder.withIndex()) {
                if (need == 0) break

                val products = Math.min(limit, need - made)

                ret += products * price
                made += products
                need -= mo

                if (mo == 0) continue

                val delivery = Math.min(made, mo)
                made -= delivery
                monthlyOrder[i] -= delivery
            }

            need = monthlyOrder.reduce { a, b -> a + b }
            made = 0
        }

        ret += need * cost[cost.size - 1][1]

        return ret
    }

    fun main() {
        val p = Paths.get(System.getProperty("user.dir") + "/data/자전거_공장.txt")
        val reader = Files.newBufferedReader(p)

        repeat(reader.readLine().toInt()) {
            val tokens = reader.readLine().split(" ").map(String::toInt)

            val cost = mutableListOf<List<Int>>()
            val order = mutableListOf<List<Int>>()

            repeat(tokens[0]) {
                cost.add(reader.readLine().split(" ").map(String::toInt))
            }

            repeat(tokens[1]) {
                order.add(reader.readLine().split(" ").map(String::toInt))
            }

            val answer = reader.readLine().toInt()

            println(String.format("%d %d", answer, solve(cost, order)))
        }

        reader.close()
    }
}

fun main() {
    자전거_공장.main()
}
