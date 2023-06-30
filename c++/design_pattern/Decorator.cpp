#include <iostream>
#include <sstream>
#include <string>
#include <initializer_list>

using namespace std;


namespace Decorator{
	
	struct Notifier {
		virtual void send(const string& message) =0;
	};

	struct ConcreteNotifier : Notifier {
		void send(const string& message){
			cout << "[ConcreteNotifier] : " << message << endl;
		}
	};

	struct BaseDecorator : Notifier{
		
		BaseDecorator(Notifier& wrapee) : wrapee(wrapee) {}

		void send(const string& message) override{
			wrapee.send(message);
		}

		protected : 
			Notifier& wrapee;
	};

	class SMSDecorator : public BaseDecorator {
		public : 
			
			SMSDecorator(Notifier& wrapee) : BaseDecorator(wrapee){}

			void sendSMS(const string& message){
				cout << "[SMS] :" << message << endl;
			}

			void send(const string& message) override{
				BaseDecorator::send(message);
				sendSMS(message);
			}
	};

	class SlackDecorator : public BaseDecorator {
		public : 
			
			SlackDecorator(Notifier& wrapee) : BaseDecorator(wrapee){}

			void sendSlack(const string& message){
				cout << "[Slack] :" << message << endl;
			}

			void send(const string& message) {
				BaseDecorator::send(message);
				sendSlack(message);
			}
	};
	class FacebookDecorator : public BaseDecorator {
		public : 
			
			FacebookDecorator(Notifier& wrapee) : BaseDecorator(wrapee){}

			void sendFacebook(const string& message){
				cout << "[Facebook] :" << message << endl;
			}

			void send(const string& message) {
				BaseDecorator::send(message);
				sendFacebook(message);
			}
	};

	void main(){

		ConcreteNotifier cn;
		SlackDecorator sd(cn);
		FacebookDecorator fd(sd);
		SMSDecorator smsd(fd);

		smsd.send("hello world");

	}
};

struct Shape {
	virtual string str() const = 0;
};

struct Circle : Shape {
	
	float radius;
	explicit Circle(const float radius) : radius(radius) {}
	void resize(float factor){ radius *= factor;}
	string str() const override {
		ostringstream oss;
		oss << "A circle of radius " << radius;
		return oss.str();
	}

};

namespace DynamicDecortator {

	struct ColorShape : Shape {
		Shape& shape;
		string color; 

		ColorShape(Shape& shape, const string& color) : shape(shape), color(color){}
		ColorShape(Shape&& shape, const string& color) : shape(shape), color(color){}

		string str() const override{
			ostringstream oss;
			oss << shape.str() << " has " << color;
			return oss.str();
		}

	};

	struct TransparentShape : Shape {
		Shape& shape;
		uint8_t transparency; 

		TransparentShape(Shape& shape, const uint8_t transparency) : shape(shape), transparency(transparency){}
		TransparentShape(Shape&& shape, const uint8_t transparency) : shape(shape), transparency(transparency){}

		string str() const override{
			ostringstream oss;
			oss << shape.str() << " has " << static_cast<float>(transparency)/255.f * 100.f << " transparency";
			return oss.str();
		}
	};
	
	void main(){

		cout << "[good Case]"<<endl ;
		TransparentShape c1{
			ColorShape{
				Circle(23), "red"
			}, 128
		};
		cout << c1.str() << endl;


		cout << "[Bad Case]"<<endl ;
		ColorShape c2{
			ColorShape{
				Circle(23), "red"
			}, "green"
		};
		cout << c2.str() << endl;

	}
};

namespace StaticDecorator {


	template <typename T>
	struct ColorShape : T{

		string color;

		template <typename ...Args>
		ColorShape(const string& color, Args...args)
			: T(std::forward<Args>(args)...), color(color){}

		string str() const override {
			ostringstream oss;
			oss << T::str() << " has the color " << color ;
			return oss.str();
		}

	};


	template <typename T>
	struct TransparentShape : T {

		uint8_t transparency;

		template <typename ...Args>
		TransparentShape(uint8_t transparency, Args... args) 
			: T(std::forward<Args>(args)...), transparency(transparency){}

		string str() const override {
			ostringstream oss;
			oss << T::str() << " has the transparency " << transparency / 255.f * 100.f;
			return oss.str();
		}

	};

	void main(){
	
		ColorShape<TransparentShape<Circle>> c3 {"red", 64, 5};
		cout << c3.str() << endl;
	
	}

};

namespace FunctionalDecorator {

	// 1. function 타입이용

	struct Logger {
		function<void()> func;
		string name; 

		Logger(const function<void()>& func, const string& name) 
			: func{func}, name{name} {}

		void operator()() const {
			cout << "Engering " << name << endl;
			func();
			cout << "Exiting " << name << endl;
		}
	};

	// 2. 템플릿 인자 이용

	template<typename Func>
	struct TemplateLogger{
		string name;
		Func func;

		TemplateLogger(const Func& func, const string& name)
			: func{func}, name{name} {}

		void operator()() const {
			cout << "Engering " << name << endl;
			func();
			cout << "Exiting " << name << endl;
		}		
	};

	template <typename Func> auto make_logger ( Func func, const string& name){
		return TemplateLogger<Func>{func, name};
	}	
	
	void main(){

		// 1. function 타입 이용
		cout << "=========" << endl;
		Logger([](){
			cout << "Hello" << endl;
		}, "HelloFunction")();


		// 2. 템플릿 인자 이용
		cout << "=========" << endl;
		auto call = make_logger([](){ cout << "Hello"<<endl;}, "HelloFunction2");
		call();
	}
};


int main(void){

	Decorator::main();
	DynamicDecortator::main();
	StaticDecorator::main();
	FunctionalDecorator::main();

	return 0;
}