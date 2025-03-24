package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*

object 사라지는_발판 {

    val MAX_BOARD_ROW = 5
    val MAX_BOARD_COL = 5

    data class Result(val win: Boolean, val turns: Int)

    data class Coord(val y: Int, val x: Int) {

        fun move(m: Movement): Coord {
            return Coord(y + m.dy, x + m.dx)
        }

        fun isValid(board: Array<Array<Int>>): Boolean {
            return y >= 0 && y < board.size && x >= 0 && x < board[0].size
        }
    }

    enum class Movement(val dy: Int, val dx: Int) {
        UP(-1, 0),
        DOWN(1, 0),
        LEFT(0, -1),
        RIGHT(0, 1)
    }

    fun game(
        player: Coord,
        opponenet: Coord,
        board: Array<Array<Int>>
    ): Result {

        if (board[player.y][player.x] == 0) {
            return Result(false, 0)
        }

        var playerWins = false
        var loseTurns = 0
        var winTurns = Int.MAX_VALUE

        board[player.y][player.x] = 0

        for (m in Movement.values()) {
            val newCoord = player.move(m)

            if (!newCoord.isValid(board)) {
                continue
            }

            if (board[newCoord.y][newCoord.x] == 0) {
                continue
            }

            val (opponenetWins, turns) = game(opponenet, newCoord, board)

            when {
                !opponenetWins -> {
                    playerWins = true
                    winTurns = Math.min(winTurns, turns + 1)
                }
                !playerWins -> {
                    loseTurns = Math.max(loseTurns, turns + 1)
                }
            }
        }
        board[player.y][player.x] = 1

        return if (playerWins) Result(true, winTurns)
        else Result(false, loseTurns)
    }

    fun solve(board: Array<Array<Int>>, aLoc: List<Int>, bLoc: List<Int>): Int {
        return game(Coord(aLoc[0], aLoc[1]), Coord(bLoc[0], bLoc[1]), board)
            .turns
    }

    fun main() {
        val reader =
            with(
                Paths.get(
                    System.getProperty("user.dir") + "/data/사라지는_발판.txt")) {
                    Files.newBufferedReader(this)
                }

        repeat(reader.readLine().toInt()) {
            val nums = reader.readLine().split(" ").map(String::toInt)
            val board =
                List(nums[0]) {
                        reader
                            .readLine()
                            .split(" ")
                            .map(String::toInt)
                            .toTypedArray()
                    }
                    .toTypedArray()
            val aLoc = reader.readLine().split(" ").map(String::toInt)
            val bLoc = reader.readLine().split(" ").map(String::toInt)
            val answer = reader.readLine().toInt()

            println("$answer ${solve(board, aLoc, bLoc)}")
        }
    }
}

fun main() {
    사라지는_발판.main()
}
