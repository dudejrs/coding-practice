package com.example.cote.PGMRS

import kotlin.random.*

val TEST_CASES = 10
val MAX_SKILLS = 5
val MAX_SKILL_TREES_LENGTH = 20
val random = Random(43)

fun generate(n: Int): String {

	val set = mutableSetOf<String>()

	do {
		val skill = ('A' + random.nextInt(26 - 1)).toString()
		set.add(skill)
	} while(set.size < n)

	return set.toMutableList().shuffled(random).joinToString("")
}

fun solve(skills: String, skillTrees: List<String>): Int {
	val regex = Regex(String.format("[^%s]", skills))
	
	return skillTrees.map{
		it.replace(regex, "")
	}.filter(skills::startsWith)
	.count()
}

fun main() {
	repeat(TEST_CASES) {
		val n = random.nextInt(MAX_SKILLS - 1) + 1
		val skills = generate(n)
		
		val skillTrees = IntRange(1, random.nextInt(MAX_SKILL_TREES_LENGTH - 2) + 2)
			.map {
				val k = random.nextInt(MAX_SKILLS - 1) + 1
				generate(k)
			}
		println(solve(skills, skillTrees))
	}
}