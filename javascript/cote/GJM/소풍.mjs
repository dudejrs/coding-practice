import {readFile} from 'fs/promises'


function getRelationShip(line, n, k){

	const ret = new Array(n)

	for (let i=0; i<n; i++){
		ret[i] = new Array(n)
		for (let j=0; j<n; j++){
			ret[i][j] = false
		}
	}

	const tokens = line
			.split(" ")
			.map(n => parseInt(n))

	for (let t=0; t<k; t++) {
		let [i, j] = [tokens[2*t], tokens[2*t+1]]

		ret[i][j] = true
		ret[j][i] = true
	}
	
	return ret
}

function solve(areFriend, taken, n){

	let target = -1
	for (let i =0; i<n; i++){
		if(!taken[i]){
			target = i
			break
		}
	}

	if (target == -1) return 1;

	let ret = 0;

	for (let i=0; i<n; i++){
		if(!taken[i] && areFriend[target][i]){
			taken[i] = taken[target] = true
			ret += solve(areFriend, taken, n)
			taken[i] = taken[target] = false
		}
	}


	return	ret
}

const lines = await readFile('data/소풍.txt', {encoding: 'UTF-8'})
		.then(file => file.split("\n").map(line => line.trim()))

let testcases = parseInt(lines[0]) 
let cur = 1

while (testcases > 0){
	
	const [n, k] = lines[cur++]
						.split(" ")
						.map(n => parseInt(n))

	const areFriend = getRelationShip(lines[cur++], n, k)	
	let taken = new Array(n)
	
	for (let i=0; i<n; i++){
		taken[i] = false
	}

	console.log(solve(areFriend, taken, n))

	testcases--
}