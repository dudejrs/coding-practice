package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*
import java.util.*

object 다리를_지나는_트럭 {

    val MAX_BRIDGE_LENGTH = 10000
    val MAX_WEIGHT = 10000
    val MAX_TRUCT_WIEGHTS_LENGTH = 10000

    fun solve(bridgeLength: Int, weight: Int, truckWeights: Array<Int>): Int {

        val bridge = ArrayDeque(List(bridgeLength) { 0 })
        var bridgeWeight = 0
        var cur = 0
        var count = 0

        while (cur < truckWeights.size) {

            bridgeWeight -= bridge.removeFirst()

            if (bridgeWeight + truckWeights[cur] <= weight) {
                bridge.addLast(truckWeights[cur])
                bridgeWeight += truckWeights[cur]
                cur++
            } else {
                bridge.addLast(0)
            }

            count++
        }

        while (bridgeWeight > 0) {
            bridgeWeight -= bridge.removeFirst()
            count++
        }

        return count
    }

    fun main() {
        val p =
            Paths.get(System.getProperty("user.dir") + "/data/다리를_지나는_트럭.txt")
        val reader = Files.newBufferedReader(p)

        repeat(reader.readLine().toInt()) {
            val bridgeLength = reader.readLine().toInt()
            val weight = reader.readLine().toInt()
            val truckWeights =
                reader.readLine().split(" ").map(String::toInt).toTypedArray()
            val answer = reader.readLine().toInt()

            println("solved: " + solve(bridgeLength, weight, truckWeights))
            println("answer: " + answer)
        }

        reader.close()
    }
}

fun main() {
    다리를_지나는_트럭.main()
}
