package com.example.cote.LTCD

import java.io.*
import java.nio.file.*

object 팰린드롬_연결_리스트 {
    class Node(val value: Int) {
        var next: Node? = null
    }

    fun solve(head: Node): Boolean {
        val queue = ArrayDeque<Int>()

        var cur: Node? = head
        while (cur != null) {
            queue.addLast(cur.value)
            cur = cur.next
        }

        while (queue.size > 1) {
            if (queue.removeFirst() != queue.removeLast()) {
                return false
            }
        }

        return true
    }

    // Runner 알고리즘
    fun solve2(head: Node): Boolean {

        var fast: Node? = head
        var slow: Node? = head
        var rev: Node? = null

        while (fast?.next != null) {
            fast = fast.next?.next
            var slowNext = slow!!.next
            var revPrev = rev
            rev = slow
            rev.next = revPrev
            slow = slowNext
        }

        if (fast != null) {
            slow = slow?.next
        }

        while (rev != null && rev.value == slow!!.value) {
            rev = rev.next
            slow = slow.next
        }

        return rev == null
    }

    fun main() {
        val p =
            Paths.get(System.getProperty("user.dir") + "/data/팰린드롬_연결_리스트.txt")
        val reader = Files.newBufferedReader(p)
        repeat(reader.readLine().toInt()) {
            val nodes =
                reader
                    .readLine()
                    .trim('\n')
                    .split(" ")
                    .map(String::toInt)
                    .map(::Node)

            repeat(nodes.size - 1) { nodes[it].next = nodes[it + 1] }

            println("" + solve(nodes[0]) + " " + solve2(nodes[0]))
        }
    }
}

fun main() {
    팰린드롬_연결_리스트.main()
}
