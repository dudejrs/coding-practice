#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>

using namespace std;

namespace CommandImplementation {
	struct Command {
		virtual void execute()=0;
	};

	struct CommandReciever {
		void do_something(const string& a){
			cout << "Reciever : "<< a << endl;
		}
	};

	struct ComplexCommand : public Command{
		ComplexCommand(CommandReciever* receiver, const string& a, const string& b)
			:receiver(receiver), a(a), b(b){}
		
		void execute()override{
			this->receiver->do_something(a);
			this->receiver->do_something(b);
		}

		protected :
			CommandReciever* receiver; 
			string a, b;
	};
	class CommandHistory {
		vector<Command*> history;

		public :
			void push(Command* cmd){history.push_back(cmd);}
			void pop(){}
	};

	struct Command1  : public Command{
		void execute() override { cout << "command1" << endl;}
	};
	struct Command2  : public Command{
		void execute() override { cout << "command2" << endl;}
	};
	struct Command3 : public ComplexCommand {
		Command3(CommandReciever* receiver, const string& a, const string& b) : ComplexCommand(receiver,a,b){}
	};


// 도메인 객체
	class CommandInvoker {
 		Command* on_start_;
 		Command* on_finish_;
 		CommandHistory history;
 		
 		public : 
		 	void set_on_start(Command* command){ this->on_start_ = command;}
		 	void set_on_finish(Command* command){ this->on_finish_ = command;}
		 	void do_something(Command* command) {
		 		if(this->on_start_) this->on_start_->execute();
				history.push(command);
				command->execute();
		 		if(this->on_finish_) this->on_finish_->execute();
		 	
			};
	};

	void main(){
		CommandInvoker ci;
		ci.set_on_start(new Command1());
		ci.set_on_finish(new Command2());
		CommandReciever rcv;
		ci.do_something(new Command3(&rcv, "Hello World", "End"));
	}
};
namespace CommandImplementation2 {

	struct BankAccount {

		int balance = 0;
		int overdraft_limit = -500;

		void deposit(int amount){
			balance += amount;
			cout << "[deposit] "<< amount << ", balance is now " << balance << endl;
		};

		void withdraw(int amount) {
			if( balance - amount < overdraft_limit) return;
			balance += amount;
			cout << "[withdraw] "<< amount << ", balance is now " << balance << endl;

		}

	};

	struct Command {


		virtual void call() const =0;
	};

	struct BankAccountCommand  : public Command{

		BankAccount& account;
		int amount;
		enum Action {DEPOSIT, WITHDRAW} action;

		BankAccountCommand(BankAccount& account, Action action, int amount) : account(account), action(action), amount(amount){}

		void call() const override {
			switch(action){
				case DEPOSIT :
					account.deposit(amount);
					break;
				case WITHDRAW :
					account.withdraw(amount);
					break;
			} 
		}
	};

	void main(){
		BankAccount ba;
		BankAccountCommand cmd(ba, BankAccountCommand::DEPOSIT, 1000);
		cmd.call();
	}
};
namespace CommandWithUndo {

	struct BankAccount {
		
		int balance = 0; 
		int overdraft_limit = -500;

		bool deposit(int amount){
			balance += amount;
			cout << "[deposit] "<< amount << ", balance is now " << balance << endl;
			return true;
		}

		bool withdraw(int amount) {
			if( balance - amount < -500 ) return false;
			balance -= amount;
			cout << "[withdraw] "<< amount << ", balance is now " << balance << endl;
			return true;
		}
	};

	struct Command {
		bool succeeded;
		virtual void call() =0;
		virtual void undo() =0;
	};

	struct ReversibleBankAccountCommand  : Command{

		BankAccount& account;
		enum Action{DEPOSIT, WITHDRAW} action;
		int amount;
		bool succeeded = false;

		ReversibleBankAccountCommand(BankAccount& account, Action action, int amount )
			: account(account), action(action), amount(amount){}

		void call()  override{
			switch(action){
				case DEPOSIT :
					succeeded = account.deposit(amount);
					break;
				case WITHDRAW :
					succeeded = account.withdraw(amount);
					break;
			} 			
		}

		void undo()  override {
			switch(action){
				case DEPOSIT :
					if(succeeded)
						account.withdraw(amount);
					break;
				case WITHDRAW :
					if(succeeded) 
						account.deposit(amount);
					break;
			}
			succeeded = false;
		}

	};

	void main(){

		BankAccount ba;
		ReversibleBankAccountCommand cmd(ba, ReversibleBankAccountCommand::DEPOSIT, 500);
		ReversibleBankAccountCommand cmd2(ba, ReversibleBankAccountCommand::WITHDRAW, 500);
		ReversibleBankAccountCommand cmd3(ba, ReversibleBankAccountCommand::WITHDRAW, 2500);

		cmd.call();
		cmd2.call();
		cmd2.undo();
		cmd3.call();
		cmd3.undo();
	}
};
namespace CompositeCommand {

	struct BankAccount {
		int balance = 0; 
		int overdraft_limit = -500;

		bool deposit(int amount){
			balance += amount;
			cout << "[deposit] "<< amount << ", balance is now " << balance << endl;
			return true;
		}

		bool withdraw(int amount) {
			if( balance - amount < -500 ) return false;
			balance -= amount;
			cout << "[withdraw] "<< amount << ", balance is now " << balance << endl;
			return true;
		}
	};

	struct Command {
		bool succeeded;
		virtual void call() = 0;
		virtual void undo() = 0;

	};

	struct BankAccountCommand  : Command{

		BankAccount& account;
		enum Action{DEPOSIT, WITHDRAW} action;
		int amount;
		bool succeeded = false;

		BankAccountCommand(BankAccount& account, Action action, int amount )
			: account(account), action(action), amount(amount){}

		void call()  override{
			switch(action){
				case DEPOSIT :
					succeeded = account.deposit(amount);
					break;
				case WITHDRAW :
					succeeded = account.withdraw(amount);
					break;
			} 			
		}

		void undo()  override {
			switch(action){
				case DEPOSIT :
					if(succeeded)
						account.withdraw(amount);
					break;
				case WITHDRAW :
					if(succeeded) 
						account.deposit(amount);
					break;
			}
			succeeded = false;
		}

	};

	struct CompositeBankAccountCommand : Command, vector<BankAccountCommand>{
		CompositeBankAccountCommand (const initializer_list<value_type>& items )
			: vector<BankAccountCommand>(items){}

		void call() override {
			bool ok = true;
			for(auto& cmd : *this){
				if(ok){
					cmd.call();
					ok = cmd.succeeded;
				}else {
					cmd.succeeded = false;
				}
			}

		}

		void undo() override {
			for(auto it = rbegin(); it != rend(); ++it){
				it->undo();
			}
		}
	};

	void main(){
		BankAccount ba1, ba2;
		CompositeBankAccountCommand cmd {
			BankAccountCommand(ba1, BankAccountCommand::Action::WITHDRAW, 100),
			BankAccountCommand(ba2, BankAccountCommand::Action::DEPOSIT, 500),
			BankAccountCommand(ba2, BankAccountCommand::Action::WITHDRAW, 1000),
			BankAccountCommand(ba1, BankAccountCommand::Action::DEPOSIT, 100)
		};

		cmd.call();
		cmd.undo();
	}
};
namespace CommandQuerySeperation{
	void main(){
	}
};

int main(void){

	cout << "[CommandImplementation]" << endl;
	CommandImplementation::main();
	cout << endl<< "[CommandImplementation2]" << endl;
	CommandImplementation2	::main();
	cout << endl<< "[CommandWithUndo]" << endl;
	CommandWithUndo::main();
	cout << endl<< "[CompositeCommand]" << endl;
	CompositeCommand::main();
	cout << endl<< "[CommandQuerySeperation]" << endl;
	CommandQuerySeperation::main();


	return 0;
}
