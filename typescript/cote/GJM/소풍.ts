import {readFile} from 'fs/promises'

function makeGraph(friends: string[][], n: number): boolean[][]{
	const graph = new Array(n).fill(0)
		.map(_ => new Array(n).fill(false))

	for (let [a, b] of friends) {
		let [i, j] = [parseInt(a), parseInt(b)]
		graph[i][j] = graph[j][i] = true
	}

	return graph
}

function solve(friends: string[][], n: number): number{
	const graph: boolean[][] = makeGraph(friends, n)
	const visited: boolean[] = new Array(n).fill(false)

	function search(): number {
		const target = visited.findIndex(value => value == false)
		
		if (target === -1) {
			return 1
		}	
			
		let ret = 0

		for (let i = 0; i < n; i++) {
			if (!visited[i] && graph[target][i]) {
				visited[i] = visited[target] = true;
				ret += search();
				visited[i] = visited[target] = false;
			}
		}

		return ret 
	}

	return search()
}

async function main() {	
	const data: string[] = await readFile("data/소풍.txt", {'encoding' : 'utf-8'})
		.then(lines => lines.split("\n")
			.map(line => line.trim())
		);

	const testCases: number = parseInt(data[0])
	let cur: number = 1


	for (let it = 0; it < testCases; it++) {
		const [n, m] = data[cur++].split(" ")
			.map(token => parseInt(token))

		const friends: string[][] = data[cur++].split(",")
			.map(token => token.split(" "))
		console.log(solve(friends, n))
	}
}

main()