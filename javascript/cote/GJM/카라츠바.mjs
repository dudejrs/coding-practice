
const TEST_CASE = 10
const MAX_SIZE = 1000

// 십진수 각자리의 숫자를 나타내는 배열을 생성([1, 2, 3] -> 321)
function initialize() {
	return new Array(Math.floor(Math.random() *  (MAX_SIZE - 1) + 1))
		.fill(1)
		.map(i => Math.floor(Math.random() * 10))
}

function normalize(a) {
	a.push(0)

	for (let i = 0; i < a.length - 1; i++) {
		if (a[i] < 0) {
			const borrow = Math.floor((Math.abs(a[i]) + 9) / 10)
			a[i + 1] -= borrow
			a[i] += borrow * 10

		} else {
			a[i + 1] += Math.floor(a[i] / 10)
			a[i] = a[i] % 10 
		}
	}

	while (a.at(a.length - 1) == 0){
		a.pop()
	}

	return a
}

function multiply(a, b) {
	const ret = new Array(a.length + b.length + 1).fill(0)

	for (let i = 0; i < a.length; i++) {
		for (let j = 0; j < b.length; j++){
			ret[i+j] += a[i] * b[j]
		}
	}

	return normalize(ret)
}

function add(a, b, k) {
	const ret = new Array(Math.max(a.length, b.length + k)).fill(0)

	for (let i = 0; i < a.length; i++){
		ret[i] = a[i]
	}

	for (let i = 0; i < b.length; i++) {
		ret[i + k] += b[i]
	}

	return normalize(ret)
}

function sub(a, b) {

	if (a.length < b.length) {
		return []
	}

	const ret = [...a]

	for (let i = 0; i < b.length; i++){
		ret[i] -= b[i]
	}

	return normalize(ret)
}

// a와 b를 곱한 숫자를 반환
function karastuba(a, b) {

	if (a.length < b.length) {
		return karastuba(b, a)
	}
	if (a.length == 0 || b.length == 0){
		return [0]
	}
	if (a.length < 50){
		return multiply(a,b);
	}

	const mid = Math.floor(a.length / 2)
	const a0 = a.slice(0, mid)
	const a1 = a.slice(mid)
	const b0 = b.slice(0, Math.min(b.length, mid))
	const b1 = b.slice(Math.min(b.length, mid))

	const z0 = karastuba(a0, b0)
	const z2 = karastuba(a1, b1)

	let z1 = karastuba(add(a0, a1, 0), add(b0, b1, 0))
	z1 = sub(z1, z2)
	z1 = sub(z1, z0)

	let ret = add(z0, z1, mid)
	ret = add(ret, z2, mid * 2)

	return ret
}

function toString(a) {
	return a.toReversed().join("")
}

for (let it = 0; it < TEST_CASE; it++) {
	const a = initialize()
	const b = initialize()

	console.log(`${toString(a)} * ${toString(b)} = ${toString(karastuba(a,b))}\n`)

}