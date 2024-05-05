const _awaitUnlock = async(lock: Lock) => {
	if (!lock._locked) {
		return Promise.resolve(true)
	}
	return new Promise((resolve)=> {
		setTimeout(()=> {
			_awaitUnlock(lock).then(() => resolve(true))
		}, 100)
	})
}

class Lock {

	_locked : boolean

	constructor() {
		this._locked = false
	}

	async acquire() {
		await _awaitUnlock(this)
		this._locked = true
	}

	release() {
		this._locked = false
	}
}

class Database {
	private static instance: Database;
	private static lock: Lock = new Lock()

	private constructor() {}

	public static getInstance(): Database {

		if (!Database.instance) {

			this.lock.acquire()

			if (!Database.instance) {
				Database.instance = new Database()
			}
			this.lock.release()
		}


		return Database.instance;
	}
}

function main() {
	const db1 = Database.getInstance();
	const db2 = Database.getInstance();

	console.log(db1 === db2)
}

main()