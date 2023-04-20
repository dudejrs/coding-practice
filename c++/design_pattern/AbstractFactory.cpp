#include <iostream>
#include <map>
#include <cmath>
#include <initializer_list>

using namespace std;

/* 1. 추상 팩터리  */
	/*	- 하나의 객체가 아닌 연관된 여러종류의 객체들을 생성해야 할 경우	*/

namespace AbstractFactory{

	struct HotDrink{
		virtual ~HotDrink(){}
		virtual void prepare(int volume) = 0;
	};

	struct Tea : HotDrink{
		void prepare(int volume) override {
			std::cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon" << std::endl;
		}
	};

	struct Coffee : HotDrink{
		void prepare(int volume) override {
			std::cout << " Coffee" << volume << "ml" << std::endl;
		}
	};


	// Bad Case
	unique_ptr<HotDrink> make_drink(string type){
		unique_ptr<HotDrink> drink;
		if(type == "tea"){
			drink = make_unique<Tea>();
			drink->prepare(200);
		}else if( type =="coffee"){

			drink = make_unique<Coffee>();
			drink->prepare(50);
		}

		return drink;
	}

	//Good Case
	struct HotDrinkFactory{
		virtual ~HotDrinkFactory(){}
		virtual unique_ptr<HotDrink> make() const = 0;
	};

	struct CoffeeFactory : HotDrinkFactory{
		unique_ptr<HotDrink> make() const override{
			return make_unique<Coffee>();
		}
	};
	struct TeaFactory : HotDrinkFactory{
		unique_ptr<HotDrink> make() const override{
			return make_unique<Tea>();
		}
	};

	class DrinkFactory{
		map < string, unique_ptr<HotDrinkFactory> > hot_factories;

		public : 
			DrinkFactory(){
				hot_factories["coffee"] = make_unique<CoffeeFactory>();
				hot_factories["tea"] = make_unique<TeaFactory>();
			}

			unique_ptr<HotDrink> make_drink(const string& name ){
				auto drink = hot_factories[name]->make();
				drink->prepare(200);

				return drink;
			}
	};

	void do_abstract_factory(){
		DrinkFactory my_factory;
		auto my_drink = my_factory.make_drink("tea");
	}
}


/* 2. 함수형 팩터리  */
	/*	- 하나의 객체가 아닌 연관된 여러종류의 객체들을 생성해야 할 경우	*/


namespace FunctionalFactory{

	struct HotDrink{
		virtual ~HotDrink(){}
		virtual void prepare(int volume) = 0;
	};

	struct Tea : HotDrink{
		void prepare(int volume) override {
			std::cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon" << std::endl;
		}
	};

	struct Coffee : HotDrink{
		void prepare(int volume) override {
			std::cout << " Coffee" << volume << "ml" << std::endl;
		}
	};


	// Bad Case
	unique_ptr<HotDrink> make_drink(string type){
		unique_ptr<HotDrink> drink;
		if(type == "tea"){
			drink = make_unique<Tea>();
			drink->prepare(200);
		}else if( type =="coffee"){

			drink = make_unique<Coffee>();
			drink->prepare(50);
		}

		return drink;
	}

	//Good Case
	struct HotDrinkFactory{
		virtual ~HotDrinkFactory(){}
		virtual unique_ptr<HotDrink> make() const = 0;
	};

	struct CoffeeFactory : HotDrinkFactory{
		unique_ptr<HotDrink> make() const override{
			return make_unique<Coffee>();
		}
	};
	struct TeaFactory : HotDrinkFactory{
		unique_ptr<HotDrink> make() const override{
			return make_unique<Tea>();
		}
	};

	class DrinkFactory{
		map < string, unique_ptr<HotDrinkFactory> > hot_factories;

		public : 
			DrinkFactory(){
				hot_factories["coffee"] = make_unique<CoffeeFactory>();
				hot_factories["tea"] = make_unique<TeaFactory>();
			}

			unique_ptr<HotDrink> make_drink(const string& name ){
				auto drink = hot_factories[name]->make();
				drink->prepare(200);

				return drink;
			}
	};

	class DrinkWithVolumeFactory{
		map < string, function<unique_ptr<HotDrink>()> > factories;

		public : 
			DrinkWithVolumeFactory(){
				factories["tea"] = []{
					auto tea = make_unique<Tea>();
					tea->prepare(200);
					return tea;
				};

				factories["coffee"] =[]{
					auto coffee = make_unique<Coffee>();
					coffee->prepare(50);
					return coffee;
				};
			}
			inline unique_ptr<HotDrink> make_drink(const string& name){
				return factories[name]();
			}
	};


	void do_functional_factory(){
		DrinkWithVolumeFactory x;
		auto drink = x.make_drink("coffee");
	}
}




int main(void){

	AbstractFactory::do_abstract_factory();
	FunctionalFactory::do_functional_factory();

	return 0;
}