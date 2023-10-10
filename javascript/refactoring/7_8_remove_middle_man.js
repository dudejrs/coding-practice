/* Client가 Department를 직접 호출할 수 있게, 위임 메서드들을 모두 제거하라*/


class Person{
	constructor(name, department){
		this._name = name;
		this._department = new Department(department)
	}
	
	get department(){return this._department;}
	set department(arg) {this._department = arg}

	// get manager() { return this._department.manager;}
	// set manager(arg) {this._department.manager = arg;}

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
var manager = aPerson.department.manager
