package com.example.cote.GJM

import java.util.*
import kotlin.random.*

object k번째_최대증가부분수열 {

    val TEST_CASE = 10
    val M = 20
    val MAX_VALUE = 100
    val MAX = 200000000
    val K = 3

    val random = Random(43)

    val cache = MutableList(M + 1) { -1 }
    val counts = MutableList(M + 1) { -1 }

    fun searchMax(cur: Int, v: List<Int>): Int {

        if (cur == v.size) {
            return 1
        }

        var ret = cache[cur + 1]

        if (ret != -1) {
            return ret
        }

        ret = 0

        for (i in cur + 1..v.size - 1) {
            if (cur == -1 || v[cur] < v[i]) {
                ret = Math.max(ret, searchMax(i, v) + 1)
            }
        }

        cache[cur + 1] = ret

        return ret
    }

    fun count(cur: Int, v: List<Int>): Int {
        // if (searchMax(cur, v) == 1){
        // 	return 1
        // }

        var ret = counts[cur + 1]

        if (ret != -1) {
            return ret
        }

        ret = 0

        for (i in cur + 1..v.size - 1) {
            if (cur == -1 || v[cur] < v[i]) {
                if (searchMax(cur, v) == searchMax(i, v) + 1) {
                    ret = Math.min(MAX, ret + count(i, v))
                }
            }
        }

        counts[cur + 1] = ret

        return ret
    }

    fun reconstruct(cur: Int, k: Int, v: List<Int>, ret: MutableList<Int>) {

        if (cur != -1) {
            ret.add(v[cur])
        }

        val followers = mutableListOf<Pair<Int, Int>>()

        for (i in cur + 1..v.size - 1) {
            if (cur == -1 || v[cur] < v[i]) {
                if (searchMax(cur, v) == searchMax(i, v) + 1) {
                    followers.add(Pair(v[i], i))
                }
            }
        }

        followers.sortBy { it.first }

        var skip = k

        for ((_, i) in followers) {
            val cnt = count(i, v)

            if (cnt <= skip) {
                skip -= cnt
            } else {
                reconstruct(i, skip, v, ret)
                break
            }
        }
    }

    fun solve(v: List<Int>, k: Int): List<Int> {
        cache.fill(-1)
        counts.fill(-1)

        searchMax(-1, v)
        val c = count(-1, v)

        val ret = mutableListOf<Int>()

        reconstruct(-1, Math.min(c, k) - 1, v, ret)

        return ret
    }

    fun main() {
        repeat(TEST_CASE) {
            val v = List(M) { random.nextInt(1, MAX_VALUE) }
            val k = random.nextInt(2, K)
            println(solve(v, k))
        }
    }
}

fun main() {
    k번째_최대증가부분수열.main()
}
