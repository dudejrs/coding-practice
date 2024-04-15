const TEST_CASES = 10
const N = 10
const MAX_RUN_SPEED = 13
const MAX_CYCLE_SPEED = 20
const TRACK_LENGTH = 100

type Speed = number
type TrackLength = number
type Record = number

class Player {
	accessor runSpeed: Speed;
	accessor cycleSpeed: Speed;

	constructor(runSpeed: Speed, cycleSpeed: Speed) {
		this.runSpeed = runSpeed;
		this.cycleSpeed = cycleSpeed;
	}

	runTime(runTrackLength: TrackLength): Record {
		return runTrackLength / this.runSpeed;
	} 

	cycleTime(cycleTrackLength: TrackLength): Record {
		return cycleTrackLength / this.cycleSpeed
	}

	time(runTrackLength: TrackLength, cycleTrackLength: TrackLength) {
		return this.runTime(runTrackLength) + this.cycleTime(cycleTrackLength)
	}
}

function initialize(): [Speed[], Speed[]] {
	const runSpeeds = new Array(N).fill(0)
		.map(_ => Math.random() * (MAX_RUN_SPEED * 2 / 5) + MAX_RUN_SPEED * 3 / 5 );
	const cycleSpeeds = new Array(N).fill(0)
		.map(_ => Math.random() * (MAX_CYCLE_SPEED * 2 / 5) + MAX_CYCLE_SPEED * 3 / 5);

	return [runSpeeds, cycleSpeeds];
}

function solve(runSpeeds: Speed[], cycleSpeeds: Speed[]): TrackLength {
	const players: Player[] = new Array(N - 1).fill(0)
		.map((_, i) => new Player(runSpeeds[i], cycleSpeeds[i]));

	const cheater: Player = new Player(runSpeeds[N - 1], cycleSpeeds[N - 1]);

	function diff(runTrackLength: TrackLength) : Record {
		const cycleTrackLength = TRACK_LENGTH - runTrackLength;

		const cheaterRecord = cheater.time(runTrackLength, cycleTrackLength)
		let bestRecord = Number.MAX_VALUE

		for (const player of players) {
			bestRecord = Math.min(bestRecord, player.time(runTrackLength, cycleTrackLength))
		}

		return bestRecord - cheaterRecord
	}

	let [lo, hi] = [0, TRACK_LENGTH]

	for (let i = 0; i < 100; i++) {
		const aab = (lo * 2 + hi) / 3;
		const abb = (lo + 2 * hi) / 3;

		if (diff(aab) < diff(abb)) {
			lo = aab
		} else {
			hi = abb
		}
	}
	
	return (lo + hi) / 2;
}

function main() {
	for (let i = 0; i < TEST_CASES; i++) {
		const [runSpeeds, cycleSpeeds] = initialize();
		console.log(solve(runSpeeds, cycleSpeeds).toFixed(3));
	}
}

main()