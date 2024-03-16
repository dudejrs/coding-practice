package com.example.cote.PGMRS;

import java.io.*
import java.nio.file.*

class Hand(val hand: String,
	var y : Int,
	var x : Int,
	val baseX: Int,
	preferedHand: String) {
	
	val prefered: Boolean
	
	init {
		prefered = preferedHand.equals(hand)
	}
	
	fun distance(y: Int, x: Int): Double 
		= when {
			x == baseX -> 0.0
			prefered -> Math.abs(this.x - x) + Math.abs(this.y - y) - 0.5
			else ->  (Math.abs(this.x - x) + Math.abs(this.y - y)).toDouble()
		}

	fun move(y: Int, x: Int): Hand {
		this.x = x;
		this.y = y;
		return this;
	}
}

fun getY(number: Int): Int 
	= if (number == 0) 3 else (number - 1) / 3

fun getX(number: Int): Int 
	= if (number == 0) 1 else (number - 1) % 3 

fun press(number: Int, left: Hand, right: Hand): String {
	val y = getY(number)
	val x = getX(number)

	val lDistance = left.distance(y, x)
	val rDistance = right.distance(y, x)

	return if (lDistance > rDistance) right.move(y, x).hand
		else left.move(y, x).hand
}

fun solve(numbers: Array<Int>, prefered: String): String {
	var preferedHand  = if (prefered.equals("left")) "L" else "R"
	val left = Hand("L", 3, 0, 0, preferedHand)
	val right = Hand("R", 3, 2, 2, preferedHand)

	return numbers.map{
		press(it, left, right)
	}.joinToString("")
}

fun main() {

	val p = Paths.get(System.getProperty("user.dir") + "/data/키패드_누르기.txt")
	val reader = Files.newBufferedReader(p)

	repeat(reader.readLine().toInt()) {
		val numbers = reader.readLine().split(" ")
			.map(String::toInt)
			.toTypedArray()

		val prefered = reader.readLine()
		val answer = reader.readLine()

		println("$answer ${solve(numbers, prefered)}")
	}
}