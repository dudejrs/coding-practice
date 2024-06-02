import {readFileSync} from 'fs'

const [N, K] = [200, 1000]
const S = 10000

const DIRECTIONS = [[-1, 0], [1, 0], [0, -1], [0, 1]]

function solve(map, k, s, y, x) {
	function visit(y, x, v, newVirus) {	
		for (let [dy, dx] of DIRECTIONS) {
			const [ny, nx] = [y + dy, x + dx]
			if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
				continue
			}
			if (map[ny][nx] != 0) {
				continue
			}
			map[ny][nx] = v
			newVirus.push([ny, nx])
		}	
	}

	const n = map.length
	let depth = 0

	const hostVirus = new Array(k + 1).fill(0).map(_ => [])

	for (let i = 0; i < n; i++) {
		for (let j = 0; j < n; j++) {
			if (map[i][j]) {
				const v = map[i][j]
				hostVirus[v].push([i, j])
			}
		}
	}

	while (depth < s) {
		if (map[y - 1][ x - 1] > 0) {
			break
		}

		for (let v = 1; v <= k; v++) {
			const newVirus = []
			for (let [y, x] of hostVirus[v]) {
				visit(y, x, v, newVirus)
			}
			hostVirus[v] = newVirus
		}
		depth++
	}

	return map[y - 1][x - 1]
}

(function main() {
	const [tc, ...data] = readFileSync('./data/경쟁적_전염.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, k] = data[cur++].split(" ").map(i => parseInt(i))

		const map = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i=> parseInt(i)))
		const [s, y, x] = data[cur++].split(" ").map(i => parseInt(i))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(map, k, s, y, x))
		// break;
	}

})()