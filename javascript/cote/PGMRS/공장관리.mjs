import {readFile} from 'fs/promises'


function searchFinishedHour(goal, durations, maxDuration) {

	let [lo, hi] = [0, maxDuration * Math.ceil(goal / durations.length)]

	while (lo + 1 < hi) {
		const mid = Math.floor((lo + hi) / 2)
	
		let count = 0
		for (let duration of durations) {
			count += Math.floor(mid / duration )
		}
		
		if (goal <= count) {
			hi = mid
		} else {
			lo = mid
		}

	}

	return hi
}

function calcPay(hour, durations, maxDuration) {

	const min = Math.floor(hour / maxDuration)

	let ret = 0

	for (let duration of durations) {
		ret += (Math.floor(hour / duration) - min) * 10000
	}

	return ret
}

function solve(goal, durations) {
	const maxDuration = durations.toSorted().pop()
	
	const hour = searchFinishedHour(goal, durations, maxDuration)

	return calcPay(hour, durations, maxDuration)
}

const lines = await readFile('data/공장관리.txt', {encoding : 'UTF-8'})
	.then(lines => lines.split("\n")
		.map(line => line.trim()))

let testcases = parseInt(lines[0])
let cur = 1
while(testcases > 0){
	const goal = parseInt(lines[cur++])
	const durations = lines[cur++].split(" ")
		.map(i => parseInt(i))
	const answer = parseInt(lines[cur++])

	console.log(answer, solve(goal, durations))

	testcases--
}
