import {readFile} from 'fs/promises';

type Position = [number, number];

type Direction = "UPLEFT" | "UP" | "UPRIGHT" | "LEFT" | "RIGHT" | "DOWNLEFT" | "DOWN" | "DOWNRIGHT";

const Directions =  {
	UPLEFT : [-1, -1],
	UP : [-1, 0],
	UPRIGHT : [-1, 1],
	LEFT : [0, -1],
	RIGHT : [0, 1],
	DOWNLEFT : [1, -1],
	DOWN : [1, 0],
	DOWNRIGHT : [1, 1],
} as const satisfies Record<Direction, Position> 

function solve(boards: string[], words: string[]): Position[] {
	let set : Set<Position> = new Set();
	const [row, col] = [boards.length, boards[0].length];

	function outside(cur: Position) {
		const [y, x] = cur;

		return y < 0 || y >= row || x < 0 || x >= col;
	}

	function dfs(cur: Position, word: string): boolean {
		if (outside(cur)) {
			return false;
		}
		const [y, x] = cur

		if (word[0] != boards[y][x]) {
			return false;
		}
		if (word.length === 1) {
			return true;
		}

		for (let [dy, dx] of Object.values(Directions) ) {
			const next: Position = [y + dy, x + dx];

			if (dfs(next, word.slice(1))) {
				return true;
			}
		}

		return false;
	}

	for (let word of words) {
		for (let i = 0; i < row; i++) {
			for (let j = 0; j < col; j++ ){
				if (dfs([i, j], word)) {
					set.add([i, j]);
				}
			}
		}
	}

	return [...set];
}

async function main() {
	const data  = await readFile("data/보글게임.txt", {encoding : 'utf-8'})
		.then( lines => lines.split("\n")
			.map(line => line.trim()));
	let cur = 0;
	const testCases = parseInt(data[cur++]);

	for (let it = 0; it < testCases; it++) {
		const [y, x] = data[cur++].split(" ")
			.map(i => parseInt(i));
		const board: string[] = new Array(y).fill(0)
			.map(_ => data[cur++]);
		const words: string[] = data[cur++].split(" ");
		console.log(solve(board, words));
	}
}

main() 