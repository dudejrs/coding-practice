import {readFileSync} from 'fs'

function generate(str, visited) {
	const ret = []

	for (let i = 0; i < str.length; i++) {
		if (visited[i]) {
			continue
		}
		visited[i] = true
		const word = str.split("").map((c, i) => [c, i])
			.filter((d) => visited[d[1]])
			.map(d => d[0]).join("")

		visited[i] = false

		ret.push([word, i])
	}

	ret.sort((d1, d2) => d1[0] < d2[0] ? -1 : 1)

	return ret
}

function search(str, visited, ret) {
	if (visited.every(visit => visit)) {
		return
	}

	const data = str.split("").map((c, i) => [c, i])

	for (let [word, i] of generate(str, visited)) {
		ret.push(word)
		visited[i] = true
		search(str, visited, ret)
		break
	}
}

function solve(str) {
	const visited = new Array(str.length).fill(false)
	const ret = []
	search(str, visited, ret)
	process.stdout.write(ret.join('\n'))
	return
}

(function () {
	const [tc, ...data] = readFileSync('./data/ZOAC.txt', {encoding : 'utf-8'}).split("\n")
	const testCases = parseInt(tc)

	for (let i = 1; i < 2; i++) {
		solve(data[i])
	}

})()