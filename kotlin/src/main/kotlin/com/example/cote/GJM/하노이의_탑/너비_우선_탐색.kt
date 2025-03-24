package com.example.cote.GJM.하노이의_탑

import java.io.*
import java.nio.file.*
import java.util.*

object 너비_우선_탐색 {

    val MAX_DISCS = 12

    fun getState(str: String): List<Int> {
        val discs = str.trim().split(" ").filter(String::isNotEmpty)

        return if (discs.size > 0) discs.map(String::toInt) else listOf()
    }

    fun set(state: Int, col: Int, i: Int): Int {
        return (state and (3 shl (i * 2)).inv()) or (col shl (i * 2))
    }

    fun get(state: Int, i: Int): Int {
        return (state shr (i * 2)) and 3
    }

    fun translate(state: List<List<Int>>): Int {
        var ret = 0

        for ((col, column) in state.withIndex()) {
            for (i in column) {
                ret = set(ret, col, i - 1)
            }
        }

        return ret
    }

    fun dfs(initial: Int, final_: Int, n: Int): Int {
        val cost = MutableList(1 shl MAX_DISCS * 2) { -1 }
        val queue = ArrayDeque<Int>()

        queue.addLast(initial)
        cost[initial] = 0

        while (!queue.isEmpty()) {
            val cur = queue.removeFirst()

            val top = MutableList(4) { -1 }
            for (disc in n - 1 downTo 0) {
                top[get(cur, disc)] = disc
            }

            for (i in 0..3) {
                if (top[i] == -1) {
                    continue
                }

                for (j in 0..3) {
                    if (i == j || (top[j] != -1 && top[i] > top[j])) {
                        continue
                    }

                    val next = set(cur, j, top[i])

                    if (cost[next] != -1) {
                        continue
                    }

                    cost[next] = cost[cur] + 1

                    if (next == final_) {
                        return cost[next]
                    }

                    queue.addLast(next)
                }
            }
        }

        return -1
    }

    fun solve(n: Int, initial: List<List<Int>>, final_: List<List<Int>>): Int {
        val begin = translate(initial)
        val end = translate(final_)

        return dfs(begin, end, n)
    }

    fun main() {
        val reader =
            with(
                Paths.get(
                    System.getProperty("user.dir") + "/data/하노이의_탑.txt")) {
                    Files.newBufferedReader(this)
                }

        repeat(reader.readLine().toInt()) {
            val n = reader.readLine().toInt()
            val initial: List<List<Int>> =
                List(4) { getState(reader.readLine()) }

            val final: List<List<Int>> = List(4) { getState(reader.readLine()) }

            val answer = reader.readLine().toInt()
            println("$answer ${solve(n, initial, final)}")
        }
    }
}

fun main() {
    너비_우선_탐색.main()
}
