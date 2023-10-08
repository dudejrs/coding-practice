/* Person의 내부 컬렉션을 캡슐화하는 메서드를 작성하고 client 코드들을 수정하여라  */

class Person {
	constructor(name){
		this._name = name;
		this._courses = [];
	}
	get name() {return this._name;}
	get courses() {return this._courses.slice();}
	set courses(aList) {this._courses = aList.slice();}

	addCourse(aCourse){
		this._courses.push(aCourse);
	}
	removeCourse(aCourse, fnIfAbscent = ()=>{throw new RangeError()}){
		const index = this._courses.indexOf(aCourse);
		if(index == -1)
			fnIfAbscent();
		else 
			this._courses.splice(index,1);
	}
};

class Course {
	constructor(name, isAdvanced){
		this._name = name;
		this._isAdvanced = isAdvanced;
	}
	get name() {return this._name;}
	get isAdvanced() {return this._isAdvanced;}
};

// --- client Code --

aPerson = new Person("Adam");
filename = ""

function readBasicCourseNames(filename){
	return ["a","b","c"]
}

numAdvancedCourses = aPerson.courses
	.filter(c => c.isAdvanced)
	.length;

const basicCourseNames = readBasicCourseNames(filename);
aPerson.courses = basicCourseNames.map(name => new Course(name.false));

for (const name of readBasicCourseNames(filename)){
	aPerson.addCourse(new Course(name,false));
}

