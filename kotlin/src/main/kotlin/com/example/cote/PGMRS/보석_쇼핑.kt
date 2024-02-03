package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*
import java.util.*

data class Range(val start: Int, val end: Int) {
	val length
		get() = end - start
}


fun solve(gems: List<String>): Range {

	val gemSet = setOf(*gems.distinct().toTypedArray())
	val includes = mutableMapOf<String,Int>()

	var answer = Range(0, gems.size)
	var cur = Range(0,1)

	includes[gems[0]] = 1

	while (cur.start < gems.size) {
		when {
			(includes.size == gemSet.size) -> {
				if (cur.length < answer.length) {
					answer = cur
				}

				includes[gems[cur.start]] = (includes[gems[cur.start]] ?: 1) -1

				if (includes[gems[cur.start]] == 0) {
					includes.remove(gems[cur.start])
				}

				cur = cur.copy(start=cur.start+1)
			}
			(cur.end < gems.size) -> {
				cur = cur.copy(end=cur.end+1)
				includes[gems[cur.end-1]] = (includes[gems[cur.end-1]] ?: 0) + 1 
			}
			else -> {
				break
			}
		}
	}


	return answer.copy(start = answer.start+1)
}

fun main() {

	val p = Paths.get(System.getProperty("user.dir")+"/data/보석_쇼핑.txt")
	val reader = Files.newBufferedReader(p)

	repeat(reader.readLine().toInt()) {
		val gems = reader.readLine().split(" ")
		val answer = reader.readLine()
						.split(" ")
						.map(String::toInt)

		val (start, end) = solve(gems)
		println(String.format("solved: (%d,%d),  answer: (%d,%d)", start, end, answer[0], answer[1]))
	}

	return
}