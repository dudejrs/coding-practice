package com.example.cote.PGMRS;

import kotlin.random.*;

val MAX_COMMANDS_LENGTH = 1000000
val TEST_CASES = 10
val random = Random(43)


enum class Direction(
	val dy: Int,
	val dx: Int
	) {
	LEFT(0, -1), TOP(-1, 0), RIGHT(0, 1), BOTTOM(1, 0);

	fun turnLeft(): Direction {
		val cur =  Direction.values().indexOf(this)
		val next = (cur + 3) % Direction.values().size

		return Direction.values().get(next)
	}

	fun turnRight(): Direction {
		val cur =  Direction.values().indexOf(this)
		val next = (cur + 1) % Direction.values().size

		return Direction.values().get(next)
	}

	operator fun component1(): Int = dy
	operator fun component2(): Int = dx
}

class Robot(
	var position : Pair<Int, Int>,
	var direction: Direction
	) {

	fun moveForward() {
		val (y, x) = position
		val (dy, dx) = direction

		position = Pair(y + dy, x + dx)
	}

	fun moveBackward() {
		val (y, x) = position
		val (dy, dx) = direction

		position = Pair(y - dy, x - dx)
	}


	fun turnLeft() {
		direction = direction.turnLeft()
	}

	fun turnRight() {
		direction = direction.turnRight()
	}
}

enum class Command {
		LEFT_TURN {
			override fun exec(robot: Robot) {
				robot.turnLeft()
			}
		}, RIGHT_TURN {
			override fun exec(robot: Robot) {
				robot.turnRight()
			}
		}, GO {
			override fun exec(robot: Robot) {
				robot.moveForward()
			}
		}, BACK {
			override fun exec(robot: Robot) {
				robot.moveBackward()
			}
		}, NULL {
			override fun exec(robot: Robot) {
				// do nothing
			} 
		};

	abstract fun exec(robot: Robot)
}

fun getCommand(abbrev: String) = when (abbrev) {
	"L" -> Command.LEFT_TURN
	"R" -> Command.RIGHT_TURN
	"G" -> Command.GO
	"B" -> Command.BACK
	else -> Command.NULL
}

fun Random.nextIntRange(a: Int, b: Int): Int 
	= nextInt(b - a) + a  

fun Random.nextCommand(): String 
	= listOf("L", "R", "G", "B").get(nextInt(4))

fun solve(commands: List<String>): Pair<Int, Int> {

	val robot = Robot(Pair(0, 0), Direction.BOTTOM)

	for (command in commands) {
		getCommand(command).exec(robot)
	}

	return robot.position;
}

fun main() {
	repeat(TEST_CASES) {
		val n = random.nextIntRange(1, MAX_COMMANDS_LENGTH)
		val commands = List(n) {
			random.nextCommand()
		}

		println(solve(commands))
	}
}