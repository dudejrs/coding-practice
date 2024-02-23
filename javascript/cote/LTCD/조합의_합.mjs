
const TEST_CASES = 10
const MAX_VALUE = 100
const N = 15

function solve(candidates, target) {
	const ret = []

	function dfs(cur, path, acc) {

		if (candidates.length <= cur) {
			return
		}

		if (acc > target) {
			return
		}

		if (acc == target) {
			ret.push([...path])
			return
		}

		for (let i = cur; i < candidates.length; i++) {
			path.push(candidates[i])
			dfs(i + 1, path, acc + candidates[i])
			path.pop()
		}

		return
	}

	dfs(0, [], 0)

	return ret
}

for (let it = 0; it < TEST_CASES; it++) {
	
	const candidates = []

	for (let i = 0; i < N; i++) {
		candidates.push(Math.floor(Math.random() * MAX_VALUE))
	}

	const target = Math.floor(Math.random() * MAX_VALUE * 1.5)

	console.log(solve(candidates, target))
} 
