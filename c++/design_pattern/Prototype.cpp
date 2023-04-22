#include <iostream>
#include <sstream>
#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/access.hpp>

using namespace std;


//  0. 문제의 경우
namespace ProblemCase{

	struct Address{
		string street, city;
		int suite;

		Address(const string& street, const string& city, int suite ) : street(street), city(city), suite(suite){}
		Address(const Address& other) : street(other.street), city(other.city), suite(other.suite){} 
		Address(Address&& other)	 : street(other.street), city(other.city), suite(other.suite){}
		
		Address& operator= (Address&& other){
			this->street = other.street;
			this->city = other.city;
			this->suite = other.suite;
			return *this;
		}

	};

	struct Contact{
		string name;
		Address address;

		Contact(const string& name, const Address& address) : name(name), address(std::move(address)) {}
		Contact(Contact& prototype): name(prototype.name), address(prototype.address){}
		Contact(Contact&& other) : name(other.name), address(other.address){}

		Contact& operator= (Contact && other){
			this->name = other.name;
			this->address = std::move(other.address);
			return *this;
		}
	};

	struct Contact2{
		string name;
		Address* address;
	};



	void do_problem_case(){
		
		// 일반적인 경우는 문제가 없음
		Contact worker{"", Address("123 East Dr ", "London ", 0)};
		Contact jane = worker;
		jane.name = "Jane Doe";
		jane.address.suite = 11;

		std::cout << "John's address : " <<  worker.address.street <<  worker.address.city<<  worker.address.suite << std::endl;
		std::cout << "Jane's address : " <<  jane.address.street <<  jane.address.city<<  jane.address.suite << std::endl;
		std::cout << std::endl;

		// 포인터를 사용한 경우 문제가 발생
		Address worker_address("123 East Dr ", "London ", 0);
		Contact2 worker_entry{"", &worker_address};
		Contact2 john_entry = worker_entry;
		john_entry.name = "John Doe";
		john_entry.address->suite = 10;
		Contact2 jane_entry = worker_entry;
		jane_entry.name = "Jane Doe";
		jane_entry.address->suite = 11;

		std::cout << "John's address : " <<  worker_entry.address->street <<  worker_entry.address->city<<  worker_entry.address->suite << std::endl;
		std::cout << "John's address : " <<  john_entry.address->street <<  john_entry.address->city<<  john_entry.address->suite << std::endl;
		std::cout << "Jane's address : " <<  jane_entry.address->street <<  jane_entry.address->city<<  jane_entry.address->suite << std::endl;
		std::cout << std::endl;
	}

}

// 1. 프로토타입
namespace ProtoType{
	
	template <typename T>
	struct Colneable {
		virtual T clone() const =0;
	};

	struct Address {
		string street, city;
		int suite;

		Address(string street, string city, int suite) : street(street),city(city),suite(suite){} 
		Address(Address& other) : Address(other.street, other.city, other.suite){}
		Address(Address&& other) : Address(other.street, other.city, other.suite){}


		Address& operator= (Address&& other){
			this->street = other.street;
			this->city = other.city;
			this->suite = other.suite;

			return *this;
		}

	};

	struct Contact : Colneable<Contact> {
		string name;
		Address* address;

		Contact(const string& name, Address* address) : name(name), address(address){}
		Contact (const Contact& other) : Contact(other.name, new Address(*other.address)){}
		Contact(Contact&& other) : Contact(other.name, other.address){}

		Contact clone() const override{
			return {name, new Address(*address)};
		}
	};

	void do_problem_case(){
		Address worker_address("123 East Dr", "London", 0);
		Contact worker_entry{"worker", &worker_address};

		Contact john_entry = worker_entry;
		john_entry.name = "John Doe";
		john_entry.address->suite = 10;

		Contact jane_entry = worker_entry.clone();
		jane_entry.name = "Jane Doe";
		jane_entry.address->suite = 11;

		std::cout << "John's address : " <<  worker_entry.address->street <<  worker_entry.address->city<<  worker_entry.address->suite << std::endl;
		std::cout << "John's address : " <<  john_entry.address->street <<  john_entry.address->city<<  john_entry.address->suite << std::endl;
		std::cout << "Jane's address : " <<  jane_entry.address->street <<  jane_entry.address->city<<  jane_entry.address->suite << std::endl;
		std::cout << std::endl;
	}
}

// 2. 직렬화 프로토타입
namespace SerializibleProtoType{
	void do_problem_case(){
		
	}
}

// 3. 프로토타입 팩터리 메서드
namespace ProtoTypeFactory{
	void do_problem_case(){
		
	}
}

// 4. 프로토타입 레지스터리
namespace ProtoTypeRegistery{
	void do_problem_case(){
		
	}
}

int main(){
	ProblemCase::do_problem_case();
	ProtoType::do_problem_case();

	return 0;
}

