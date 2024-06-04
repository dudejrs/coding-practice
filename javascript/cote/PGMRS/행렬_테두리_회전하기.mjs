import {readFileSync} from 'fs'

function directions() {
    return [[0, 1], [1, 0], [0, -1], [-1, 0]]
}

function* rotation(query, matrix) {
	const [y1, x1, y2, x2] = query
    let cur = {y : y1 -1, x : x1 - 1}
    let tmp = matrix[cur.y][cur.x];

    for (let [dy, dx] of directions()) {
        if (dy == 0) {
            for (let i = 0; i < x2 - x1; i++) {
                [tmp, matrix[cur.y][cur.x + dx]] = [matrix[cur.y][cur.x + dx], tmp]
                cur.x += dx
               yield tmp
            }
        } else {
            for (let j = 0; j < y2 - y1; j++) {
            	[tmp, matrix[cur.y + dy][cur.x]] = [matrix[cur.y + dy][cur.x], tmp]
                cur.y += dy
                yield tmp
            }
        }
    }   
    return 
}

function solve(rows, columns, queries) {
    var answer = [];
    
    const matrix = new Array(rows).fill(0)
        .map((_, i) => new Array(columns).fill(0).map((_,j) => i * columns + j + 1))

    for (let query of queries) {
        answer.push(Math.min(...rotation(query, matrix)))
    }
    
    return answer;
}

(function main() {
	const [tc, ...data] = readFileSync('./data/행렬_테두리_회전하기.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())
	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [rows, columns, q] = data[cur++].split(" ").map(i => parseInt(i))
		const queries = new Array(q).fill(0).map(i => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = data[cur++].split(" ").map(i => parseInt(i))
		console.log(answer, solve(rows, columns, queries))
	}
})()