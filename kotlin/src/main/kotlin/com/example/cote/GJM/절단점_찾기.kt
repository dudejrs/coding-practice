package com.example.cote.PGMRS

import kotlin.random.*
import kotlin.math.*

val N = 1000

val TEST_CASES = 10
val random = Random(43)

fun reachable(ret: List<List<Int>>): Boolean {
	val visited = MutableList(ret.size) {false}

	fun dfs(cur: Int) {
		visited[cur] = true

		for (next in ret[cur]) {
			if (!visited[next]) {
				dfs(next)
			}
		}
	}

	dfs(0)

	return visited.all{it}
}

fun initialize(): List<List<Int>> {
	var ret : List<List<Int>>

	while (true) {
		val n = random.nextInt(N - 3) + 3
		ret = List(n) { i ->
			IntRange(0, n - 1)
			.filter { j ->
				j != i && random.nextFloat() < 0.0075
			}
		}

		if (reachable(ret)) {
			break
		}
	}

	return ret
}

fun solve(adj: List<List<Int>>): List<Int> {
	val curVertexes = mutableListOf<Int>()
	val discovered = MutableList(adj.size) {-1}
	var counter = 0

	fun find(cur: Int, isRoot: Boolean): Int {
		discovered[cur] = counter++

		var children = 0 
		var ret = discovered[cur]

		for (next in adj[cur]) {
			if (discovered[next] == -1) {
				children++

				val subtree = find(next, false) 

				if (!isRoot && subtree >= discovered[cur]) {
					curVertexes.add(cur)
				}
				ret = min(ret, subtree)

			} else {
				ret = min(ret, discovered[next])
			}
		}

		if (isRoot && children > 1) {
			curVertexes.add(cur)
		}

		return ret
	}

	find(0 , true)

	return curVertexes
}

fun main() {
	repeat(TEST_CASES) {
		val adj = initialize()	
		println(solve(adj))
	}
}