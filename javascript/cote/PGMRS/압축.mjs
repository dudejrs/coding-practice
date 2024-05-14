import {readFileSync} from 'fs'

class Node {
    constructor(id = -1) {
        this.id = id
        this.children = new Map()
    }
    
    add(word, id, offset = 0) {
        const length = word.length - offset  
        if (length == 0) {
            this.id = id
        }
        
        if (length > 0) {
            const c = word.charAt(offset)
            if (!this.children.has(c)) {
                this.children.set(c, new Node())
            }
            this.children.get(c).add(word, id, offset + 1)
        }
    }
    
    search(word, offset = 0) {
        if (offset == word.length) {
            return this.id
        }
        
        const c = word.charAt(offset)
        
        if (!this.children.has(c)) {
            return -1
        }
        
        return this.children.get(c).search(word, offset + 1)
    }
}

const defaultDictionary = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'.split("").map((c, i) => [c, i + 1])

function solve(msg) {
    var answer = []
    
    const trie = new Node()
    
    for (const [_, entry] of defaultDictionary.entries()) {
        const [c, id] = entry
        trie.add(c, id)
    }

    let cur = 0 
    let counter = 27
    
    while (cur < msg.length) {
        let [start, end] = [cur, cur + 1]
        let num = -1
        while (end <= msg.length && trie.search(msg.substring(start, end)) != -1) { 
            num = trie.search(msg.substring(start, end))
            end++
        }
        answer.push(num)
        trie.add(msg.substring(start, end), counter++)
        cur = end -1
    }
    
    return answer;
}

(function main() {
	const [tc, ...data] = readFileSync('./data/압축.txt', {encoding : 'utf-8'}).split("\n")
	
	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const msg = data[cur++].trim()
		const answer = data[cur++].trim().split(" ").map(i => parseInt(i))
		console.log(answer, solve(msg))
	}
})()