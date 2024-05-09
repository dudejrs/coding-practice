class Database {
	private static DatabaseHolder = {
		db : new Database()
	}

	private constructor() {}

	static getInstance() {
		return Database.DatabaseHolder.db
	}
}

function main() {
	const db1 = Database.getInstance();
	const db2 = Database.getInstance();

	console.log(db1 === db2)
}

main()