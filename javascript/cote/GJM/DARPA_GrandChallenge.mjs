const TEST_CASE = 10
const N = 10
const MAX_GAPS = 10


function initialize() {
	const ret = []

	const gaps = (new Array(N)).fill(1)
		.map( _ => Math.random() * (MAX_GAPS - 1) + 1 )

	for (let i = 0; i< N; i++) {
		ret.push(
			gaps.slice(0,i+1)
			.reduce((a,b)=>a+b,0))
	}

	return ret
}

function decision(locations, cameras, gap) {

	let limit = -1 
	let installed = 0

	for (let location of locations) {
		if (limit <= location) {
			limit = location + gap
			installed++
		}
	}
	return installed <= cameras
}

function solve(locations, cameras) {
	let [lo, hi] = [0, locations[locations.length -1]]

	for (let i = 0; i < 100; i++) {
		let mid = (lo + hi) / 2.0

		// lo <= x < hi
		if (decision(locations, cameras, mid)) {
			lo = mid
		} else {
			hi = mid
		}	
	}

	return lo.toFixed(3)
}

for (let it = 0; it < TEST_CASE; it++) {
	const locations = initialize()
	const cameras = Math.floor(Math.random() *(N-2)) + 2
	console.log(solve(locations, cameras))
}