/* 
Customer의 discountRate 필드를 CustomerContract 클래스로 옮겨라
*/


class Customer {
	constructor(name, discountRate){
		this._name = name;
		this._contract = new CustomerContract(dateToday(), discountRate);
		
		// this._discountRate = discountRate;
	}

	get discountRate() { return this._contract.discountRate;}
	
	_setDiscountRate(aNumber){
		// this._discountRate = aNumber;
		this._contract.discountRate = aNumber;
	}

	becomePrefereed() {
		this._setDiscountRate(this.discountRate + 0.03);
	}

	applyDiscount(amount){
		return amount.subtract(amount.multiply(this.discountRate));
	}
};


class CustomerContract {
	constructor(startDate, discountRate){
		this._startDate = startDate;
		this._discountRate = discountRate;
	}

	get discountRate() {return this._discountRate;}
	set discountRate(arg) {return this._discountRate = arg;}
};


class Amount {
	constructor(amount){
		this._amount = amount;
	}

	get amount(){return this._amount;}
	set amount(arg){this._amount = arg ;}

	subtract(a) { return this.amount - a;}

	multiply(a){ return this.amount * a; }
}

function dateToday(){
	return Date.now();
}

customer = new Customer("Tom" , 0.15);
amount = new Amount(100000);
console.log(customer.applyDiscount(amount))
customer.becomePrefereed()
console.log(customer.applyDiscount(amount))
