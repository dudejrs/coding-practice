/* 
	client코드 1,2,3 에서 사용되는 
	공통으로 사용되는 reading 데이터를 조작하는 함수들을 긴밀히 하나의 변환함수로 옮긴다 
*/

// 깊은 복사를 하는 함수(lodash와 같은 라이브러리 이용)
var cloneDeep = function(original){return original;}

reading = { customer : "ivan", quantity : 10, month : 5, year : 2017 };

function acquireReading(){
	return Object.assign({},reading);
}
function baseRate(month, year){ return 0.1 * Math.min(5, year-2010) + 0.01 * Math.min(12, month); }
function taxThreshold(year){return 0.02 - 0.001 * Math.min(12,year-2010)}
function calculateBaseCharge(aReading){
	return baseRate(aReading.month, aReading.year) * aReading.quantity;
}


function enrichReading(rawReading) {
	const result = cloneDeep(rawReading);
	result.baseCharge = calculateBaseCharge(rawReading);
	result.taxableCharge = Math.max(0, result.baseCharge- taxThreshold(result.year));
	return result;
}

// client 1 
const rawReading1 = acquireReading();
const aReading1 = enrichReading(rawReading1);
const baseCharge = aReading1.baseCharge;

// clinet 2 
const rawReading2 = acquireReading();
const aReading2 = enrichReading(rawReading2);
const base = aReading2.baseCharge;
const taxableCharge = aReading2.taxableCharge;

// client 3
const rawReading3 = acquireReading();
const aReading3 = enrichReading(rawReading3);
const basicChargeAmount = aReading3.baseCharge;

// function calculateBaseCharge(aReading){
// 	return baseRate(aReading.month, aReading.year) * aReading.quantity;
// }

