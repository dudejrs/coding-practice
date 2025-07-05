package com.example.cote.LTCD

typealias Matrix = Array<Array<Int>>

object 범위합_구하기 {
    private fun getRangeSum(matrix: Matrix): Matrix {
        val result: Matrix =
            Array(matrix.size + 1) { Array((matrix[0].size + 1)) { 0 } }

        for (i in 0 until matrix.size) {
            for (j in 0 until matrix.size) {
                result[i + 1][j + 1] =
                    result[i + 1][j] + result[i][j + 1] - result[i][j] +
                        matrix[i][j]
            }
        }

        return result
    }

    public fun solve(
        matrix: Matrix,
        row1: Int,
        col1: Int,
        row2: Int,
        col2: Int
    ): Int {
        val rangeSum = getRangeSum(matrix)

        return rangeSum[row2 + 1][col2 + 1] -
            rangeSum[row1][col2 + 1] -
            rangeSum[row2 + 1][col1] + rangeSum[row1][col1]
    }
}
