package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*

object 사칙연산 {

    val MIN_ARRAY_LEGNTH = 3
    val MAX_ARRAY_LENGTH = 201
    val MIN_NUMBER_SIZE = 1000

    enum class Operator(val symbol: Char) {
        PLUS('+'),
        MINUS('-');

        val initValue: Int
            get() {
                return when (symbol) {
                    '+' -> Int.MIN_VALUE
                    '-' -> Int.MAX_VALUE
                    else -> 0
                }
            }

        fun compare(a: Int, b: Int): Int {
            return when (symbol) {
                '+' -> a.compareTo(b)
                '-' -> b.compareTo(a)
                else -> 0
            }
        }
    }

    val cache =
        Array(MAX_ARRAY_LENGTH + 1) {
            Array(MAX_ARRAY_LENGTH + 1) {
                IntArray(Operator.values().size) { Int.MIN_VALUE }
            }
        }

    fun compute(start: Int, end: Int, type: Operator, tokens: String): Int {
        var ret = cache[start][end][type.ordinal]

        if (ret != Int.MIN_VALUE) {
            return ret
        }

        if (start == end - 1) {
            return Character.getNumericValue(tokens[start])
        }

        ret = type.initValue

        for (i in start + 1 until end - 1 step 2) {
            val left = compute(start, i, type, tokens)
            var value = left

            when (tokens[i]) {
                Operator.PLUS.symbol -> {
                    val right = compute(i + 1, end, Operator.PLUS, tokens)
                    value += right
                }
                Operator.MINUS.symbol -> {
                    val right = compute(i + 1, end, Operator.MINUS, tokens)
                    value -= right
                }
                else -> {}
            }

            if (type.compare(value, ret) > 0) {
                ret = value
            }
        }

        cache[start][end][type.ordinal] = ret
        return ret
    }

    fun solve(tokens: String): Int {

        for (outer in cache) {
            for (inner in outer) {
                inner.fill(Int.MIN_VALUE)
            }
        }

        return compute(0, tokens.length, Operator.PLUS, tokens)
    }

    fun main() {
        val p = Paths.get(System.getProperty("user.dir") + "/data/사칙연산.txt")
        val reader = Files.newBufferedReader(p)

        repeat(reader.readLine().toInt()) {
            val tokens = reader.readLine()
            val answer = reader.readLine().toInt()
            println("$answer ${solve(tokens)}")
        }
    }
}

fun main() {
    사칙연산.main()
}
