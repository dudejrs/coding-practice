/* Person에서 TelephoneNumber을 별도의 class로 추출하여라 */

class Person {

	constructor(name, officeAreaCode, officeNumber){
		this._name = name;
		this._officeAreaCode = officeAreaCode;
		this._officeNumber = officeNumber;
		this._telephoneNumber = new TelephoneNumber(officeAreaCode, officeNumber)
	}

	get name() { return this._name;}
	set name(arg) {this._name = arg;}
	get officeAreaCode() { return this._telephoneNumber.officeAreaCode;}
	set officeAreaCode(arg) {this._telephoneNumber.officeAreaCode = arg;}
	get officeNumber() { return this._telephoneNumber.officeNumber;}
	set officeNumber(arg) {this._telephoneNumber.officeNumber = arg;}
	get telephoneNumber() { return this._telephoneNumber.toString();}
}

class TelephoneNumber {
	
	constructor(officeAreaCode, officeNumber){
		this._officeAreaCode = officeAreaCode;
		this._officeNumber = officeNumber;
	}

	get officeAreaCode(){ return this._officeAreaCode;}
	set officeAreaCode(arg){this._areaCode = arg;}
	get officeNumber(){return this._officeNumber;}
	set officeNumber(arg){this._officeNumber = arg;}

	toString(){
		return`(${this.officeAreaCode}) ${this.officeNumber}`;
	}
}


var person = new Person("Tom", 31, 1234567);
console.log(person.telephoneNumber);