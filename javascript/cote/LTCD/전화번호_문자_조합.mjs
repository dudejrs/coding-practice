
const N = 10
const TEST_CASES = 10

const dics = new Map(Object.entries({
	"2" : "abc",
	"3" : "def",
	"4" : "ghi",
	"5" : "jkl",
	"6" : "mno",
	"7" : "pqks",
	"8" : "tuv",
	"9" : "wxyz"
}))

function solve(digits) {

	const l = [...digits]
	const [stack, ret] = [[],[]]

	function dfs() {
		if (l.length == 0) {
			ret.push([...stack].join(""))
			return
		}

		const cur = l.shift() 
		for (let c of dics.get(cur)) {
			stack.push(c)
			dfs()
			stack.pop()
		}
		l.unshift(cur)

	}
	
	dfs()

	return ret
}


function main() {

	for (let it = 0; it < TEST_CASES; it++) {
		const n = Math.floor(Math.random() * (N - 1)) + 1
		const digits = new Array(n).fill(0).map(_ => (Math.floor(Math.random() * 8) + 2).toString())
		console.log(solve(digits))
	}
}

main()