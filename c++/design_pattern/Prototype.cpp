#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/access.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

//  0. 문제의 경우
namespace ProblemCase {

struct Address {
  string street, city;
  int suite;

  Address(const string& street, const string& city, int suite)
      : street(street), city(city), suite(suite) {}
  Address(const Address& other)
      : street(other.street), city(other.city), suite(other.suite) {}
  Address(Address&& other)
      : street(other.street), city(other.city), suite(other.suite) {}

  Address& operator=(Address&& other) {
    this->street = other.street;
    this->city = other.city;
    this->suite = other.suite;
    return *this;
  }
};

struct Contact {
  string name;
  Address address;

  Contact(const string& name, const Address& address)
      : name(name), address(std::move(address)) {}
  Contact(Contact& prototype)
      : name(prototype.name), address(prototype.address) {}
  Contact(Contact&& other) : name(other.name), address(other.address) {}

  Contact& operator=(Contact&& other) {
    this->name = other.name;
    this->address = std::move(other.address);
    return *this;
  }
};

struct Contact2 {
  string name;
  Address* address;
};

void do_problem_case() {
  // 일반적인 경우는 문제가 없음
  Contact worker{"", Address("123 East Dr ", "London ", 0)};
  Contact jane = worker;
  jane.name = "Jane Doe";
  jane.address.suite = 11;

  std::cout << "John's address : " << worker.address.street
            << worker.address.city << worker.address.suite << std::endl;
  std::cout << "Jane's address : " << jane.address.street << jane.address.city
            << jane.address.suite << std::endl;
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

  std::cout << "John's address : " << worker_entry.address->street
            << worker_entry.address->city << worker_entry.address->suite
            << std::endl;
  std::cout << "John's address : " << john_entry.address->street
            << john_entry.address->city << john_entry.address->suite
            << std::endl;
  std::cout << "Jane's address : " << jane_entry.address->street
            << jane_entry.address->city << jane_entry.address->suite
            << std::endl;
  std::cout << std::endl;
}

}  // namespace ProblemCase

// 1. 프로토타입
namespace ProtoType {

template <typename T>
struct Colneable {
  virtual T clone() const = 0;
};

struct Address {
  string street, city;
  int suite;

  Address(string street, string city, int suite)
      : street(street), city(city), suite(suite) {}
  Address(Address& other) : Address(other.street, other.city, other.suite) {}
  Address(Address&& other) : Address(other.street, other.city, other.suite) {}

  Address& operator=(Address& other) {
    this->street = other.street;
    this->city = other.city;
    this->suite = other.suite;

    return *this;
  }
};

struct Contact : Colneable<Contact> {
  string name;
  Address* address;

  Contact(const string& name, Address* address)
      : name(name), address(address) {}
  Contact(const Contact& other)
      : Contact(other.name, new Address(*other.address)) {}
  Contact(Contact&& other) : Contact(other.name, other.address) {}

  Contact& operator=(const Contact& other) {
    if (this == &other) return *this;
    name = other.name;
    address = new Address(*(other.address));
    return *this;
  }

  Contact clone() const override { return {name, new Address(*address)}; }
};

void do_main() {
  Address worker_address("123 East Dr", "London", 0);
  Contact worker_entry{"worker", &worker_address};

  Contact john_entry = worker_entry;
  john_entry.name = "John Doe";
  john_entry.address->suite = 10;

  Contact jane_entry = worker_entry.clone();
  jane_entry.name = "Jane Doe";
  jane_entry.address->suite = 11;

  std::cout << "John's address : " << worker_entry.address->street
            << worker_entry.address->city << worker_entry.address->suite
            << std::endl;
  std::cout << "John's address : " << john_entry.address->street
            << john_entry.address->city << john_entry.address->suite
            << std::endl;
  std::cout << "Jane's address : " << jane_entry.address->street
            << jane_entry.address->city << jane_entry.address->suite
            << std::endl;
  std::cout << std::endl;
}
}  // namespace ProtoType

// 2. 직렬화 프로토타입
namespace SerializibleProtoType {

struct Address {
  string street, city;
  int suite;

  friend ostream& operator<<(ostream& os, const Address& obj) {
    return os << "street: " << obj.street << " city: " << obj.city
              << " suite: " << obj.suite;
  }

 private:
  friend class boost::serialization::access;

  template <class Ar>
  void serialize(Ar& ar, const unsigned int version) {
    ar & street;
    ar & city;
    ar & suite;
  }
};

struct Contact {
  string name;
  Address* address = nullptr;

  friend ostream& operator<<(ostream& os, const Contact& obj) {
    return os << "name: " << obj.name << " address: " << *obj.address;
  }

 private:
  friend class boost::serialization::access;
  template <class Ar>
  void serialize(Ar& ar, const unsigned int version) {
    ar & name;
    ar & address;
  }
};

void do_main() {
  auto clone = [](const Contact& c) {
    ostringstream oss;
    // boost::archive::text_oarchive oa(oss);
    // oa << c;

    Contact result;
    istringstream iss(oss.str());
    // boost::archive::text_iarchive ia(iss);
    // ia >> result;

    return result;
  };

  Address* worker_address = new Address{"123 East Dr ", "London ", 0};
  Contact worker_entry{"", worker_address};
  Contact jane_entry = clone(worker_entry);
}
}  // namespace SerializibleProtoType

// 3. 프로토타입 팩터리 메서드
namespace ProtoTypeFactory {

struct Address {
  string street, city;
  int suite;

  Address(string street, string city, int suite)
      : street(street), city(city), suite(suite) {}
  Address(Address& other) : Address(other.street, other.city, other.suite) {}
  Address(Address&& other) : Address(other.street, other.city, other.suite) {}

  Address& operator=(Address& other) {
    this->street = other.street;
    this->city = other.city;
    this->suite = other.suite;

    return *this;
  }
};

struct Contact {
  string name;
  Address* address;

  Contact(const string& name, Address* address)
      : name(name), address(address) {}
  Contact(const string& name, const string& street, const string& city,
          int suite)
      : name(name), address(new Address(street, city, suite)) {}
  Contact(const Contact& other)
      : Contact(other.name, new Address(*other.address)) {}
  Contact(Contact&& other) : Contact(other.name, other.address) {}

  Contact& operator=(const Contact& other) {
    if (this == &other) return *this;
    name = other.name;
    address = new Address(*(other.address));
    return *this;
  }
};

struct EmploymentFactory {
  static Contact main;  // 본사
  static Contact aux;   // 지사

  static unique_ptr<Contact> NewMainEmployee(const string& name, int suite) {
    return NewEmployee(name, suite, main);
  }
  static unique_ptr<Contact> NewAuxEmployee(const string& name, int suite) {
    return NewEmployee(name, suite, aux);
  }

 private:
  static unique_ptr<Contact> NewEmployee(string name, int suite,
                                         Contact& proto) {
    auto result = make_unique<Contact>(proto);
    result->name = name;
    result->address->suite = suite;
    return result;
  }
};

Contact EmploymentFactory::main = Contact{"", "123 East Dr ", "London ", 0};
Contact EmploymentFactory::aux = Contact{"", "123B East Dr ", "London ", 0};

void do_main() {
  auto john = EmploymentFactory::NewAuxEmployee("John Doe", 123);
  auto Jane = EmploymentFactory::NewMainEmployee("Jane Doe", 125);
}
}  // namespace ProtoTypeFactory

// 4. 프로토타입 레지스터리
namespace ProtoTypeRegistery {

struct Button {
  int x, y;
  string color;

  Button(int x, int y, string color) : x(x), y(y), color(color) {}

  string getColor() { return color; }

  Button clone() { return {x, y, color}; }
};

struct ButtonRegistery {
  map<string, Button*> items;

  void addItem(const string& name, Button* p) {
    items.insert(make_pair(name, p));
  }

  Button getByColor(const string& color) {
    for (auto item : items) {
      if (item.second->getColor() == color) {
        return item.second->clone();
      }
    }
    return {0, 0, "red"};
  }
};

void do_main() {
  Button btn(10, 40, "red");
  ButtonRegistery regeistry;
  regeistry.addItem("a", &btn);

  Button btn2 = regeistry.getByColor("red");
}
}  // namespace ProtoTypeRegistery

int main() {
  ProblemCase::do_problem_case();
  ProtoType::do_main();
  SerializibleProtoType::do_main();

  return 0;
}
