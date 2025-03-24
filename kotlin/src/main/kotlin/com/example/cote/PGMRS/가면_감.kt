package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*
import kotlin.math.*

object 가면_감 {

    val stack = ArrayDeque<Int>()
    var counter: Int = 0
    var groupCounter: Int = 0

    class Member(var visit: Int = -1, var group: Int = -1) {
        override fun toString(): String = "$visit($group)"
    }

    fun initialize(n: Int, reply: List<List<Int>>): List<List<Int>> {
        val adj = List(n - 1) { mutableListOf<Int>() }

        for (i in 1..n - 1) {
            for (k in reply[i]) {
                adj[k - 1].add(i - 1)
            }
        }

        return adj
    }

    fun dfs(cur: Int, members: List<Member>, adj: List<List<Int>>): Int {
        members[cur].visit = counter++
        stack.add(cur)

        var ret = members[cur].visit

        for (next in adj[cur]) {
            if (members[next].visit == -1) {
                ret = min(ret, dfs(next, members, adj))
            } else if (members[next].group == -1) {
                ret = min(ret, members[next].visit)
            }
        }

        if (ret == members[cur].visit) {
            while (stack.size != 0) {
                val t = stack.removeLast()
                members[t].group = groupCounter
                if (t == cur) {
                    break
                }
            }
            groupCounter++
        }

        return ret
    }

    fun count(members: List<Member>, adj: List<List<Int>>): Int {
        val skip = MutableList(groupCounter) { false }

        // 다른 컴포넌트로 가는 간선이 있는 경우 같은 그룹으로 처리해 준다
        for ((i, e) in adj.withIndex()) {
            for (j in e) {
                if (members[i].group != members[j].group) {
                    skip[members[i].group] = true
                }
            }
        }

        return skip.filter { !it }.count()
    }

    fun solve(n: Int, reply: List<List<Int>>): Int {
        counter = 0
        groupCounter = 0
        stack.clear()

        val members = List(n - 1) { Member() }
        val adj = initialize(n, reply)

        for ((i, member) in members.withIndex()) {
            if (member.visit == -1) {
                dfs(i, members, adj)
            }
        }

        return count(members, adj)
    }

    fun main() {
        val reader =
            with(Paths.get(System.getProperty("user.dir") + "/data/가면_감.txt")) {
                Files.newBufferedReader(this)
            }

        repeat(reader.readLine().toInt()) {
            val n = reader.readLine().toInt()
            val reply =
                List(n) { reader.readLine().split(" ").map(String::toInt) }
            val answer = reader.readLine().toInt()

            println("$answer ${solve(n, reply)}")
        }
    }
}

fun main() {
    가면_감.main()
}
