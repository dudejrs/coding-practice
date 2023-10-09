#include <iostream>

using namespace std;

struct Logger {
	virtual ~Logger() = default;
	virtual void info(const string& s) = 0;
	virtual void warn(const string& s) = 0;
};


namespace NullObject{

	struct NullLogger : Logger {
		void info(const string& s) override {}
		void warn(const string& s) override {}
	};


	struct BankAccount {
		std::shared_ptr<Logger> logger;
		string name;
		int balance = 0;
		
		BankAccount(const shared_ptr<Logger>& logger, const string& name, int balance)
			:logger(logger), name(name), balance(balance){}

		void deposit(int amount){
			balance += amount;
			logger->info("Deposited % "+ to_string(amount) + " to " + name + ", balance is now $"+to_string(balance) );
		}

	};
	void main(void){
		cout << "[NullObject]" << endl;

		shared_ptr<NullLogger> s = make_shared<NullLogger>();
		BankAccount ba1(s, "John", 10000);
		ba1.deposit(3000);

		shared_ptr<NullLogger> empty_pointer;
		BankAccount ba2(empty_pointer, "Jane", 5000);
		// ba2.deposit(3000)  //비어있는 포인터를 전달했을 떄 런타임 오류가 발생할 수 있음. 위엄한 방법이다 

		cout <<endl;
	}

};

namespace ImplicitNullObject{

	struct OptionalLogger : Logger{

		shared_ptr<Logger>impl;
		static shared_ptr<Logger> no_logging;

		OptionalLogger(const shared_ptr<Logger>& logger) : impl(logger){}
		
		void info(const string& s) override {
			if(impl) impl->info(s);
		}

		void warn(const string& s) override {
			if(impl) impl->warn(s);
		}
	};

	struct BankAccount {
		std::shared_ptr<Logger> logger;

		static shared_ptr<OptionalLogger> no_logging;

		string name;
		int balance = 0;
		
		BankAccount( const string& name, int balance,
			const shared_ptr<Logger>& logger = no_logging)
			:logger(make_shared<OptionalLogger>(logger)), name(name), balance(balance){

			}

		void deposit(int amount){
			balance += amount;
			logger->info("Deposited % "+ to_string(amount) + " to " + name + ", balance is now $"+to_string(balance) );
		}
	};

	shared_ptr<Logger> OptionalLogger::no_logging{};
	shared_ptr<OptionalLogger> BankAccount::no_logging{};

	void main(void){
		cout << "[ImplicitNullObject]" << endl;

		BankAccount ba("Jane", 5000);	
		ba.deposit(10000);

		BankAccount ba2("James", 5000, OptionalLogger::no_logging);	
		ba2.deposit(10000);

		cout <<endl;
	}
};


int main(void){

	NullObject::main();
	ImplicitNullObject::main();

	return 0;
}