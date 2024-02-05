const TEST_CASES = 10
const N = 10
const MAX = 987654321
const MAX_WEIGHT = 100


function initialize(){
	const ret = new Array(N).fill(0)
				.map(v => new Array(N).fill(MAX))

	for (let i=0; i<N; i++) {
		for(let j= i+1; j<N; j++){
			const tmp = Math.floor(Math.random() * MAX_WEIGHT) + 1
			if (tmp % 13 == 0 ) continue
			ret[i][j] = tmp
			ret[j][i] = tmp
		}
	}

	return ret 
}

function calculate(w, path) {
	let ret = 0
	let start, end

	for (let i =1; i < N; i++) {
		start = path[i-1]
		end = path[i]
		ret += w[start][end]
	}

	start = path[0]
	end = path[N-1]

	return w[end][start] == MAX ? MAX : ret + w[end][start]
}

function search(w, visited, path) {
	if (path.length == N) {
		return calculate(w, path)
	}

	let ret = Number.MAX_VALUE
	const cur = path[path.length-1]

	for (let i=0; i<N; i++) {
		if(visited[i] || w[cur][i] == MAX) continue

		visited[i] = true
		path.push(i)
		ret = Math.min(search(w,visited,path), ret)
		path.pop()
		visited[i] = false
	}

	return ret
}

function solve(w) {
	const visited = new Array(N).fill(false)
	visited[0] = true
	return search(w, visited, [0])
}


for (let it=0; it< TEST_CASES; it++) {
	const w = initialize()
	console.log(solve(w))
}

