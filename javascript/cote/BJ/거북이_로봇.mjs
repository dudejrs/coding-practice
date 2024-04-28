import {readFileSync} from 'fs'

const MAX_COMMAND_LENGTH = 500

class Bound {
	constructor(min = 0, max = 0){
		this.min = min
		this.max = max
	}
	
	update(val) {
		if (val > this.max) {
			this.max = val
		} 
		if (val < this.min) {
			this.min = val
		}
	}

	get length() {
		return this.max - this.min
	}
}

class TurtleRobot {
	static dy = [1, 0, -1, 0]
	static dx = [0, 1, 0, -1]

	constructor() {
		this.d = 0
		this.y = 0
		this.x = 0
		this.xBound = new Bound(0, 0)
		this.yBound = new Bound(0, 0)
	}

	rotate(step) {
		this.d = (this.d + step + 4) % 4;
	}

	move(step) {
		this.y += step * TurtleRobot.dy[this.d]
		this.x += step * TurtleRobot.dx[this.d]
		this.#checkBound()
	}

	#checkBound(){
		this.xBound.update(this.x)
		this.yBound.update(this.y)
	}

	get boundArea() {
		return this.xBound.length * this.yBound.length
	}
}

class Command {
	constructor(robot) {
		this.robot = robot
	}
	exec() {
		//do nothing
	}
}

class Forward extends Command {
	constructor(robot) {
		super(robot)
	}
	exec() {
		this.robot.move(1)
	}
}

class BackWard extends Command {
	constructor(robot) {
		super(robot)
	}
	exec() {
		this.robot.move(-1)
	}
}

class RotateClockWise extends Command {
	constructor(robot) {
		super(robot)
	}
	exec() {
		this.robot.rotate(1)
	}
}

class RotateCounteClockWise extends Command {
	constructor(robot) {
		super(robot)
	}
	exec() {
		this.robot.rotate(-1)
	}
}

function createCommand(abbrev, robot) {
	switch (abbrev) {
		case "F" :
			return new Forward(robot)
		case "B" :
			return new BackWard(robot)
		case "L" :
			return new RotateCounteClockWise(robot)
		case "R" :
			return new RotateClockWise(robot)
	}

	return new Command(robot)
}

function solve(commandLine) {
	const robot = new TurtleRobot()
	const commands = commandLine.split("")
		.map(abbrev => createCommand(abbrev, robot))

	for (let command of commands) {
		command.exec()
	}

	return robot.boundArea
}

function main() {
	const data = readFileSync('data/거북이_로봇.txt', {encoding : 'utf-8'})
		.split("\n")

	let cur = 0
	const testCases = parseInt(data[cur++]);

	for (let it = 0; it < testCases; it++) {
		const commandLine = data[cur++]
		const answer = parseInt(data[cur++])
		console.log(answer, solve(commandLine));
	}
}

main()