

const TEST_CASES = 10 
const N = 1000
const TARGET = 1.5 * N



function shuffle(a, n) {

	for (let it = 0; it < n; it++) {

		let i = Math.floor(Math.random() * (a.length-1))
		let j = Math.floor(Math.random() * (a.length-1))
		
		if (a[i] && a[j]){
			[a[i], a[j]] = [a[j], a[i]]
		}
	}

	return a
}

function solve(nums, target) {
	let map = new Map()

	for (let i=0; i<nums.length; i++){
		map[nums[i]] = i
	}

	for (let i=0; i<nums.length; i++) {

		if ( map[target-nums[i]] && i != map[target - nums[i]]) {
			return [i, map[target - nums[i]]]
		}
	}

	return []
}

for (let i=0; i<TEST_CASES; i++) {
	let n = Math.floor(Math.random() * (N-1)) + 1
	
	let nums = (new Array(N))
					.fill(1)
					.map((v, i) => i)

	nums = shuffle(nums, 10 * N)
				.splice(0, n)


	let target = Math.floor(Math.random() * (TARGET -1 )) + 1
	console.log(solve(nums, target))
}