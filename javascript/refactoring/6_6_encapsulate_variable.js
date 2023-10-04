 

/* 
	1. 모듈의 전역변수를 접근 통제하는 export 메서드들을을 만들어라 
	이때 Object.assign()을 사용하여 값 복사를 하여라 
*/

 let __defaultOwner = {firstName : "Marthin", lastName : "Pauler"}

function getDefaultOwner(){
 	return Object.assign({}, __defaultOwner);
 }

function setDefaultOwner(arg){
 	__defaultOwner = arg;
 }


// 데이터 참조
let newOwner = getDefaultOwner();

// 데이터 갱신
setDefaultOwner({firstName :"", lastName : ""});

module.exports.getDefaultOwner = getDefaultOwner;
module.exports.setDefaultOwner = setDefaultOwner;




/* 
	2. 모듈의 전역변수를 접근 통제하는 export 메서드들을을 만들어라 
	이때 레코드를 캡슐화하는 방법을 이용하여라 
*/

let __defaultOwner2 = {firstName : "Marthin", lastName : "Pauler"}

class Person {
	constructor(data){
		this.__firstName = data.firstname;
		this.__lastName = data.lastName;
	}

	get firstName(){return this.__firstName;}
	get lastName(){return this.__lastName;}

	set firstName(arg){ this.__firstName = arg;}
	set lastName(arg){ this.__lastName = arg;}
}

function getDefaultOwner2(){
	return new Person(__defaultOwner2);
}

function setDefaultOwner2(arg){
	__defaultOwner2 = arg;
}

// 데이터 참조
let newOwner2 = getDefaultOwner2();

// 데이터 갱신
defaultOwner2 = setDefaultOwner2();

module.exports.getDefaultOwner2 = getDefaultOwner2;
module.exports.setDefaultOwner2 = setDefaultOwner2;

