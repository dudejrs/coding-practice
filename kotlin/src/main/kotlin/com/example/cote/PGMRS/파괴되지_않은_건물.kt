package com.example.cote.PGMRS;

import java.io.*
import java.nio.file.*

val MAX_BOUND_ROWS = 1000
val MAX_BOUND_COLS = 1000
val MAX_BOARD_DURABILITY = 1000
val MAX_SKILLS_LENGTH = 250000
val MAX_SKILLS_DEGREE = 100

data class Skill (
	val type: Int,
	val r1: Int,
	val c1: Int,
	val r2: Int,
	val c2: Int,
	val degree: Int
	) {
}

fun solve(board: List<List<Int>>, skills: List<List<Int>>): Int {
	val row = board.size;
	val col = board[0].size;

	val changes = MutableList(row + 1) {MutableList(col + 1){0}}

	val skills_ = skills.map {
		Skill(it[0], it[1], it[2], it[3], it[4], it[5])
	}

	for ((type, r1, c1, r2, c2, d) in skills_) {
		val degree = if (type == 1) -d else d

		changes[r1][c1] += degree
		changes[r1][c2 + 1] -= degree
		changes[r2 + 1][c1] -= degree
		changes[r2 + 1][c2 + 1] += degree

	}

	for (i in 0..row) {
		for (j in 0..col) {
			val diag = if (i > 0 && j > 0)  changes[i - 1][j - 1] else 0
			val up = if (i > 0) changes[i - 1][j] else 0
			val left = if (j > 0) changes[i][j - 1] else 0

			changes[i][j] += up + left - diag
		}
	}

	var safe = 0

	for ((i, _) in board.withIndex()) {
		for ((j, durability) in board[i].withIndex()) {
			if (durability + changes[i][j] > 0) {
				safe++
			}
		}
	}

	return safe
}

fun main() {
	val reader = Paths.get(System.getProperty("user.dir") + "/data/파괴되지_않은_건물.txt")
		.run {
			Files.newBufferedReader(this)
		}

	repeat(reader.readLine().toInt()) {
		val nums = reader.readLine().split(" ")
			.map(String::toInt)	
		val board = MutableList(nums[0]){
				reader.readLine().split(" ")
					.map(String::toInt)
					.toMutableList()
			}
		val skills = List(reader.readLine().toInt()) {
			reader.readLine().split(" ")
				.map(String::toInt)
		}
		val answer = reader.readLine().toInt()

		println("$answer ${solve(board, skills)}")
	}
}