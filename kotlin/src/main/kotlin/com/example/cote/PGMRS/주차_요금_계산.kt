package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*

object 주차_요금_계산 {

    val MAX_BASIC_TIME = 1439
    val MAX_BASIC_FEE = 100000
    val MAX_UNIT_TIME = 1439
    val MAX_UNIT_FEE = 10000
    val MAX_RECORDS_LENGTH = 1000

    data class Fee(
        val baseTime: Int,
        val baseFee: Int,
        val unitTime: Int,
        val unitFee: Int
    ) {

        constructor(
            fees: Array<Int>
        ) : this(fees[0], fees[1], fees[2], fees[3]) {}

        fun cost(time: Int): Int {
            var ret = baseFee
            var curTime = time - baseTime

            while (curTime > 0) {
                ret += unitFee
                curTime -= unitTime
            }

            return ret
        }
    }

    class Car(val number: String, val fee: Fee) {

        private var inTime: Int = -1
        private var totalTime: Int = 0
        val cost: Int
            get() {
                return fee.cost(totalTime)
            }

        fun enter(time: Int) {
            inTime = time
        }

        fun leave(time: Int) {
            if (inTime == -1) return
            totalTime += time - inTime
            inTime = -1
        }
    }

    fun parseTime(time: String): Int {
        val hour = time.substring(0..1).toInt()
        val minute = time.substring(3..4).toInt()
        return hour * 60 + minute
    }

    fun solve(fees: Array<Int>, records: Array<String>): Array<Int> {
        val fee = Fee(fees)
        val cars = mutableMapOf<String, Car>()

        for (record in records) {
            val tokens = record.split(" ")
            val time = parseTime(tokens[0])

            val car = cars.getOrDefault(tokens[1], Car(tokens[1], fee))

            when (tokens[2]) {
                "IN" -> car.enter(time)
                "OUT" -> car.leave(time)
                else -> {}
            }

            cars[tokens[1]] = car
        }

        val endTime = parseTime("23:59")

        for (car in cars.values) {
            car.leave(endTime)
        }

        return cars.values.sortedBy(Car::number).map(Car::cost).toTypedArray()
    }

    fun main() {
        val p = Paths.get(System.getProperty("user.dir") + "/data/주차_요금_계산.txt")
        val reader = Files.newBufferedReader(p)

        repeat(reader.readLine().toInt()) {
            val fees =
                reader.readLine().split(" ").map(String::toInt).toTypedArray()

            val numRecords = reader.readLine().toInt()

            val records =
                IntRange(1, numRecords).map { reader.readLine() }.toTypedArray()

            val answer =
                reader.readLine().split(" ").map(String::toInt).toTypedArray()

            println(
                "${answer.contentToString()} ${solve(fees, records).contentToString()}")
        }
    }
}

fun main() {
    주차_요금_계산.main()
}
