class Database {
	private static instance: Database;

	private constructor() {}

	public static getInstance(): Database {
		if (!Database.instance) {
			Database.instance = new Database()
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