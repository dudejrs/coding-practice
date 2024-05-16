import {readFileSync} from 'fs'

class File {
    static FORMAT = /([.-\sa-zA-Z]+)([0-9]{1,5})([\s\w.-]*)/g
    
    constructor(index, head, number, tail){
        this.head = head
        this.number = number
        this.n = parseInt(number)
        this.tail = tail
        this.index = index
    }
    
    static of(file, index) {
        const [_, head, number, tail] = file.matchAll(File.FORMAT).next().value
        
        return new File(index, head, number, tail)
    }
    
    get name() {
        return `${this.head}${this.number}${this.tail}`
    }
}

function solve(files) {
    files = files.map((file, i) => File.of(file, i))
    files.sort((f1, f2) => {
        if (f1.head.toLowerCase() != f2.head.toLowerCase()) {
            return f1.head.toLowerCase() < f2.head.toLowerCase() ? -1 : 1
        }
        
        if (f1.n != f2.n) {
            return f1.n - f2.n
        }
        
        return f1.index - f2.index
    })
    
    return files.map(file => file.name);
}

(function main(){
	
	const [tc, ...data] = readFileSync('data/파일명_정렬.txt', {encoding : 'utf-8'}).split("\n")

	const testcases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testcases; it++) {
		const files = data[cur++].split(",")
		console.log(solve(files))
	}

})()