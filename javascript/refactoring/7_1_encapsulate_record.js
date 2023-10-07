/* 
1. 간단한 레코드를 캡슐화하라
*/

class Organization {
	constructor(data){
		this._name = data.name;
		this._country = data.country;
	}

	get name(){return this._name;}
	get country(){return this._country;}
	set name(arg){this._name = arg;}
};

const raw_organization = {name : "애크미 구스베리", country : "GB"};
const organization = new Organization(raw_organization)

function getOrganization(){return organization;}

result = '';
newName= '에구미 쿠스페리';
result += `<h1>${getOrganization().name}</h1>`;
getOrganization().name = newName;



/* 
2. 중첩된 레코드를 캡슐화하라
*/


function cloneDeep(data){
	return data;
}

class CustomerData {
	constructor(data){
		this._data = data;
	}

	setUsage(customerID,year,month,amount){
		this._data[customerID].usages[year][month] = amount;
	}
	get rawData() {
		return cloneDeep(this._data)
	}

	getUsage(customerID, year, month){
		return this._data[customerID].usages[year][month];
	}
}

let customerData = new CustomerData({
	"1920" : {
		name : "마틴 파울러",
		id : "1920",
		usages : {
			"2016" : {
				"1" : 50,
				"2" : 55,
			},
			"2015" : {
				"1" : 70,
				"2" : 63,
			}
		}
	} 
});


function getCustomerData(){return customerData;}

// function getRawDataOfCustomers(){return customerData.rawData;}
// function setRawDataOfCustomers(arg){customerData._data = arg}

// function setUsage(customerID, year,month,amounth){
// 	getCustomerData().setUsage(customerID,year,month,amount);
// }
// function getUsage(customerID, year, month){
// 	return getCustomerData().getUsage(customerID,year,month);
// }


customerID = 1920;
year = 2016;
month = 2;
amount = 100;
getCustomerData().setUsage(customerID,year,month,amount);

function compareUsage(customerID, laterYear, month) {
	const later = getCustomerData().getUsage(customerID,year,month);
	const earlier = getCustomerData().getUsage(customerID,year-1,month);
	return {lastAmount : later, change : later - earlier};
}

console.log(compareUsage(customerID, year,month));