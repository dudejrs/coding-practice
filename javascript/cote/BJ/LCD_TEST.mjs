const S = 10
const N = 9999999999
const TEST_CASES = 10

const mapper = {
	data : {
		0 : [true, true, true, true, true, true, false],
		1 : [false, true, true, false, false, false, false],
		2 : [true, true, false, true, true, false, true],
		3 : [true, true, true, true, false, false, true],
		4 : [false, true, true, false, false, true, true],
		5 : [true, false, true, true, false, true, true],
		6 : [true, false, true, true, true, true, true],
		7 : [true, true, true, false, false, false, false],
		8 : [true, true, true, true, true, true, true],
		9 : [true, true, true, true, false, true, true]
	},

	draw : function (n, s, buffer) {
		if (0 > n || n >= 10) {
			throw new Error("UnExpected Number");
		}

		this.data[n].forEach((v, i) => {
			if (v) {
				buffer.drawline(...this.start(i, s), ...this.end(i, s))
			}
		})
	},

	start : function (i, s) {
		switch(i){
			case 0 :  
				return [0, 1]
			case 1 : 
				return [1, s + 1]
			case 2 : 
				return [s + 2, s + 1]
			case 3 : 
				return [2 * s + 2, 1]
			case 4 : 
				return [s + 2, 0]
			case 5 : 
				return [1, 0]
			case 6 : 
				return [s + 1, 1]

		}
	},
	
	end : function (i, s) {
		switch(i) {
			case 0 : 
				return [0, s + 1]
			case 1 : 
				return [s + 1, s + 1]
			case 2 : 
				return [2 * s + 2, s + 1]
			case 3 : 
				return [2 * s + 2, s + 1]
			case 4 : 
				return [2 * s + 2, 0]
			case 5 : 
				return [s + 1, 0]
			case 6 : 
				return [s + 1, s + 1]
		}
	}
}

class Buffer {
	constructor(s) {
		this.s = s;
		this.data = Array(2 * s + 3).fill(0)
			.map(_ => new Array(s + 2).fill(" ")) 
	}

	concat(other) {
		for (let i = 0; i < this.data.length; i++ ){
			this.data[i].push(" ",...other.data[i])
		}

		return this
	}

	drawline(y1, x1, y2, x2) {
		const dy = y2 - y1;
		const dx = x2 - x1;

		if (dy != 0 && dx != 0) {
			throw new Error("Unsupported");
		}
		if (dy != 0 ) {
			for (let y = Math.min(y1, y2);  y < Math.max(y1, y2); y++) {
				this.data[y][x1] = '|'
			}
		} 
		if (dx != 0) {
			for (let x = Math.min(x1, x2);  x < Math.max(x1, x2); x++) {
				this.data[y1][x] = '-'
			}
		}
	}

	*[Symbol.iterator]() {
		for (let row of this.data) {
			yield row
		}
	}
}

class Unit {
	constructor(mapper, s, n) {
		this.mapper = mapper;
		this.s = s;
		this.n = n;
		this.buffer = this.#createBuffer() 
	}

	concat(other) {
		this.n = this.n * 10 + other.n
		this.buffer = this.buffer.concat(other.buffer)

		return this
	}

	#createBuffer() {
		const buffer = new Buffer(this.s);

		mapper.draw(this.n, this.s, buffer)

		return buffer;
	}
}

class LCD {
	constructor(mapper, s){
		this.mapper = mapper;
		this.s = s;
	}

	print(n) {
		const total = n.toString().split("")
			.map(i => parseInt(i))
			.map(i => new Unit(this.mapper, this.s, i))
			.reduce((acc, val) => acc.concat(val))

		for (let row of total.buffer) {
			console.log(row.join(""))
		}
	}
}

function solve(s, n) {
	const lcd = new LCD(mapper, s);
	lcd.print(n)

}

function main() {

	for (let it = 0; it < TEST_CASES; it++) {
		let s = Math.floor(Math.random() * (S - 1)) + 1
		let n = Math.floor(Math.random() * N)
		solve(s, n)
	}

}

main();

