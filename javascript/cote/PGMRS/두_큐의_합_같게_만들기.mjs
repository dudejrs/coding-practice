import {readFileSync} from 'fs'

const QUEUE_LENTH = 300_000

function sum(queue) {
    return queue.reduce((acc, a) => acc + a, 0)
}

function solve(queue1, queue2) {
    let sum1 = sum(queue1)
    const total = sum1 + sum(queue2)
    
    if (total % 2 != 0) {
        return -1
    }
    
    const n = queue1.length + queue2.length
    const q = queue1.concat(queue2)
    const target = total / 2
    let [i, j] = [0, queue1.length]
    
    let count = 0
    while (i < n) {
        if (sum1 === target) {
            return count
        }
        if (sum1 > target) {
            sum1 -= q[i]
            i++
        } else {
            sum1 += q[j]
            j = (j + 1) % n
        }
        count++
    }
    
    return -1;
}

(function main() {
	const [tc, ...data] = readFileSync('./data/두_큐의_합_같게_만들기.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)
	let cur = 0

	for (let it = 0; it < testCases; it++) {
		const queue1 = data[cur++].split(" ").map(i => parseInt(i))
		const queue2 = data[cur++].split(" ").map(i => parseInt(i))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(queue1, queue2))
	}
})()
