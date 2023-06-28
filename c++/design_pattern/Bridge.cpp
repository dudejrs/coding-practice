#include <iostream>
#include <string>

using namespace std;



namespace Pimpl {
	using namespace std;

	/* header */

	// 다른 모듈이 include 하는 header에는 다음과 같은 필요한 public 인터페이스만 적재
	struct Person {
		string name;
		void greet();
		
		Person(string name);
		~Person();

		class PersonImpl;
		PersonImpl* impl;
	};
	


	/* implementation */

	struct Person::PersonImpl{
		void greet(Person* p);
	};

	Person::Person(string name) : impl(new PersonImpl) {
		this->name = name;
	}

	void Person::greet(){
		impl->greet(this);
	}

	void Person::PersonImpl::greet(Person* p){
		cout << "Hello " << p->name << endl;
	}

	void main() {
		Person p1("Tom");
		p1.greet();
	}

};

namespace Bridge{

	struct Circle {
		float x,y,radius;

		void draw() {

		}
		void resize(float factor){

		}

		Circle(float x, float y, float radius) : x(x), y(y), radius(radius){
		}
	};

	void main(){

		Circle raster_circle(5,5,5);
		Circle vector_circle(5,5,5);

		raster_circle.draw();
		vector_circle.draw();
	}
};

int main(void){

	Pimpl::main();
	Bridge::main();

	return 0;
}