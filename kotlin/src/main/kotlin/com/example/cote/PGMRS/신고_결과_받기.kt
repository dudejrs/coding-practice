package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*

object 신고_결과_받기 {
    data class Record(val reporter: String, val accused: String)

    fun solve(
        idList: List<String>,
        records: List<List<String>>,
        k: Int
    ): List<Int> {

        val reportsById = mutableMapOf<String, MutableSet<String>>()
        val counts = mutableMapOf<String, Int>()
        val reports = records.map { Record(it[0], it[1]) }

        for ((reporter, accused) in reports) {
            val accusedByReporter =
                reportsById[reporter] ?: mutableSetOf<String>()

            if (accused in accusedByReporter) {
                continue
            }

            accusedByReporter.add(accused)
            reportsById[reporter] = accusedByReporter
            counts[accused] = (counts[accused] ?: 0) + 1
        }

        val banned =
            counts
                .asSequence()
                .filter { it -> it.value >= k }
                .map { it.key }
                .toSet()

        return idList.map { id ->
            reportsById[id]?.filter { it: String -> it in banned }?.size ?: 0
        }
    }

    fun main() {
        val reader =
            with(
                Paths.get(
                    System.getProperty("user.dir") + "/data/신고_결과_받기.txt")) {
                    Files.newBufferedReader(this)
                }

        repeat(reader.readLine().toInt()) {
            val idList = reader.readLine().split(" ")
            val records =
                IntRange(1, reader.readLine().toInt()).map {
                    reader.readLine().split(" ")
                }
            val k = reader.readLine().toInt()
            val answer = reader.readLine().split(" ").map(String::toInt)
            println("$answer ${solve(idList, records, k)}")
        }
    }
}

fun main() {
    신고_결과_받기.main()
}
