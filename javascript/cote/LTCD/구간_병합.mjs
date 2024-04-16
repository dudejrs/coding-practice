const TEST_CASES = 1
const N = 10000
const MAX_NUMBER = N
const MAX_INTERVAL = 100

function initialize() {
	const n = Math.floor(Math.random() * (N - 1)) + 1
	const ret = []

	for (let i = 0; i < n; i++) {
		const begin = Math.floor(Math.random() * (MAX_NUMBER - MAX_INTERVAL)) 
		const end = begin + Math.floor(Math.random() * MAX_INTERVAL)
		ret.push([begin, end])
	}

	return ret
}

function solve(intervals) {
	const merged = []

	intervals.sort((a, b) => a[0] - b[0])
	console.log(intervals)

	for (const [begin, end] of intervals) {
		const last = merged ? merged[merged.length - 1] : undefined
		if (last && begin <= last[1] ) {
			last[1] = Math.max(last[1], end)
		} else {
			merged.push([begin, end])
		}

	}

	return merged
}

function main () {
	for(let i = 0; i < TEST_CASES; i++) {
		const intervals = initialize()
		console.log(intervals)
		console.log(solve(intervals))
	}
}

main()