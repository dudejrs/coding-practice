#include <iostream>
#include <vector>
#include <string>

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
	void main(){
	}
};
namespace CommandWithUndo {
	void main(){
	}
};
namespace CompositeCommand {
	void main(){
	}
};
namespace CommandQuerySeperation{
	void main(){
	}
};

int main(void){

	CommandImplementation::main();
	CommandImplementation2	::main();
	CommandWithUndo::main();
	CompositeCommand::main();
	CommandQuerySeperation::main();


	return 0;
}
