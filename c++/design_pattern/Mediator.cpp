#include <iostream>
#include <string>
#include <vector>

using namespace std;


namespace BasicMediator {
	
	struct Mediator;

	struct ComponentA{

		ComponentA() : mediator(nullptr){}

		void opeationA();
		void set_mediator(Mediator* mediator){
			this->mediator = mediator;
		}
		
		private : 
			Mediator* mediator;
	};

	struct ComponentB{

		ComponentB() : mediator(nullptr){}

		void opeationB();

		void set_mediator(Mediator* mediator){
			this->mediator = mediator;
		}

		private :
			Mediator* mediator;
	};


	struct Mediator{

		ComponentA* a;
		ComponentB* b;

		Mediator(ComponentA* a, ComponentB* b) : a(a), b(b){
			a->set_mediator(this);
			b->set_mediator(this);
		}

		void notify(const string& sender, const string& recevier){
			if(sender == "A")
				cout << "Mediator react to A and  Send Message to " << recevier << endl;

			else if(sender == "B")
				cout << "Mediator react to B and  Send Message to " << recevier << endl;

			
		}
	};

	void ComponentA::opeationA(){
		cout << "A does operation" << endl;
		mediator->notify("A", "B");
	};
	void ComponentB::opeationB(){
		cout << "B does operation" << endl;
		mediator->notify("B", "A");
	};

	void main(void){
		cout <<"[BasicMediator]" << endl;

		ComponentA a;
		ComponentB b;
		Mediator m(&a, &b);

		a.opeationA();
		cout << endl;
		b.opeationB();
		cout << endl;

	}
}

namespace CollectionMediator {


	struct ChatRoom;

	struct Person{
		string name;
		ChatRoom* room = nullptr;
		vector<string> chat_log;

		Person(const string& name) : name(name){}

		void say(const string& message)const;
		void pm(const string& who, const string& message) const;
		void recieve(const string& origin, const string& message) {
			string s{origin+" : "+message+"\t"};
			cout << "[" << name<<"'s session]  " << s << endl;
			chat_log.emplace_back(s);
		}
	};

	struct ChatRoom{
		vector<Person*> people;

		void join(Person* p){
			string join_msg = p->name + " joins the chat";
			p->room = this;
			broadcast("rooms", join_msg);
			people.push_back(p);
		}

		void broadcast(const string& origin, const string& message){
			for(auto p : people)
				if(p->name != origin)
					p->recieve(origin, message);
			
		}

		void message(const string& origin, const string& who, const string& message){
			auto target = find_if(begin(people), end(people),[&](const Person* p){
				return p->name == who;
			});

			if(target != end(people))
				(*target)->recieve(origin, message);
		}
	};

	void Person::say(const string& message)const {
		room->broadcast(name, message);
	}
	void Person::pm(const string& who, const string& message) const {
		room->message(name,who,message);
	}



	void main(void){

		cout <<"[CollectionMediator]" << endl;

		ChatRoom room;

		Person john{"john"};
		Person jane{"jane"};
		Person simon{"simon"};

		room.join(&john);
		room.join(&jane);
		john.say("hi jane");
		room.join(&simon);
		john.say("hi simon");
		john.pm("simon", "glad  you could join us, simon!");



		cout << endl;
	}
}


namespace MediatorWithHierahicalComponent {

	class BaseComponent;
	class Mediator{
		public :
			virtual void notify(BaseComponent* sender, const string& event) const = 0;
	};

	class BaseComponent {
		protected : 
			Mediator* mediator;

		public :
			string name;
			BaseComponent() : mediator(nullptr){}
			BaseComponent(const string& name) : mediator(nullptr), name(name){}
			BaseComponent(const string& name, Mediator* mediator) :name(name), mediator(mediator){}
			
			virtual void set_mediator(Mediator* mediator){
				this->mediator = mediator;
			}
	};

	struct ComponentA : public BaseComponent{

		explicit ComponentA(const string& name) : BaseComponent(name){}

		void doA(){
			cout << "Component " <<  name << " does A" << endl;
			mediator->notify(this, "A");
		}

		void doB(){
			cout << "Component " <<  name << " does B" << endl;
			mediator->notify(this, "B");
		}

	};

	struct ComponentB : public BaseComponent{


		explicit ComponentB(const string& name) : BaseComponent(name){}

		void doC(){
			cout << "Component " <<  name << " does C" << endl;
			mediator->notify(this, "C");
		}

		void doD(){
			cout << "Component " <<  name << " does D" << endl;
			mediator->notify(this, "D");
		}

	};

	class ConcreteMediator : public Mediator {
		ComponentA* a;
		ComponentB* b;

		public :

			explicit ConcreteMediator(ComponentA* a, ComponentB* b) : a(a), b(b){
				this->a->set_mediator(this);
				this->b->set_mediator(this);
			}


			void notify(BaseComponent* sender, const string& event)const override{

				if(auto child = dynamic_cast<ComponentA*>(sender))
					if(event == "A"){
						cout << "Mediator reacts "<<child->name <<" on A and trigger following operations:" << endl;
						this->b->doC();
					}
				if(auto child =dynamic_cast<ComponentB*>(sender))
					if( event == "D"){
						cout << "Mediator reacts "<<child->name << " on B and trigger following operations:" << endl;
						this->a->doB();
					}
			}
	};


	void main(void){
		cout <<"[MediatorWithHierahicalComponent]" << endl;
		ComponentA* a = new ComponentA("<a1>");
		ComponentB* b = new ComponentB("<b1>");

		ConcreteMediator* mediator = new ConcreteMediator(a,b);

		a->doA();
		cout << endl;
		b->doD();

		delete a;
		delete b;
		delete mediator;

	}
}



namespace MediatorWithBoostSignal {
	void main(void){
		cout <<"[MediatorWithBoostSignal]" << endl;
		cout << endl;

	}
};


int main(void){
	BasicMediator::main();
	cout << endl;
	CollectionMediator::main();
	cout << endl;
	MediatorWithHierahicalComponent::main();
	cout << endl;
	MediatorWithBoostSignal::main();
	cout << endl;

	return 0;
}