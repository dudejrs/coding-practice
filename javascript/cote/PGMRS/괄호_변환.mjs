import {readFileSync} from 'fs'

const OPENING = '('
const CLOSING = ')'

function isComplete(p) {
    let count = 0
    for (let c of p.split("")) {
        if (c == OPENING) {
            count++
        } else {
            if (count === 0) {
                return false
            }
            count--
        }
    }
    return count == 0
}

function solve(p) {
    if (p === '') {
        return ''
    }
    
    if (isComplete(p)) {
        return p
    }
    
    let [openings, closings] = [0, 0]
    let [start, end] = [0, 0]
    
    for (let i = 0; i < p.length; i++) {
        if (p.charAt(i) === OPENING) {
            openings++
        } else {
            closings++
        }
        
        if (i != 0 && openings == closings) {
            end = i + 1
            break;
        }
    }
    
    const [u, v] = [p.substring(start, end), p.substring(end, p.length)]
    
    if (isComplete(u)) {
        return u +  solve(v)
    } 
    
    const reversed = u.split("").slice(1, u.length - 1).map(c => c === OPENING ? CLOSING : OPENING).join("")

    
    return `(${solve(v)})${reversed}`;
}

(function main() {
	const [tc, ...data] = readFileSync('./data/괄호_변환.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())
	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const p = data[cur++]
		const answer = data[cur++]
		console.log(answer, solve(p))
	}
})()