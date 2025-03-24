package com.example.algorithm

import kotlin.math.*
import kotlin.random.*

object 카라츠바 {

    val testCases = 10
    val N = 100
    val random = Random(43)

    fun normalize(a: MutableList<Int>) {
        a.add(0)

        for ((i, v) in a.withIndex()) {
            when {
                v < 0 -> {
                    val borrow = (abs(v) + 9) / 10
                    a[i + 1] -= borrow
                    a[i] += borrow * 10
                }
                v >= 10 -> {
                    val borrow = v / 10
                    a[i + 1] += borrow
                    a[i] = v % 10
                }
                else -> {
                    // do nothing
                }
            }
        }

        while (a.last() == 0) {
            a.removeAt(a.size - 1)
        }
    }

    fun mutliply(a: List<Int>, b: List<Int>): List<Int> {
        val ret = MutableList(a.size + b.size + 1) { 0 }

        for ((i, n1) in a.withIndex()) {
            for ((j, n2) in b.withIndex()) {
                ret[i + j] += n1 * n2
            }
        }

        normalize(ret)

        return ret
    }

    fun List<Int>.add(other: List<Int>, k: Int): List<Int> {

        val ret = this.toMutableList()

        if (ret.size < other.size + k) {
            repeat(other.size + k - ret.size) { ret.add(0) }
        }

        for ((i, num) in other.withIndex()) {
            ret[i + k] += num
        }

        normalize(ret)

        return ret
    }

    fun List<Int>.sub(other: List<Int>): List<Int> {
        if (this.size < other.size) {
            throw UnsupportedOperationException()
        }

        val ret = this.toMutableList()

        for ((i, num) in other.withIndex()) {
            ret[i] -= num
        }

        normalize(ret)

        return ret
    }

    fun karatsuba(a: List<Int>, b: List<Int>): List<Int> {

        if (a.size == 0 || b.size == 0) return listOf(0)
        if (a.size < b.size) return karatsuba(b, a)
        if (a.size <= 50) return mutliply(a, b)

        val half: Int = a.size / 2
        val a0 = a.subList(0, half)
        val a1 = a.subList(half, a.size)
        val b0 = b.subList(0, min(half, b.size))
        val b1 = b.subList(min(half, b.size), b.size)

        val z2 = karatsuba(a1, b1)
        val z0 = karatsuba(a0, b0)

        val x1 = a1.add(a0, 0)
        val x2 = b1.add(b0, 0)

        val z1 = karatsuba(x1, x2)

        val ret = z0.add(z1, half)

        return ret.add(z2, half * 2)
    }

    fun main() {
        repeat(testCases) {
            val a = List(random.nextInt(1, N)) { random.nextInt(1, 9) }
            val b = List(random.nextInt(1, N)) { random.nextInt(1, 8) }
            println(
                "${a.asReversed().joinToString("")} * ${b.asReversed().joinToString("")} = ${karatsuba(a,b).asReversed().joinToString("")}")
        }
    }
}

fun main() {
    카라츠바.main()
}
