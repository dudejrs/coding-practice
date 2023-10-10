#include <iostream>
#include <mutex>
#include <vector>
#include <string>

using namespace std;


namespace Observer {

	template<typename T> struct Observer;

	template<typename T>
	struct Observable {
		void subscribe(Observer<T>* observer) {
			lock_guard<mutex> guard {mtx};
			observers.push_back(observer);
		};

		void unsubscribe(Observer<T>* observer){
			if(observers.empty()) return;
			lock_guard<mutex> guard{mtx};
			observers.erase(remove(begin(observers),end(observers),observer));
		}
		
		void notify(T& source, const string& name){
			lock_guard<mutex> guard {mtx};
			for(auto ob : observers)
				ob->field_changed(source, name);
		};

		private :
			vector<Observer<T>*> observers;
			mutex mtx;
	};

	template<typename T> 
	struct Observer {
		virtual void field_changed(T& source, const string& field_name) = 0;
	};

	struct Person : Observable<Person> {
		Person(int age) : age(age){}

		int get_age(){return age;}
		void set_age(const int value){
			age = value;
			notify(*this, "age");
		}

		private : 
			int age;
	};

	struct ConsolePersonObserver : Observer<Person>{
		void field_changed(Person& source, const string& field_name) override {
			if(field_name == "age")
				cout << "Person's "<< field_name << "has changed tp" << source.get_age()<< ".\n";
		}
	};


	void main(void){
		cout << "[Observer]" << endl;
		Person p(20);
		ConsolePersonObserver cpo;
		p.subscribe(&cpo);
		p.set_age(21);
		p.set_age(22);
		p.unsubscribe(&cpo);
		p.set_age(23);
		cout << endl;
	}
}

int main(void){
	Observer::main();

	return 0;
}