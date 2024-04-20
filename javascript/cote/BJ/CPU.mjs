import {readFile} from 'fs/promises'

class MachineCode {
	constructor() {
		this.slot = new Array(16).fill(0);	
	}

	static numberToBinary(number, length) {
		const ret = [];

		while (number >= 1) {
			ret.unshift(number % 2);
			number = Math.floor(number / 2);
		}

		while (ret.length < length) {
			ret.unshift(0);
		}

		return ret.splice(ret.length - length);
	}

	setOpcode(number) {
		const opcode= MachineCode.numberToBinary(number, 5);

		for (let i = 0; i < 5; i++) {
			this.slot[i] = opcode[i];
		}
	}
	
	set first(number){
		const code = MachineCode.numberToBinary(number, 3);

		for (let i = 0; i < 3; i++) {
			this.slot[6 + i] = code[i];
		}
	}

	set second(number){
		const code = MachineCode.numberToBinary(number, 3);

		for (let i = 0; i < 3; i++) {
			this.slot[9 + i] = code[i];
		}
	}

	set third(number){
		const code = MachineCode.numberToBinary(number, 3);

		for (let i = 0; i < 3; i++) {
			this.slot[12 + i] = code[i];
		}
	}

	set constant(number) {
		const code = MachineCode.numberToBinary(number, 4);

		for (let i = 0; i < 4; i++) {
			this.slot[12 + i] = code[i];
		}
	}

	getCode() {
		return this.slot.join("");
	}
};

class Translator {
	constructor(mapper) {
		this.mapper = mapper;
	}

	translate(command) {
		const result = new MachineCode();

		result.setOpcode(this.mapper[command.name]);
		result.first = command.args[0].value;
		
		if (["ADDC", "SUBC", "ANDC", "MULTC", "LSFTLC", "LSFTRC", "ASFTRC", "RLC", "RRC"].includes(command.name)) {
			result.second = command.args[1].value;
			result.constant = command.args[2].value;
		} else if (command.name === "MOVC") {
			result.constant= command.args[1].value;
		} else if (command.name === "MOV") {
			result.third = command.args[1].value;
		} else if (command.name === "NOT") {
			result.third= command.args[1].value;
		} else {
			result.second = command.args[1].value;
			result.third = command.args[2].value;
		}

		return result.getCode()
	}
};	

class CommandName {
	constructor(value) {
		this.value = value
	}
};

class Argument {
	constructor(value){
		this.value = value;
	}
};

class Command {
	constructor(name, a, b, c) {
		this._name = new CommandName(name);
		this.args= Command.processArguments(a, b, c);
	}

	get name() {
		return this._name.value
	}

	static processArguments(a, b, c) {
		const ret = [];

		ret.push(new Argument(a));

		if (b !== 0) {
			ret.push(new Argument(b));
		}

		ret.push(new Argument(c));

		return ret;
	}
};

const mapper = {
	"ADD" : 0,
	"ADDC" : 1,
	"SUB" : 2,
	"SUBC" : 3,
	"MOV" : 4,
	"MOVC" : 5,
	"AND" : 6,
	"ANDC" : 7,
	"OR" : 8,
	"ORC" : 9,
	"NOT" : 10,
	"MULT" : 12,
	"MULTC" : 13,
	"LSFTL" : 14, 
	"LSFTLC" : 15,
	"LSFTR" : 16, 
	"LSFTRC" : 17,
	"ASFTR" : 18, 
	"ASFTRC" : 19, 
	"RL" : 20,
	"RLC" : 21,
	"RR" : 22,
	"RRC" : 23
};

const translator = new Translator(mapper);

function solve(commandLine) {
	const [name, a, b, c] = commandLine.split(" ");

	return translator.translate(new Command(name, parseInt(a), parseInt(b), parseInt(c)));
}

async function main() {
	const data = await readFile('./data/CPU.txt', {encoding: "utf-8"})
		.then(lines => lines.split("\n").map(line => line.trim()));

	let cur = 0;
	const testCases = parseInt(data[cur++]);

	for (let it = 0; it < testCases; it++) {
		const command = data[cur++];
		const answer = data[cur++];
		console.log(answer, solve(command));
	}
}

main()