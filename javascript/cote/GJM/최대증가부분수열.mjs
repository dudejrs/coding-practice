
const TEST_CASE = 10
const MAX_LENGTH = 20
const MAX_VALUE = 100


const cache = new Array(MAX_LENGTH+1)

function search(i, v){
	
	let ret = cache[i+1] 

	if( ret != -1){
		return ret;
	}


	ret = 1 

	for (let start = i+1; start<v.length; start++){
		if ( i == -1 || v[i] < v[start]) {
			ret = Math.max(ret, 1 + search(start, v))
		}
	}

	cache[i+1] = ret

	return ret;
}


function solve(v){

	cache.fill(-1)

	return search(-1,v);
}


for (let i=0; i<TEST_CASE; i++){

	const n = Math.floor(Math.random() * MAX_LENGTH)
	const v = new Array(n).fill(1).map(i => Math.floor(Math.random() * MAX_VALUE))

	console.log(solve(v))

}