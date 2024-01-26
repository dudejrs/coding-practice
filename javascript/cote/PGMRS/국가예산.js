
const TEST_CASE = 10
const N = 10 


function* numGenerate(n) {
	while (true){
		yield Math.floor(Math.random() * n)
	}
}

function underBudget(budgets, limit, m){

	let total = 0 ;

	for(let budget of budgets){
		total += (budget < limit) ? budget : limit
	}

	return total <= m;
}

function solve(budgets, m){

	let lo = 0, hi = Math.max(...budgets);

	for(let it=0; it<100; it++) {
		let mid = (lo+hi)/2

		if (underBudget(budgets, mid, m)){
			lo = mid
		} else {
			hi = mid
		}
	}

	return lo
}


let budgetGenerator = numGenerate(100)
let mGenerator = numGenerate(100 * N * 0.8)

for (let i=0; i< TEST_CASE; i++){

	let budgets= [];


	for(let n=0; n< N; n++){
		let { value : budget } = budgetGenerator.next()
		budgets.push(budget)
	}


	let {value : m} = mGenerator.next()

	console.log(solve(budgets, m).toPrecision(3))

} 