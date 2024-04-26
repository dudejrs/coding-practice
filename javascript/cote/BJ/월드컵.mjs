import {readFileSync} from 'fs'


function next(graph) {

	for (let i = 0; i < 6; i++) {
		for (let j = 0; j < 6; j++) {
			if (i != j && graph[i][j] == -1) {
				return [i, j]
			}
		}
	}

	return null
}

function isSame(graph, results) {
	const count = new Array(6).fill(0)
		.map(_ => new Array(3).fill(0))

	for (let i = 0; i < 6; i++) {
		for (let j = 0; j < 6; j++) {
			const outcome = graph[i][j]
			count[i][outcome]++;
		}
	}

	for (let i =0 ; i < 6; i++) {
		for (let j = 0; j < 3; j++) {
			if (count[i][j] != results[i][j]) {
				return false
			}
		}
	}

	return true
}

function promising(graph, results) {
	const allCounts = [0, 0, 0];
	
	for (let i = 0; i < 6; i++) {
		
		const count = [0, 0, 0]
		let notDecided = 0;

		for (let j = 0; j < 6; j++) {
			const outcome = graph[i][j];
			if (outcome != -1) {
				count[outcome]++; 
			} else {
				notDecided++
			}
		}

		for (let outcome = 0; outcome < 3; outcome++) {
			if (notDecided + count[outcome] < results[i][outcome]) {
				return false;
			}
			if (count[outcome] > results[i][outcome]) {
				return false;
			}

			allCounts[outcome] += count[outcome]
		}
	}

	return true;
}

function search(graph, results) {
	const cur = next(graph)

	if (!cur) {
		return isSame(graph, results)
	}

	const [i, j] = cur

	if (!promising(graph, results )) {
		return false
	}

	let ret = false
	
	for (let outcome = 0; outcome < 3; outcome++) {
			if (graph[j][i] != -1 && graph[j][i] != 2 - outcome) {
				continue;
			}

			graph[i][j] = outcome;
			ret = ret || search(graph, results)
	}

	graph[i][j] = -1


	return ret
}

function validate(results) {
	const count = [0, 0, 0]

	for (let result of results) {
		for (let i = 0; i < 3; i++) {
			count[i] += result[i]
		}
	}

	if (count[0] != count[2]) {
		return false;
	}

	if (count[0] + count[1] + count[2] != 30) {
		return false;
	}

	return true;
}

function solve(results) {	
	results = new Array(6).fill(0)
		.map((_, i) => results.slice(i * 3, i * 3 + 3))

	if (!validate(results)) {
		return 0
	}
	let graph = new Array(6).fill(0)
		.map(_ => new Array(6).fill(-1))


	return search(graph, results) ? 1 : 0
}

function main() {
	const data =  readFileSync('data/월드컵.txt', {encoding : 'utf-8'})
		.split("\n")
		.map(line => line.trim())

	let cur = 0

	const testCases = parseInt(data[cur++])

	for (let it = 0; it < testCases; it++) {
		let ret = []
		for (let i = 0; i < 4; i++) {
			const results = data[cur++].split(" ")
				.map(i => parseInt(i))
			ret.push(solve(results))
		}

		const answer = data[cur++]
		console.log(answer, ",", ret.join(" "))
	}
}

main()