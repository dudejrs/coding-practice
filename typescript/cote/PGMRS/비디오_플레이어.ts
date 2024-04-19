const TEST_CASES = 10
const N = 10000

type Time = string;
type Second = number;
type Command = "prev" | "next";
type TimeAmount = number;

class VideoPlayer {
	private static MAXIMUM : Second = 3660;
	private openingStart: Second;
	private openingEnd: Second;
	private current: Second ;

	constructor(openingStart: Time, openingEnd: Time, position: Time) {
		this.openingStart = VideoPlayer.timeToSecond(openingStart);
		this.openingEnd = VideoPlayer.timeToSecond(openingEnd);
		this.current = VideoPlayer.timeToSecond(position)
	}

	static timeToSecond(time: Time): Second {
		const [mm, ss] = time.split(":")
			.map(i => parseInt(i));
		return 60 * mm + ss;
	}

	move(amount: TimeAmount) {
		if (this.current + amount < 0) {
			this.current = 0;
		} else if (this.current + amount > VideoPlayer.MAXIMUM) {
			this.current = VideoPlayer.MAXIMUM;
		} else {
			this.current += amount;
		}

		this.skipIfOpeningSequence()
	}

	get position() {
		const mm = Math.floor(this.current / 60)
		const ss = this.current % 60

		return `${mm}:${ss}`
	}

	private skipIfOpeningSequence() {
		if (this.openingStart <= this.current && this.current <= this.openingEnd) {
			this.current = this.openingEnd;
		}
	}
}

class VideoPlayerCommand {
	private player: VideoPlayer
	private amount: TimeAmount

	constructor(player: VideoPlayer, amount: TimeAmount) {
		this.player = player;
		this.amount = amount
	}

	static create(player: VideoPlayer, command: Command): VideoPlayerCommand {
		switch (command) {
			case "prev" :
				return new VideoPlayerCommand(player, -10);
			case "next" :
				return new VideoPlayerCommand(player, 10);
		}
	}

	exec() {
		this.player.move(this.amount)
	}
}

function initialize(end: Time = "59:59"): Time {
	const [mm, ss] = end.split(":")
		.map(i => parseInt(i));
	let m =  Math.floor(Math.random() * mm);
	let s = Math.floor(Math.random() * ss);

	return `${m}:${s}`;
}

function generateCommands(): Command[] {
	const n = Math.floor(Math.random() * N);
	const ret: Command[] = [];

	for (let i = 0; i < n; i++) {
		let command: Command = Math.random() < 0.5 ? "prev" : "next";
		ret.push(command);
	}

	return ret
}

function solve(openingStart: Time, openingEnd: Time, position: Time, commands: Command[]): Time {
	const player = new VideoPlayer(openingStart, openingEnd, position);

	for (let command of commands) {
		const c = VideoPlayerCommand.create(player, command);
		c.exec()
	}

	return player.position;
}

function main() {
	for (let it = 0; it < TEST_CASES; it++) {
		let openingEnd = initialize();
		let openingStart = initialize(openingEnd);
		let position = initialize();
		let commands = generateCommands();
		console.log(solve(openingStart, openingEnd, position, commands));
	}
}

main()