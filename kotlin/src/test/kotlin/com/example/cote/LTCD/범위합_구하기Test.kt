package com.example.cote.LTCD;

import com.example.cote.LTCD.범위합_구하기.solve;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.FieldSource;

typealias Matrix = Array<Array<Int>>

object 범위합_구하기Test {

	@JvmStatic
	val matrix : Matrix = arrayOf(
			arrayOf(1, 2, 3, 4, 5),
			arrayOf(6, 7, 8, 9, 10),
			arrayOf(11, 12, 13, 14, 15),
			arrayOf(16, 17, 18, 19, 20),
			arrayOf(21, 22, 23, 24, 25),
		)

	@JvmStatic
	val testCases = listOf(
			arrayOf(matrix, 0, 0, 4, 4, 325),
			arrayOf(matrix, 0, 0, 0, 0, 1),
			arrayOf(matrix, 1, 1, 2, 2, 40),
		)


	@ParameterizedTest(name="accuracy test : ({1},{2}), ({3},{4})")
	@FieldSource("testCases")
	fun test (matrix:  Matrix, row1: Int, col1: Int, row2: Int, col2: Int, expected: Int) {
		val result = solve(matrix, row1, col1, row2, col2)

		assertEquals(result, expected, "expected: ${expected} actual: ${result}")
	}
}