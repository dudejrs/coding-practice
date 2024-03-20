const N = 10
const MAX_VALUE = 15
const TEST_CASE = 10

let cache;

function initialize() {
	const ret = []

	for (let i = 0; i < N; i++) {
		ret.push([])
		for (let j = 0; j<= i; j++) {
			ret[i].push(Math.floor(Math.random() * MAX_VALUE))
		}
	}

	return ret
}

function search(y, x, map, cache) {
	if (y == N - 1){
		return map[y][x]
	}

	let ret = cache[y][x]

	if (ret != -1) {
		return ret
	}

	ret = 0

	ret = Math.max(ret, search(y + 1, x, map, cache) + map[y][x])
	ret = Math.max(ret, search(y + 1, x + 1, map, cache) + map[y][x])

	return ret

}

function solve(map) {
	cache = new Array(N + 1).fill(0).map(_ => new Array(N + 1).fill(-1))

	return search(0, 0, map, cache)
}

for (let it = 0; it < TEST_CASE; it++) {
	const map = initialize()
	console.log(solve(map))
}