import {readFileSync} from 'fs'

class Node {
	constructor(id, children = []) {
		this.ids = []
		this.children = new Map(children)
	}

	add(word, id, offset = 0){
		if (offset == word.length) {
			this.ids.push(id)
			return
		}

		const c = word.charAt(offset)
		if (!this.children.has(c)) {
			this.children.set(c, new Node())
		}

		this.children.get(c).add(word, id, offset + 1)
	}

	search(word, offset = 0) {
		if (offset == word.length) {
			return [...this.ids]
		}

		const c = word.charAt(offset)

		if (c === '?'){
			let ret = []
			for (let children of this.children.values()) {
				ret.push(...children.search(word, offset + 1))
			}
			return ret
		}

		if (!this.children.has(c)) {
			return []
		}

		return this.children.get(c).search(word, offset + 1)
	}
}

function build(base) {
	const ret = new Node()

	let count = 0
	
	for (let i = 0; i < base.length; i++) {
		for (let j = i + 1; j <= base.length; j++) {
			ret.add(base.substring(i,j), count++)
		}
	}

	return ret
}

function convert(trie, target) {	
	if (trie.search(target).length != 0) {
		return true
	}

	for (let i = 1; i < target.length; i++) {
		const head = target.substring(0, i)
		const tail = target.substring(i, target.length)

		const headIds = trie.search(head)
		const tailIds = trie.search(tail)

		for (let headId of headIds) {
			for (let tailId of tailIds) {
				if (tailId !=  headId) {
					return true
				}
			}
		}
	}

	return false
}

function* generate(target) {
	yield target

	for (let i = 0; i < target.length; i++) {
		yield target.substring(0, i) + "?" + target.substring(i + 1, target.length)
	}

	return
}

function solve(base, targets){
	const trie = build(base)
	const ret = []

	for (let target of targets) {
		let convertible = false
		
		for (let t of generate(target)) {
			convertible |= convert(trie, t)
		}

		ret.push(convertible)
	}

	return ret
}

(function main(){
	const [tc, ...data]= readFileSync('data/문자열_해독_게임.txt', {encoding : 'utf-8'}).split("\n")

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const base = data[cur++]
		const targets = data[cur++].split(" ")
		const answer = data[cur++].split(" ").map(i => parseInt(i))
		console.log(answer, solve(base, targets))
	}
})()
