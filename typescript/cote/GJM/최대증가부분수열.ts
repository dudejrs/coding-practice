const TEST_CASES = 10
const N = 20;
const MAX_VALUE = 100


function initialize(): number[] {
	return new Array(N).fill(0)
		.map(_ => Math.floor(Math.random() * MAX_VALUE))
}

function solve(v : number[]) : number {
	const cache : number[] = new Array(N + 1).fill(-1)

	function search(cur : number, v : number[]) {	
		if (cache[cur + 1] != -1) {
			return cache[cur + 1]
		}

		let ret : number = 1

		for (let i = cur + 1; i < N; i++) {
			if (cur == -1 || v[cur] < v[i]) {
				ret = Math.max(ret, search(i, v) + 1)
			}
		}

		cache[cur + 1] = ret

		return ret
	}

	return search(-1, v)
}

for (let it = 0; it < TEST_CASES; it++) {
	const v : number[] = initialize()
	console.log(solve(v))
}

