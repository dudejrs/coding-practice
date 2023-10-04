/* 함수 이름을 circum -> circumreference로 바꾸기 */

function circum(radius){
	return circumreference(radius);
}

function circumreference(radius){
	return 2* Math.pI * radius;
}



/*매개변수를 aCustomer가 아니라 aCustomer.stateCode로 주기*/

const someCustomers = [{address : {stateCode : "MA"}}];
const newEnglanders = someCustomers.filter(c => inNewEngland(c.address.stateCode));

// function inNewEngland(aCustomer){
// 	return["MA","CT", "ME","VI","NH","RI"].includes(aCustomer.address.state);
// }

// function xxinNewEngland(stateCode){
// 	return inNewEngland(stateCode)
// }

function inNewEngland(stateCode){
	return["MA","CT", "ME","VI","NH","RI"].includes(stateCode);
}
