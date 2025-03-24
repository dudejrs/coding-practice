package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*
import kotlin.random.*

object 네트워크 {
    val TEST_CASES = 10
    val N = 20
    val random = Random(43)

    fun dfs(
        cur: Int,
        visited: MutableList<Boolean>,
        computers: List<List<Int>>
    ) {
        visited[cur] = true

        for ((i, v) in computers[cur].withIndex()) {
            if (!visited[i] && v == 1) {
                dfs(i, visited, computers)
            }
        }
    }

    fun solve(computers: List<List<Int>>): Int {
        val visited = MutableList(computers.size) { false }
        var count = 0
        for (i in 0..computers.size - 1) {
            if (!visited[i]) {
                dfs(i, visited, computers)
                count++
            }
        }

        return count
    }

    fun main() {
        val p = Paths.get(System.getProperty("user.dir") + "/data/네트워크.txt")
        val reader = Files.newBufferedReader(p)

        repeat(reader.readLine().toInt()) {
            val numComputer = reader.readLine().toInt()
            val computers =
                IntRange(1, numComputer).map {
                    reader.readLine().split(" ").map(String::toInt)
                }
            val answer = reader.readLine().toInt()

            if (answer != solve(computers)) {
                println("$answer ${solve(computers)}")
                return
            }
        }

        repeat(TEST_CASES) {
            val computers =
                List(N) { i ->
                    val ret =
                        MutableList(N) { j ->
                            if (i == j || random.nextInt(100) > 90) 1 else 0
                        }
                    ret
                }

            println("${solve(computers)}")
        }
    }
}

fun main() {
    네트워크.main()
}
