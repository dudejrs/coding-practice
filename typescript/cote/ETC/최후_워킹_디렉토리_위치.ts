import {readFile} from "fs/promises"

type Root = "~";
type Parent = "..";
type Current = ".";
type DirectoryName = string | Root | Parent | Current;
type Path = DirectoryName[];
type Commandable = "rmdir" | "cd" | "mkdir";

function isRoot(name: DirectoryName): name is Root {
	return name === "~" || name === "";
}

function isParent(name: DirectoryName): name is Parent {
	return name === "..";
}

function isCurrent(name: DirectoryName): name is Current {
	return name === ".";
}

function exists(child: Directory | undefined): child is Directory {
	return child !== undefined;
}

function isCommandable(keyword: string): keyword is Commandable {
	return ["rmdir", "cd", "mkdir"].includes(keyword);
}

function createCommand(keyword: Commandable, arg: string, c: Console): Command {
	switch(keyword) {
		case "rmdir" : 
			return new RemoveDir(c, arg);
		case "cd" :
			return new ChangeDir(c, arg);
		case "mkdir" :
			return new MakeDir(c, arg);
	}
	return new NullCommand();	
}

class Directory {
	accessor name: DirectoryName
	private _parent: Directory | null
	private children: Directory[] = []
	
	constructor(name: DirectoryName, parent:Directory | null = null) {
		this.name = name
		this._parent = parent
	}

	find(path: DirectoryName[]): Directory  {
		if (path.length === 0) {
			return this
		}

		let child = this._find(path[0])

		if (exists(child)) {
			if (path.length > 1) {
				return child.find(path.splice(1))
			}
			return child
		}
		
		throw new Error()
	}

	private _find(name: DirectoryName): Directory | undefined {
		return this.children.find(child => child.name === name)
	}

	remove(path: DirectoryName[]) {
		let child = this._find(path[0])

		if (exists(child)) {
			if (path.length != 1){
				child.remove(path.splice(1))
				return
			}

			const idx = this.children.indexOf(child!)
			this.children.splice(idx, 1)

			return
		}

		throw new Error()
	}

	create(path: DirectoryName[]) {
		if (path.length == 1) {
			this.children.push(new Directory(path[0], this))
			return
		}

		let child = this._find(path[0])

		if (exists(child)) {
			child.create(path.splice(1))
			return
		}

		throw new Error()
	}

	createRecursive(path: DirectoryName[]) {
		if (path.length == 0) {
			return
		}

		const childrenNames = this.children.map(child => child.name)

		if (!(path[0] in childrenNames)){
			this.children.push(new Directory(path[0], this))
		}

		let child = this._find(path[0])!
		child.createRecursive(path.splice(1))
	}

	get parent() : Directory {
		return this._parent!
	}

	get root(): Directory {
		let cur: Directory = this

		while (cur.parent !== null) {
			cur = cur.parent
		}

		return cur
	}

	get path(): DirectoryName[] {
		let ret = []
		let cur : Directory = this

		while (cur.parent !== null) {
			ret.unshift(cur!.name)
			cur = cur.parent
		}

		return ret
	}
}

class Console {
	accessor workingDirectory: Directory = new Directory("root")
	private pathManager = new PathManager()
	
	constructor(directories: string[]) {
		for (let directory of directories) {
			const d = this.pathManager.resolve(this.workingDirectory, directory)
			this.workingDirectory.createRecursive(d)
		}
	}

	remove(arg: string) {
		const path = this.resolve(arg)
		this.workingDirectory.root.remove(path)
	}

	find(arg: string): Directory {
		const path = this.resolve(arg)
		return this.workingDirectory.root.find(path)	
	}

	create(arg: string) {
		const path = this.resolve(arg)
		this.workingDirectory.root.create(path)
	}

	resolve(arg: string): DirectoryName[] {
		return this.pathManager.resolve(this.workingDirectory, arg);
	}

	current(): string {
		return "/" + this.workingDirectory.path.join("/")
	}
}

class PathManager {
	resolve(currentDirectory: Directory, arg: string): DirectoryName[] {
		let tokens: DirectoryName[] = arg.split("/")

		if(isRoot(tokens[0])) {
			return [...currentDirectory.path, ...tokens.splice(1)]
		}

		if(isParent(tokens[0])) {
			return [...currentDirectory.parent.path, ...tokens.splice(1)]
		}

		if(isCurrent(tokens[0])) {
			return [...currentDirectory.path, ...tokens.splice(1)]
		}

		return [...currentDirectory.path, ...tokens]
	}
}

interface Command {
	execute() : unknown;
}

class RemoveDir implements Command {

	private console: Console
	private arg: string

	constructor(c: Console, arg: string) {
		this.console = c
		this.arg = arg
	}

	execute() {
		try {
			this.console.remove(this.arg)
		} catch(e) {
			// do nothing
		}
	}
}

class ChangeDir implements Command {
	private console: Console
	private arg: string

	constructor(c: Console, arg: string) {
		this.console = c
		this.arg = arg
	}

	execute() {
		try {
			this.console.workingDirectory = this.console.find(this.arg)
		} catch (e) {
			// do nothing
		}
	}
}

class MakeDir implements Command {
	private console: Console
	private arg: string

	constructor(c: Console, arg: string) {
		this.console = c
		this.arg = arg
	}

	execute() {
		try {
			this.console.create(this.arg)
		} catch (e) {
			// do nothing
		}
	}
}

class NullCommand implements Command {
	execute() {
		// do nothing
	}
}

function solve(directories: string[], commands: string[]): string {

	let c = new Console(directories)

	for (let statement of commands) {
		const [keyword, arg] = statement.split(" ")

		if(isCommandable(keyword)) {
			const command = createCommand(keyword, arg, c)
			command.execute()
		}
	}

	return c.current()
}

async function main() {
	const data = await readFile("data/최후_워킹_디렉토리_위치.txt", {encoding : "utf-8"})
		.then(lines => lines.split("\n")
			.map(line => line.trim()));
	let cur = 0;
	const testCases = parseInt(data[cur++]);

	for (let it = 0; it < testCases; it++) {
		const directories = data[cur++].split(" ")
		const numOfCommands = parseInt(data[cur++])
		const commands = new Array(numOfCommands).fill(0)
			.map(_ => data[cur++]);
		const answer = data[cur++];
		console.log(answer, solve(directories, commands))
		cur++;
	}
}

main();