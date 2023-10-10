/* 외부 클라이언트에게 Department의 존재를 숨겨라*/

class Person{
	constructor(name, department){
		this._name = name;
		this._department = new Department(department)
	}
	
	get manager() { return this._department.manager;}
	set manager(arg) {this._department.manager = arg;}
	
	// get department() { return this._department;}
	// set department(arg) { this._department = arg;}
}

class Department{

	constructor(data){
		this._manager = data.manager
	}

	get manager() {return this._manager;}
	set manager(arg){this._manager =  arg;}
}


aPerson = {
	name : "Adam",
	department : {
		manager : "david"
	}
};
var manager = aPerson.manager
