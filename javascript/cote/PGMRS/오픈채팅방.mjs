import {readFileSync} from 'fs'

class Command {
    constructor(user) {
        this.user = user
    }
    
    exec() {
        throw new Error("Unsupported")
    }
}

class Enter extends Command {
    constructor(chatroom, user) {
        super(user)
        this.chatroom = chatroom
    }
    exec() {
        this.chatroom.push(Record.Enter(this.user))
    }
}

class Leave extends Command {
    constructor(chatroom, user){
        super(user)
        this.chatroom = chatroom
    }
    
    exec() {
        this.chatroom.push(Record.Leave(this.user))
    }
} 

class ChangeName extends Command {
    constructor(user, rename) {
        super(user)
        this.rename = rename
    }
    
    exec(){
        this.user.name = this.rename
    }
}

class User {
    constructor(id, name) {
        this.id = id
        this.name = name
    }
}

class Chatroom {
    constructor(records= []) {
        this._records = records
    }
    
    push(record) {
        this._records.push(record)
    }
    
    get records() {
        return this._records.map(r => r.build())
    }
}

class Record {
    static Enter(user) {
        return new Record(user, (name) => `${name}님이 들어왔습니다.`)
    }
    static Leave(user){
       return new Record(user, (name) => `${name}님이 나갔습니다.`)
    }
    
    constructor(user, motion) {
        this.user = user
        this.motion = motion
    }
    
    build() {
        return this.motion(this.user.name)
    }
}

function getCommand(chatroom, command, user, name) {
    switch(command) {
            case "Enter" : {
                return new Enter(chatroom, user)
            }
            case "Leave" : {
                return new Leave(chatroom, user)
            }
            case "Change" : {
                return new ChangeName(user, name)
            }
        }
    
    throw new Error("UnSupported")
}

function solve(record) {
    const chatroom = new Chatroom()
    const users = new Map()
    
    for (let r of record) {
        let [command, id, name] = r.split(" ")
        if (!users.has(id)) {
            users.set(id, new User(id, name))
        }
        
        if (command == "Enter") {
            let user = users.get(id)
            user.name = name    
        }
        
        const cmd = getCommand(chatroom, command, users.get(id), name)
        cmd.exec()
    }
    
    return chatroom.records;
}

(function main(){
	const [tc, ...data] = readFileSync('./data/오픈채팅방.txt', {encoding : 'utf-8'}).split("\n")

	const testCases = parseInt(tc)
	let cur = 0

	for (let it = 0; it < testCases; it++) {
		const n = parseInt(data[cur++])
		const records = new Array(n).fill(0).map(_ => data[cur++])
		console.log(solve(records))
	}
})()