package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*
import java.util.*

object 운영체제 {

    val MAX_PROGRAMS_LENGTH = 100000
    val MAX_PRIORIRY = 10
    val MAX_TIMES = 1000000
    val MAX_RUNTIMES = 1000

    data class Answer(
        val completedTime: Int = 0,
        val totalWaitedTimes: Array<Int> = Array(MAX_PRIORIRY) { 0 }
    )

    data class Program(val priority: Int, val time: Int, val runtime: Int)

    fun solve(programs: List<Array<Int>>): Answer {
        val sortedPrograms =
            programs
                .map { Program(it[0] - 1, it[1], it[2]) }
                .sortedBy(Program::time)

        val q = ArrayDeque<Program>(sortedPrograms)

        val pq =
            PriorityQueue<Program>(compareBy(Program::priority, Program::time))

        var current = 0
        val waitedTimes = Array<Int>(MAX_PRIORIRY) { 0 }

        while (!q.isEmpty() || !pq.isEmpty()) {

            while (!q.isEmpty() && q.first().time <= current) {
                pq.offer(q.removeFirst())
            }

            if (pq.isEmpty()) {
                current = q.peek().time
                continue
            }

            val (priority, time, runtime) = pq.poll()
            waitedTimes[priority] += current - time
            current += runtime
        }

        return Answer(current, waitedTimes)
    }

    fun main() {
        val reader =
            with(Paths.get(System.getProperty("user.dir") + "/data/운영체제.txt")) {
                Files.newBufferedReader(this)
            }

        repeat(reader.readLine().toInt()) {
            val numPrograms = reader.readLine().toInt()
            val programs = MutableList(numPrograms) { Array<Int>(3) { 0 } }
            val priorities = reader.readLine().split(" ").map(String::toInt)
            val times = reader.readLine().split(" ").map(String::toInt)
            val runtimes = reader.readLine().split(" ").map(String::toInt)

            for (i in 0..numPrograms - 1) {
                programs[i] = arrayOf(priorities[i], times[i], runtimes[i])
            }

            val completedTime = reader.readLine().toInt()
            val totalWaitedTimes =
                reader.readLine().split(" ").map(String::toInt).toTypedArray()
            val answer = Answer(completedTime, totalWaitedTimes)
            println(answer)
            println(solve(programs))
            println()
        }
    }
}

fun main() {
    운영체제.main()
}
