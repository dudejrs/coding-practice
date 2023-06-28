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

		// 전방선언으로 구현부 선언과 그에 대한 포인터를 가진다
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
	Person::~Person(){delete impl;}

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

	
	struct Renderer {
		virtual void render_circle(float x, float y, float radius){};
	};

	struct VectorRenderer : Renderer {
		void render_circle(float x, float y, float radius)override{
			cout << "Drawing a vector circle of radius " << radius << " at ("<<x <<","<<"y"<<")" << endl;
		}
	};

	struct RasterRenderer : Renderer {
		void render_circle(float x, float y, float radius)override{
			cout << "Rastering circle of radius " << radius << " at ("<<x <<","<<"y"<<")" << endl;
		}
	};

	struct Shape {
		protected : 
			Renderer& renderer;
			Shape(Renderer& renderer) : renderer(renderer){}

		public :
			virtual void draw()=0;
			virtual void resize(float factor) =0;
	};

	struct Circle : Shape {
		
		float x,y,radius;

		void draw() override{
			renderer.render_circle(x,y,radius);
		}
		void resize(float factor) override {
			radius *= factor;
		}

		Circle(Renderer renderer, float x, float y, float radius) 
		: Shape(renderer), x(x), y(y), radius(radius){

		}

	};

	void main(){

		RasterRenderer rr;
		VectorRenderer vr;

		Circle raster_circle(rr, 5,5,5);
		Circle vector_circle(vr, 5,5,5);

		raster_circle.draw();
		vector_circle.draw();
	}
};

int main(void){

	Pimpl::main();
	Bridge::main();

	return 0;
}