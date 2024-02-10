package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*


fun count(storey: Int): Int {
	if (storey <= 1) return storey

	val under10 = storey % 10
	val rest = storey / 10

	val c1 = under10 + count(rest)
	val c2 = (10 - under10) + count(rest + 1)

	return Math.min(c1,c2)
}

fun solve(storey: Int): Int {
	return count(storey)
}

fun main() {
	val p = Paths.get(System.getProperty("user.dir")+"/data/마법의_엘레베이터.txt")
	val reader = Files.newBufferedReader(p)
	
	repeat (reader.readLine().toInt()){
		val storey = reader.readLine().toInt()
		val answer = reader.readLine().toInt()

		println("${solve(storey)} $answer")
	}
}