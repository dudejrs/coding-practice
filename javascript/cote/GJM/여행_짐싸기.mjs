import {readFile} from 'fs/promises'

const N = 100
const W = 1000

let cache;

function search(cur, n, capacity, names, volumnes, needs) {
	if (capacity === 0 || cur === n) {
		return 0
	}

	let ret = cache[cur][capacity]
	
	if (ret !== -1) {
		return ret
	}

	ret  = search(cur + 1, n, capacity, names, volumnes, needs)

	if (capacity >= volumnes[cur]) {
		ret = Math.max(ret, search(cur + 1, n, capacity - volumnes[cur], names, volumnes, needs) + needs[cur])
	}

	cache[n][capacity] = ret

	return ret
}

function solve(n, capacity, names, volumnes, needs){
	cache = new Array(n+1).fill(0).map(_ => new Array(W +1).fill(-1));

	return search(0, n, capacity, names, volumnes, needs)
}

async function main() {
	const data = await readFile('data/여행_짐싸기.txt', {encoding : 'utf-8'})
		.then(lines => lines.split("\n")
				.map(line => line.trim()));
	let cur = 0;
	const testCases = parseInt(data[cur++]);
	for (let it = 0; it < testCases; it++) {
		const [n, capacity] = data[cur++].split(" ")
			.map(i => parseInt(i));
		const names = new Array(n);
		const volumnes = new Array(n);
		const needs = new Array(n);

		for (let i = 0; i < n; i++) {
			const [name, volumne, need] = data[cur++].split(" ");
			names[i] = name;
			volumnes[i] = parseInt(volumne);
			needs[i] = parseInt(need);
		}
		console.log(solve(n, capacity, names, volumnes, needs));
	}
}

main()