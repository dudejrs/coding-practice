/* 
	client코드 1,2,3 에서 사용되는 
	공통으로 사용되는 reading 데이터를 조작하는 함수들을 긴밀히 하나의 클래스로 옮긴다
*/


reading = {customer : "ivan", quantity : 10, month : 5, year : 2017};

function acquireReading(){
	return Object.assign({},reading);
}
function baseRate(month, year){ return 0.1 * Math.min(5, year-2010) + 0.01 * Math.min(12, month); }
function taxThreshold(year){return 0.02 - 0.001 * Math.min(12,year-2010)}


class Reading {
	constructor(data) {
		this._customer = data.customer;
		this._quantity = data.quantity;
		this._month = data.month;
		this._year = data.year;
	}

	get customer() {return this._customer;}
	get quantity() {return this._quantity;}
	get month() {return this._month;}
	get year() {return this._year;}

	get baseCharge(){return  baseRate(this.month, this.year) * this.quantity;}

};



// client 1
const aReading1 = new Reading(acquireReading());
const baseCharge = aReading1.baseCharge;


// client 2
const aReading2 = new Reading(acquireReading());
const taxableCharge = Math.max(0, aReading2.baseCharge - taxThreshold(aReading2.year));

// client 3
const aReading3 = new Reading(acquireReading());
const basicChargeAmount = aReading3.baseCharge;

// function caculateBaseCharge(aReading){
// 	return baseRate(aReading.month, aReading.year) * aReading.quantity;
// }

