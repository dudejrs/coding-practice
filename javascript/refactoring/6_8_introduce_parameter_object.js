
/*
readingOutsideRange의 매개변수중 min,max를 한 객체로 바꾸려고 한다 
*/


const operationPlan = {temparatureFloor : 50, temparatureCeiling: 55}
const station = { name : "281",
					readings : [
						{temp : 47, time : "2016-11-10 09:10"},
						{temp : 53, time : "2016-11-10 09:20"},
						{temp : 58, time : "2016-11-10 09:30"},
						{temp : 53, time : "2016-11-10 09:40"},
						{temp : 51, time : "2016-11-10 09:50"}
					]
				};



class NumberRange {

	constructor(min, max){
		this._min = min;
		this._max = max;
	}

	get min(){return this._min;}
	get max(){return this._max;}
}


// function readingOutsideRange(station, min, max){
// 	return newreadingOutsideRange(station, new NumberRange(min, max))
// }

function readingOutsideRange(station, range){
	return station.readings
		.filter(r => r.temp < range.min || r.temp > range.max);
}

const range = new NumberRange(operationPlan.temparatureFloor, operationPlan.temparatureCeiling);

let alert = readingOutsideRange ( station, range);