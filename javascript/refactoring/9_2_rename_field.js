/*
	데이터의 필드 이름을 바꾸려고 한다.
	데이터를 캡슐화하고, 데이터 변경에 취약하지 않도록 하시오.
*/

class Organization {
	constructor(data){
		// this._name = data.name;
		this._title = data.title ? data.title : data.name;

		// 모든 데이터를 변환 완료하면 다음과 같이 바꿔준다
		// this._title = data.title;

		this._country = data.country;
	}
	
	// get name() {return this._name;}
	// set name(arg){this._name = arg;}
	
	get title() {return this._title;}
	set title(arg){this._title = arg;}
	get country() {return this._country;}
	set country(arg){this._country = arg;}
}

const getOrganization  = () => new Organization({
	// name: "애크미 구스베리", 
	title: "애크미 구스베리", 
	country: "GB"
	});
const organization = getOrganization()

organization.title = "유니세프 코리아"
organization.country = "KR";
console.log(organization);