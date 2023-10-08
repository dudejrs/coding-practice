/* Order의 priority를 전용 클래스를 만들어서 다음과 같은 기능을 추가하여라 
	1. priority가 가질 수 있는 value를 "low", "normal", "high", "rush"만 받을 수 있도록 한정하고
	2. priority의 값을 비교할 수 있는 operation을 제공하여
*/

class Priority{
	constructor(value){
		if (value instanceof Priority) return value;
		if ( Priority.legalValues().includes(value)) 
			this._value = value;
		else 
			throw new Error(`'${value}' 는 유효하지 않는 데이터입니다.`)
	}

	static legalValues() { return ["low", "normal", "high", "rush"];}

	get _index(){return Priority.legalValues().findIndex(s => s === this._value)}

	equals(other){return other._index === this._index; }
	higherThan(other){return this._index > other._index;}
	lowerThan(other){return this._index < other._index;}
	toString(){
		return this._value;
	}
};

class Order{
	constructor(data){
		this.priority = new Priority(data.priority);
	}

	get priority(){return this._priority;}
	set priority(aString){this._priority = new Priority(aString);}
	get priorityString(){return this._priority.toString();}
};


order = [{priority : "high"},{priority : "low"},{priority : "rush"}].map( data => new Order(data));

highPriorityCount = order.filter( o => o.priority.higherThan(new Priority("normal")))
						.length;

console.log(highPriorityCount)