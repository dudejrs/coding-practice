package com.example.cote.GJM

import java.io.*
import java.nio.file.*

object 보글게임 {

    val steps =
        listOf(
            Pair(-1, -1),
            Pair(-1, 0),
            Pair(-1, 1),
            Pair(0, -1),
            Pair(0, 1),
            Pair(1, -1),
            Pair(1, 0),
            Pair(1, 1))

    fun hasWord(
        board: List<String>,
        y: Int,
        x: Int,
        word: String,
        cur: Int
    ): Boolean {
        if (cur == word.length) {
            return true
        }
        if (board[y][x] != word[cur]) {
            return false
        }

        for ((dy, dx) in steps) {
            val ny = y + dy
            val nx = x + dx
            if (ny < 0 || ny >= board.size || nx < 0 || nx >= board[0].length) {
                continue
            }
            if (hasWord(board, ny, nx, word, cur + 1)) {
                return true
            }
        }

        return false
    }

    fun solve(board: List<String>, words: List<String>): List<Pair<Int, Int>> {

        val ret = mutableListOf<Pair<Int, Int>>()

        for (word in words) {
            for (y in 0..board.size - 1) {
                for (x in 0..board[0].length - 1) {
                    if (hasWord(board, y, x, word, 0)) {
                        ret.add(Pair(y, x))
                    }
                }
            }
        }
        return ret
    }

    val p = Paths.get(System.getProperty("user.dir") + "/data/보글게임.txt")
    val reader = Files.newBufferedReader(p)

    fun main() {
        repeat(reader.readLine().toInt()) {
            val nums = reader.readLine().split(" ").map(String::toInt)

            val board = IntRange(1, nums[0]).map { reader.readLine() }

            val words = reader.readLine().trim().split(" ")
            println(solve(board, words))
        }
    }
}

fun main() {
    보글게임.main()
}
