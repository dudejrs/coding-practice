const TEST_CASE = 10
const MAX_NODE = 100
const [MIN_PER_RANK, MAX_PER_RANK] = [1, 10]
const [MIN_RANKS, MAX_RANKS] = [3, 10]
const PERCENT = 0.7


function initialize() {
	var ret = []
	const rank = Math.floor(Math.random() * (MAX_RANKS - MIN_RANKS)) + MIN_RANKS

	for (let r = 0; r < rank; r++) {
		const new_nodes = Math.floor(Math.random() * (MAX_PER_RANK - MIN_PER_RANK)) + MIN_PER_RANK

		if (ret.length + new_nodes >= MAX_NODE) break

		for (let i = 0; i < ret.length; i++) {
			for (let j = i + 1; j < ret.length + new_nodes; j++) {
				if (Math.random() < PERCENT) continue;
				ret[i].push(j)
			}
		}

		ret = ret.concat(new Array(new_nodes).fill(0).map(i => new Array()))
	}

	return ret;
}

function solve(graph) {

	const visited = new Array(graph.length).fill(false)
	const ret = []

	function dfs(cur) {
		visited[cur] = true

		for (let i of graph[cur]) {
			if (visited[i]) continue
			dfs(i)
		}

		ret.push(cur)
	}


	for (let i = 0; i < graph.length; i++) {
		if (visited[i]) continue
		dfs(i)
	}

	return ret.reverse()
}

for (let it = 0; it < TEST_CASE; it++) {
	const graph = initialize()
	console.log(solve(graph))
}
