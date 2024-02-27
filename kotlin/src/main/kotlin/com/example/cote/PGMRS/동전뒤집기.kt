package com.example.cote.PGMRS

import java.io.*
import java.nio.file.*

fun flipCoins(coin: Array<Int>, k: Int, target: Int): Int {
	var ret = 0

	for (i in 0..coin.size - k) {
		if (coin[i] == target ) continue;

		for (j in i..i+k-1) {
			coin[j] = (1 - coin[j])
		}
		ret++
	}

	val count = coin.count {it == target }

	return if (count == coin.size) ret else -1
}

fun solve(coin: Array<Int>, k: Int): Int {
	if (coin.size == 1) return 0

	val sum = coin.sum()
	if (sum == 0 || sum == coin.size) return 0

	val ret = Math.min(flipCoins(coin.copyOf(), k, 0), 
		flipCoins(coin.copyOf(), k, 1))

	return if (ret == Int.MAX_VALUE) -1 else ret
}

fun main() {

	val p = Paths.get(System.getProperty("user.dir") + "/data/동전뒤집기.txt")
	val reader = Files.newBufferedReader(p)

	repeat(reader.readLine().toInt()) {
		val coin = reader.readLine().split(" ")
			.map(String::toInt)
			.toTypedArray()	

		val k = reader.readLine().toInt()
		val answer = reader.readLine().toInt()

		println("$answer ${solve(coin, k)}")
	}

}