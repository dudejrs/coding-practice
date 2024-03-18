import {readFile} from 'fs/promises'


const data = await readFile('data/최소_높이_트리.txt', {'encoding' : 'utf-8'})
	.then(lines => lines.split("\n").map(
		line => line.trim()))

let testCases = parseInt(data[0])
let cur = 1;

function solve(edges, n) {
	if (n <= 1)
		return [0]

	const graph = new Map()

	for (let i = 0; i < n; i++) {
		graph.set(i, [])
	}

	for (let [i, j] of edges) {
		graph.get(i).push(j)
		graph.get(j).push(i)
	}	

	let leaves = []

	for (let [i, node] of graph.entries()) {
		if(node.length == 1) {
			leaves.push(i)
		}
	}

	while (n > 2) {
		n -= leaves.length

		let new_leaves = []

		for (let leaf of leaves) {
			const parent = graph.get(leaf).pop()
			graph.set(parent, graph.get(parent).filter(i => i != leaf))

			if (graph.get(parent).length == 1){
				new_leaves.push(parent)
			}
		}
		leaves = new_leaves
	}

	return leaves
}

while (testCases > 0) {
	const [n, m] = data[cur++].split(" ").map(l => parseInt(l))
	const edges = []
	for (let i = 0; i < m; i++){
		edges.push(data[cur++].split(" ").map(l => parseInt(l)))
	}
	const answer = data[cur++].split(" ").map(l => parseInt(l))
	console.log(answer, solve(edges, n))
	testCases--;
}