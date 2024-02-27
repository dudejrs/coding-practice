
const TEST_CASES = 10
const N = 8
const MAX_VALUE = 100


function solve(nums) {
	const ret = []

	function dfs(components) {
		if (components.length == 0) {
			ret.push([...ret])
			return
		}

		for (let component of components) {
			ret.push(component)
			dfs(components.filter(v => v != component))
			ret.pop()
		}
	}

	dfs([...nums])

	return ret
}


for (let it =0; it < TEST_CASES; it++) {
	let nums = []
	let n = Math.floor(Math.random() * (N - 1)) + 1
	
	for (let i = 0; i < n; i++) {
		nums[i] = Math.floor(Math.random() * MAX_VALUE)
	}
	console.log(nums.length)
	console.log(solve(nums))
}