/* 
특이 케이스를 검사하는 로직을 특이케이스 생성하고 그 객체를 이용하여 리팩토링 하여
*/

class Customer {
	
	constructor({name, billingPlan, paymentHistory}){
		this._name = name;
		this._billingPlan = billingPlan;
		this._paymentHistory = paymentHistory;
	}

	get name () { return this._name }
	get billingPlan() { return this._billingPlan;}
	set billingPlan(arg) { this._billingPlan =  arg;}
	get paymentHistory() { return this._paymentHistory;}
	get isUnknown() {return false;}
}

class UnknownCustomer {
	get isUnknown() {return true;}
	get name() {return "거주지"}
	get billingPlan() {return registery.billingPlan.basic;}
	set billingPlan(arg) {}
}


class Site {
	constructor(customer){
		this._customer = (customer=== "미확인 고객") ? new UnknownCustomer() : customer   ;
	}
	get customer() { return this._customer;}
}


function isUnknown(arg) {

	if(!(arg instanceof Customer) && !(arg instanceof UnknownCustomer) )
		throw new Error(`잘못된 값과 비교 : <${arg}>`);

	return arg.isUnknown;
}

//client 1

site = new Site(new Customer({name : "Bob"}))

const aCustomer = site.customer;
let customerName = aCustomer.name;

//client 2
const plan = aCustomer.billingPlan;

//client 3 
aCustomer.billingPlan = "newPlan";




