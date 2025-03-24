package com.example.cote.GJM

import java.io.*
import java.nio.file.*

object 알러지가_심한_친구들 {

    val N = 20
    val M = 20
    val INF = 987654321
    var best = INF

    fun search(
        eater: List<List<Int>>,
        canEat: List<List<Int>>,
        edible: MutableList<Int>,
        n: Int,
        m: Int,
        chosen: Int
    ) {

        if (chosen >= best) {
            return
        }

        val allSelected = edible.all { it > 0 }

        if (allSelected) {
            best = Math.min(best, chosen)
            return
        }

        val cur = edible.withIndex().filter { it.value == 0 }.first().index

        for (food in canEat[cur]) {

            for (person in eater[food]) {
                edible[person] += 1
            }

            search(eater, canEat, edible, n, m, chosen + 1)

            for (person in eater[food]) {
                edible[person] -= 1
            }
        }
    }

    fun solve(
        eater: List<List<Int>>,
        canEat: List<List<Int>>,
        n: Int,
        m: Int
    ): Int {
        best = INF

        search(eater, canEat, MutableList(n) { 0 }, n, m, 0)

        return best
    }

    fun main() {
        val p =
            Paths.get(System.getProperty("user.dir") + "/data/알러지가_심한_친구들.txt")
        val reader = Files.newBufferedReader(p)

        repeat(reader.readLine().toInt()) {
            val l = reader.readLine().split(" ").map(String::toInt)
            val n = l[0]
            val m = l[1]

            val person = listOf(*reader.readLine().split(" ").toTypedArray())
            val eater = List(m) { mutableListOf<Int>() }
            val canEat = List(n) { mutableListOf<Int>() }
            repeat(m) {
                val token =
                    reader
                        .readLine()
                        .trim()
                        .split(" ")
                        .drop(1)
                        .map(person::indexOf)

                eater[it].addAll(token)

                for (v in token) {
                    canEat[v].add(it)
                }
            }

            println(solve(eater, canEat, n, m))
        }

        reader.close()
    }
}

fun main() {
    알러지가_심한_친구들.main()
}
