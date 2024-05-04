import {readFileSync} from 'fs'

class Board {
        
    static EMPTY = "."
    
    constructor(m, n, board) {
        this.m = m
        this.n = n
        this.board = board.map(b => b.split(""))
    }
    
    remove(i, j) {
        for (let y = 0; y < 2; y++) {
            for (let x = 0; x < 2; x++) {
                this.board[i + y][j + x] = Board.EMPTY       
            }
        }
    }
    
    gravity() {
        for (let i = 0; i < this.n; i++) {
            const stack = []
            
            for (let j = 0; j < this.m; j++) {
                if (this.board[j][i] === Board.EMPTY) {
                    continue
                }
                stack.push(this.board[j][i])
            }
            
            for (let j = this.m - 1; j >= 0; j--) {
                if (stack.length != 0) {
                    this.board[j][i] = stack.pop()
                } else {
                    this.board[j][i] = Board.EMPTY
                }
            }
        }
    }
    
    *next() {
        for (let i = 0; i < this.m - 1; i++ ) {
            for (let j = 0; j < this.n - 1; j++) {
                if (this.#matched(i, j)) {
                    yield [i, j]
                }
            }
        }
        return
    }
    
    #matched(i, j) {
        const target = this.board[i][j]

        if (target === Board.EMPTY) {
        	return false
        }
        
        return this.board[i][j + 1] === target && this.board[i + 1][j] === target && this.board[i + 1] [j + 1] === target
    }
    
    get removed() {
        let count = 0
        
        for (let i = 0; i < this.m; i++) {
            for (let j = 0; j < this.n; j++) {
                if (this.board[i][j] === Board.EMPTY) {
                    count++
                }
            }
        }
        return count
    }
}

function solve(m, n, board) {
    var board = new Board(m, n, board)
    
    while (true) {
        const matched = [...board.next()]
        console.log(matched)
        if (matched.length == 0) {
            break
        }
        
        for (let [i, j] of matched) {
            board.remove(i, j)
        }
        board.gravity()
    }
    
    return board.removed
}

function main() {

	const [tc, ...data] = readFileSync('./data/프렌즈_4블록.txt', {encoding : 'utf-8'})
		.split("\n")

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [m, n] = data[cur++].split(" ").map(i => parseInt(i))
		const board = new Array(m).fill(0).map(_ => data[cur++])
		const answer = parseInt(data[cur++])
		console.log(answer, solve(m, n, board))
	}
}

main() 