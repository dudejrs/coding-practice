var assert = require('assert')

/* 
	case1 : 다른 인스턴스 변수를 이용하여 계산되는 production을 파생 인스턴스 변수로 바꾸어라 
*/

// origin
class ProductionPlan {
	constructor(){
		this._adjustments = [];
	}
	
	get production(){
		// assert(this._production == this.calculatedProduction)
		return this._adjustments.reduce((sum,a)=> sum + a.amount, 0);
	}

	// get calculatedProduction() {
	// 	return this._adjustments
	// 				.reduce((sum, a)=> sum+a.amount, 0);
	// }

	applyAdjustment(anAdjustment){
		this._adjustments.push(anAdjustment);
	}
}


adjustments = [{amount : 100},{amount : 150},{amount : 200},{amount : 250}];
productionPlan = new ProductionPlan();
for( adjustment of adjustments){
	productionPlan.applyAdjustment(adjustment)
}
console.log(productionPlan.production)


// case2 : 두개의 인스턴스 변수를 이용하여 계산되는 production을 파생 인스턴스 변수로 바꾸어라

class ProductionPlan2 {
	constructor(production) {
		this._initialProduction = production
		this._adjustments = [];
	}

	get production() { 
		// assert(this._production, this.calculatedProduction)
		return this._adjustments.reduce((sum,a)=> sum + a.amount, this._initialProduction);
	}

	// get calculatedProduction(){
	// 	return this._adjustments.reduce((sum,a)=> sum + a.amount, this._initialProduction);
	// }

	applyAdjustment(anAdjustment){
		this._adjustments.push(anAdjustment);
	}
}

adjustments = [{amount : 100},{amount : 150},{amount : 200},{amount : 250}];
productionPlan2 = new ProductionPlan2(1000);
for( adjustment of adjustments){
	productionPlan2.applyAdjustment(adjustment)
}
console.log(productionPlan2.production)
