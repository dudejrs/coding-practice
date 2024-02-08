const TEST_CASE = 10
const N = 30
const DAY = 1440
const MAX_TIME = 60


class Order {
	constructor(begin, end){
		this.begin = begin
		this.end = end
	}
}


function solve(begin, end) {
	let orders = new Array(begin.length)
		.fill(1)
		.map((_,i)=> new Order(begin[i],end[i]))
		.sort(order => order.end)

	let [earliest, selected] = [0,0]

	for (let order of orders) {
		if (earliest <= order.begin) {
			earliest = order.end
			selected++;
		}
	}

	return selected
}


for (let it = 0; it < TEST_CASE; it++) {
	const n = Math.floor(Math.random() * N / 2) + Math.floor(N/2)
	const begin = new Array(n).fill(1).map(_=> Math.floor(Math.random() * DAY))
	const end = new Array(n).fill(1).map((_,i) => begin[i] + Math.floor(Math.random() * MAX_TIME))
	console.log(solve(begin, end))
}

