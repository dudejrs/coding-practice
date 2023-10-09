
/* Order의 price 안의 임시변수 basePrice와 discountFactor을 질의함수로 바꾸어라 */

class Order {
	constructor(quantity, item){
		this._quantity = quantity;
		this._item = item;
	}

	get basePrice() {
		return this._quantity * this._item.price;
	}

	get discountFactor(){
		var discountFactor = 0.98;

		if(this.basePrice >1000) 
			discountFactor -= 0.03;

		return discountFactor;
	}

	get price() {
		return	this.basePrice * this.discountFactor
	}
};

var orders = [new Order(10, {"price" : 500}),new Order(3, { "price" : 250}),new Order(8, { "price" : 125})];

orders.forEach(order => console.log(order.price));