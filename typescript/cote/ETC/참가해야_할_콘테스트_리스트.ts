const M = 100
const N = 30000
const P = 1000
const TEST_CASES = 10

type Proficiency = number;

class Contest {
	private problems: Proficiency[]
	public index: number

	constructor(problems: Proficiency[], index: number) {
		this.problems = problems;
		this.index = index
	}

	*[Symbol.iterator]() {
		for (let problem of this.problems) {
			yield problem
		}
	}
}

class ContestList {
	private contests: Contest[] 

	constructor(contests: Contest[]) {
		this.contests = contests;
	}

	static of(data: Proficiency[][]): ContestList {
		let contests = data.map((d, i) => new Contest(d, i));
		return new ContestList(contests);
	}

	*matchedOrder(proficiency: Proficiency) {
		const matchedList = this.contests.map(c => new ExpectedResult(c, proficiency));

		matchedList.sort((r1, r2) => {
				if (r1.solvable != r2.solvable){
					return r2.solvable - r1.solvable;
				}
				return r1.contest.index - r2.contest.index;
		});

		for (let matched of matchedList){
			yield matched.contest;
		}
	}
}

class ExpectedResult {
	contest: Contest
	solvable: number

	constructor(contest: Contest, proficiency: Proficiency) {
		this.contest = contest
		this.solvable = [...contest].filter(level => level <= proficiency).length;
	}
}

function solve(k: number, proficiency: Proficiency, contests: Proficiency[][] ): number[] {
	const contentList  = ContestList.of(contests)
	const ret = [];

	for (let c of contentList.matchedOrder(proficiency)) {
		if (ret.length == k) {
			break;
		}

		ret.push(c.index)
	}
	
	ret.sort((a, b) => a - b)

	return ret;
}

function main() {
	for (let it = 0; it < TEST_CASES; it++) {
		const n = Math.floor(Math.random() * (N - 3)) + 3
		const k = Math.floor(Math.random() * (n - 1)) + 1
		const proficiency = Math.floor(Math.random() * (P - 1)) + 1

		const contests = new Array(n).fill(0)
			.map(_ => {
				const m = Math.floor(Math.random() * (M - 1)) + 1
				return new Array(m).fill(0)
					.map(_ => Math.floor(Math.random() * (P - 1)) + 1)
			})
		console.log(k, proficiency)
		console.log(solve(k, proficiency, contests))
	}
}

main()