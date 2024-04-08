import {readFile} from 'fs/promises'

const N = 50
const D = 100

function getDegree(adj) {
	const ret = new Array(adj.length).fill(0)

	for (let i = 0; i < adj.length; i++) {
		for (let j =0; j < adj.length; j++) {
			if (adj[i][j] != 0){
				ret[i]++;
			}
		}
	}

	return ret
}

function solve1(adj, query, d, prison) {
	const degrees = getDegree(adj)
	const path = [prison]

	function search(q) {
		let ret = 0
		const cur = path[path.length - 1]
		const curDay = path.length 

		if (curDay === d + 1) {
			if (cur != q) {
				return 0
			}

			ret = 1 

			for (let i = 0; i < path.length - 1; i++) {
				ret /= degrees[path[i]]
			}

			return ret
		}


		for (let i = 0; i < adj.length; i++) {
			if (adj[cur][i] != 1) {
				continue;
			}

			path.push(i)
			ret += search(q)
			path.pop()
		}

		return ret

	}

	const answer = []

	for (let q of query) {
		answer.push(search(q))
	}

	return answer
}

function solve2(adj, query, d, prison) {
	const degrees = getDegree(adj)
	let cache;

	const answer = []

	function search(cur, curDay, q) {
		if (curDay === d) {
			return (cur === q) ? 1. : 0.
		}

		let ret = cache[cur][curDay]

		if (ret > - 1) {
			return ret
		}
		ret = 0.

		for (let i = 0; i < adj.length; i++) {
			if (adj[cur][i] != 0) {
				ret += search(i, curDay + 1, q) / degrees[cur]
			}
		}
		cache[cur][curDay] = ret

		return ret
	}

	for (let q of query) {
		cache = new Array(adj.length + 1).fill(0)
		.map(_ => new Array(d + 1).fill(-1))
		answer.push(search(prison, 0, q))
	}	

	return answer
}

async function main() {
	const data = await readFile("data/두니발_박사의_탈옥.txt", {encoding : 'utf-8'})
		.then(lines => lines.split("\n").map(line => line.trim()))
	let cur = 0
	const testCases = parseInt(data[cur++])

	for (let i = 0; i < testCases; i++) {
		const [n, d, prison] =	data[cur++].split(" ")
			.map(i => parseInt(i))
		
		const adj = new Array(n).fill(0)
			.map(_ => data[cur++]. split(" ")
				.map(i => parseInt(i)))

		const query = data[cur++].split(" ")
			.map(i => parseInt(i))

		console.log(solve1(adj, query, d, prison), solve2(adj, query, d, prison));
	}
}

main()