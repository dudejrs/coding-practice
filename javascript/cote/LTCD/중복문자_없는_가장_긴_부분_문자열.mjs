
const TEST_CASES = 10
const N = 10000

function initialize() {

	const alphabets = "Z".charCodeAt(0) - "A".charCodeAt(0);
	
	function getAlpabet(n) {
		return String.fromCharCode("A".charCodeAt(0) + n % alphabets)
	}

	let s = ""
	let n = Math.floor(Math.random() * (N - 1) + 1)

	for (let i = 0; i < n; i++) {
		s += getAlpabet(Math.floor(Math.random() * alphabets))
	}

	return s
}

function solve(s) {
	const used = new Map();
	let [ret, start] = [0, 0]

	for (let i = 0; i < s.length; i++) {

		if (used.has(s[i]) && start <= used.get(s[i])) {
			start = used.get(s[i]) + 1
		} else {
			ret = Math.max(ret, i - start + 1)
		}
		used.set(s[i], i)
	}

	return ret
}


for (let it = 0; it < TEST_CASES; it++) {
	const s = initialize()
	console.log(solve(s))
}