
const TEST_CASES = 10
const N = 10
const K = 5

function solve(nums, k) {
	let [ret, stack] = [[],[]]

	function dfs(start) {
		if (stack.length === k) {
			ret.push([...stack])
			return
		}

		for (let i = start; i < nums.length; i++) {
			stack.push(nums[i])
			dfs(i + 1)
			stack.pop()
		}
		return 
	}

	dfs(0)

	return ret
}

function main() {
	for (let it = 0; it < TEST_CASES; it++) {
		const k = Math.floor(Math.random() * (K - 1)) + 1
		const n = Math.floor(Math.random() * (N - k)) + k
		const nums = new Array(n).fill(0)
			.map((_, i) => i)

		console.log(solve(nums, k))
	}
}

main()