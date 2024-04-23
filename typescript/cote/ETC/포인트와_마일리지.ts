
const MAX_CHARGE_AMOUNT = 1000000
const TEST_CASE = 10
const MAX_PAYMENTS_LENGTH = 10000
const MAX_DATE = 31
const MAX_AMOUNT = 1000000
const MAX_TIME = 31 * 24 * 60

type Date = number;
type TimeString = string;
type Time = number;
type Amount = number;
type Payment = [Date, TimeString, Amount];
type Point = number;
type Mileage = number;

class Member {
	chargeAmount: Amount
	totalCharged: Amount = 0
	totalPurchased: Amount = 0
	point: Point = 0
	mileage: Mileage = 0

	constructor( chargeAmount: Amount) {
		this.chargeAmount = chargeAmount;
	}
	
	purchase(amount: Amount) {
		if (this.point < amount) {
			this.charge(amount)
		}

		this.point -= amount
		this.totalPurchased += amount
	}

	withDraw(amount: Amount) {
		this.point = (this.point >= amount) ? this.point - amount : 0;
	}

	private charge(amount : Amount) {

		while (amount > 0) {
			this.point +=  this.chargeAmount;
			this.totalCharged += this.chargeAmount;
			amount -= this.chargeAmount;
		}
	}
};

interface Event {
	time: Time,
	exec(member: Member): void
}

class PurchaseEvent implements Event {

	time: Time
	amount: Amount

	constructor(time: Time, amount: Amount) {
		this.time = time;
		this.amount = amount;
	}

	exec(member: Member) {
		member.purchase(this.amount);
	}
}

class WithDrawalEvent implements Event {
	time: Time
	amount: Amount

	constructor(time: Time, amount: Amount) {
		this.time = time;
		this.amount = amount;
	}

	exec(member: Member) {
		member.withDraw(this.amount);
	}
}

class MileageEvent implements Event {
	time: Time
	amount: Amount

	constructor(time: Time, amount: Amount) {
		this.time = time
		this.amount = amount
	}

	exec(member: Member) {
		member.mileage += this.amount;
	}
}

class PiriorityQueue<T> {

	private data: T[]
	private compare: (a: T, b: T) => number

	constructor(data: T[], compareFun: (a:T, b: T) => number){
		this.compare = compareFun;
		this.data = data;
	}
	
	push(item: T) {
		if (this.isEmpty()) {
			this.data.push(item)
			return
		}

		this.data.push(item);
		this.bubbleUp(this.data.length - 1)
	}

	pop(): T | null | undefined {
		if (this.data.length == 1) {
			return this.data.pop()
		}

		const ret = this.data[0]

		this.data[0] = this.data.pop()!;
		this.bubbleDown(0);

		return ret
	}

	isEmpty(): boolean {
		return this.data.length == 0;
	}

	private bubbleDown(cur: number) {
		if (cur >= this.data.length) {
			return
		}

		const [left, right] = [2 * cur + 1, 2 * cur + 2]
		let min = cur
		
		if (left < this.data.length) {
			if (this.compare(this.data[left], this.data[min]) < 0) {
				min = left;
			}
		} 
		if (right < this.data.length) {
			if (this.compare(this.data[right], this.data[min]) < 0) {
				min = right;
			}
		}

		if (cur != min) {
			this.swap(cur, min)
			this.bubbleDown(min)
		}
	}

	private bubbleUp(cur: number) {
		if (cur == 0) {
			return
		}
		const parent = Math.floor((cur + 1) / 2 - 1)

		if (this.compare(this.data[cur], this.data[parent]) < 0) {
			this.swap(cur, parent)
			this.bubbleUp(parent)
		}

	}

	private swap(i: number, j: number) {
		const tmp = this.data[i];
		this.data[i] = this.data[j];
		this.data[j] = tmp
	}
}

function createEvent(payment: Payment): Event[] {
	const [date, timeString, amount] = payment;

	function calculateTime(date: Date, time: TimeString): Time {
		let [mm, ss] = time.split(":")
			.map(i => parseInt(i))
		return date * 1440 + mm * 60 + ss;
	} 

	function twoDaysAfter(time: Time) {
		return time + 1440 * 2;
	}

	function calculateMieleage(amount: Amount) {
		return Math.floor(amount / 10);
	}

	const time = calculateTime(date, timeString);

	if (amount >= 0) {
		return [new PurchaseEvent(time, amount),
			new MileageEvent(twoDaysAfter(time),  calculateMieleage(amount))
			];
	}

	return [new WithDrawalEvent(time, -amount)];
}

function initialize(): Payment[] {
	const ret: Payment[] = [] ;

	const n = Math.floor(Math.random() * (MAX_PAYMENTS_LENGTH - 1)) + 1;

	for (let i = 0; i < n; i++) {
		let date = Math.floor(Math.random() * (MAX_DATE - 1)) + 1;
		let time = `${Math.floor(Math.random() * 24)}:${Math.floor(Math.random() * 60)}`;
		let amount = 100 * (Math.floor(Math.random() * MAX_AMOUNT * 4 / 5 / 1000) - Math.floor(MAX_AMOUNT / 5 / 1000));
		ret.push([date, time, amount]);
	}

	ret.sort((a, b) => {
		if (a[0] != b[0]) {
			return a[0] - b[0];
		}
		return a[1] < b[1] ? -1 : 1;
	});

	return ret;
}

function solve(chargeAmount: Amount, payments: Payment[]): [Amount, Amount, Point, Mileage] {
	const member = new Member(chargeAmount);
	const eventq = new PiriorityQueue<Event>([], (a, b) => a.time - b.time)

	for (let payment of payments) {
		for (let event of createEvent(payment)) {
			eventq.push(event)
		}
	}

	let current = 0;
	while(!eventq.isEmpty()) {
		if (current >= MAX_TIME) {
			break;
		}

		const event = eventq.pop();

		if (event) {
			event.exec(member);
			current = event.time 
		}
	}

	return [member.totalPurchased, member.totalCharged, member.point, member.mileage];
}

function main() {
	for (let it = 0; it < TEST_CASE; it++) {
		const chargeAmount = Math.floor(Math.random() * MAX_CHARGE_AMOUNT / 1000) * 1000;
		const payments = initialize();
		console.log(solve(chargeAmount, payments));
	}
}

main()