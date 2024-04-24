import {readFile} from 'fs/promises'

class Signal {
	constructor(data) {
		this.data = data
		this.row = data.length;
		this.col = data[0].length;
	}

	static divide(data, width) {
		const ret = []
		const row = data.length / width

		for (let i = 0; i < row; i++) {
			ret.push(data.slice(width * i, width * (i + 1)))
		}

		return new Signal(ret);
	}

	crop(c1, c2 = this.col) {
		const ret = []

		for (let i = 0; i < this.row; i++) {
			const row = []
			for (let j =c1; j < c2; j++) {
				row.push(this.data[i][j])
			}
			ret.push(row)
		}

		return new Signal(ret)
	}

	next() {
		for (let j = 0; j < this.col; j++) {			
			for (let i = 0; i < this.row; i++) {
				if (this.data[i][j]) {
					return this.crop(j)
				}
			}
		}

		return null
	}

	match(data) {
		for (let i = 0; i < data.length; i++) {
			for (let j =0; j < data[0].length; j++) {
				if (this.data[i][j] != data[i][j]) {
					return false
				}
			}
		}

		return true
	}

	print() {
		for (let row of this.data) {
			let str = ""
			for (let c of row){
				str += (c == true) ? "#" : "."
			}
			console.log(str)
		}
	}
}

class Digit {
	constructor(digit, scale) {
		this.s = scale
		this.n = digit
		this.data = Digit.scale(scale, Digit.digit[digit])
	}

	static order = [0,2,3,4,5,6,7,8,9,1]

	static digit = {
		0 : [[true,true,true],[true,false,true],[true,false,true],[true,false,true],[true,true,true]],
		1 : [[true], [true], [true], [true], [true]],
		2 : [[true,true,true],[false,false,true],[true,true,true],[true,false,false],[true,true,true]],
		3 : [[true,true,true],[false,false,true],[true,true,true],[false,false,true],[true,true,true]],
		4 : [[true,false,true],[true,false,true],[true,true,true],[false,false,true],[false,false,true]],
		5 : [[true,true,true],[true,false,false],[true,true,true],[false,false,true],[true,true,true]],
		6 : [[true,true,true],[true,false,false],[true,true,true],[true,false,true],[true,true,true]],
		7 : [[true,true,true],[false,false,true],[false,false,true],[false,false,true],[false,false,true]],
		8 : [[true,true,true],[true,false,true],[true,true,true],[true,false,true],[true,true,true]],
		9 : [[true,true,true],[true,false,true],[true,true,true],[false,false,true],[true,true,true]],
	}

	static scale(s, digit) {
		if ( s == 1) {
			return digit
		}

		const ret = []

		for (const row of digit) {
			const newRow = []

			for (const cell of row) {
				for (let i = 0; i < s; i++) {
					newRow.push(cell)
				}
			}

			for (let i = 0; i < s; i++) {
				ret.push(newRow)
			}
		}

		return ret
	}
}

class DigitMatcher {	
	constructor(scale, signal) {
		this.scale = scale; 
		this.signal = signal.next();
	}

	match() {
		for (let i of Digit.order) {
			const digit = new Digit(i, this.scale)
			
			if (this.signal.match(digit.data)) {
				let cur = digit.data[0].length
				this.signal = this.signal.crop(cur)
				this.signal = this.signal.next()
				return i;
			}
		}

		return -1;
	}

	next() {
		return this.signal !== null
	}
}

class SignalParser {
	process(signal, scale) {
		const ret = []
		const matcher = new DigitMatcher(scale, signal)
		
		while(matcher.next()) {
			const digit = matcher.match()

			if (digit == -1 ) {
				throw new Error()
			}

			ret.push(digit)
		}

		return ret;
	}

	parse(signal) {
		let width = signal.length / 5
		let scale = 1

		while (width >=  1) {
			try {
				return this.process(Signal.divide(signal, width), scale)
			} catch(e) {
				// do nothing
			}
			width /= 2
			scale *= 2
		}

		return []
	}
}

function convert(signal) {
	return signal.split("")
		.map(c => c === "." ? 0 : 1);
}

function solve(n, signal) {
	const parser = new SignalParser()

	return parser.parse(convert(signal)).join("")
}

async function main() {

	const data = await readFile('./data/시그널.txt', {encoding : 'utf-8'})
		.then(lines => lines.split('\n').map(line => line.trim()));

	let cur = 0;
	const testCases = parseInt(data[cur++]);

	for (let it = 0; it < testCases; it++) {
		const n = data[cur++]
		const signal = data[cur++]
		const answer = data[cur++]
		console.log(answer, solve(n, signal))
	}

}

main()
