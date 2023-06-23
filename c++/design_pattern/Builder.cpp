#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <initializer_list>
#include <memory>

using namespace std;


namespace ProblemCase{

	struct HtmlElement{
		string name;
		string text;
		::std::vector<HtmlElement> elements;
		HtmlElement(): name(""),text(""),elements(0){};
		HtmlElement( string& name,  string& text) : name(name), text(text), elements(0) {}

		::std::string str(int indent = 0) const {

			::std::ostringstream oss;

			oss << "<" << name << ">" <<::std::endl;
			for(auto& it : elements){
				oss<<it.str();
			}
			oss << text <<::std::endl;
			oss<< "</" << name << ">" << ::std::endl;

			return oss.str();	
		}
	};
	
	void do_problem_case(){
		using namespace std;
		string words[2]= {"hello", "world"};
		string child_element_name = "li";
		string parent_element_name = "ul";
		string empty = "";

		::ProblemCase::HtmlElement list(parent_element_name,empty);
		for(int i = 0; i < 2; i++){
			string w = words[i];
			list.elements.emplace_back(HtmlElement(child_element_name, w));
		}
		std::cout << list.str() << endl;
	}

}

namespace SimpleBuilderCase{
	typedef ::ProblemCase::HtmlElement HtmlElement;

	struct HtmlBuilder {
		HtmlElement root;
		HtmlBuilder(string root_name){root.name = root_name;}

		void add_children(string child_name, string child_text){
			root.elements.emplace_back(HtmlElement(child_name, child_text));
		}
	};


	void do_simple_budilder_case(){
		using namespace std;
		string root_name = "ul";
		string child_name = "li";
		string words[2] = {"Hello", "World!"};
		HtmlBuilder htmlbuilder(root_name);
		for(auto &it : words){
			htmlbuilder.add_children(child_name,it);
		}
		cout << "== simple builder=="<<endl;
		cout << htmlbuilder.root.str();

	}
};


namespace FluentInterfaceBuilderCase{
	typedef::ProblemCase::HtmlElement HtmlElement;

	struct HtmlBuilder {
		HtmlElement root;
		HtmlBuilder(string root_name){root.name = root_name;}

		HtmlBuilder& add_children(string child_name, string child_text){
			root.elements.emplace_back(HtmlElement(child_name, child_text));
			return *this;
		}
	};
	struct HtmlBuilder2 {
		HtmlElement root;
		HtmlBuilder2(string root_name){root.name = root_name;}

		HtmlBuilder2* add_children(string child_name, string child_text){
			root.elements.emplace_back(HtmlElement(child_name, child_text));
			return this;
		}
	};


	void do_fluent_interface_budilder_case(){
		using namespace std;
		string root_name = "ul";
		string child_name = "li";
		string words[2] = {"Hello", "World!"};
		HtmlBuilder htmlbuilder(root_name);
		// HtmlBuilder2* htmlbuilder = new HtmlBuilder2(root_name);

		htmlbuilder.add_children(child_name, words[0]).add_children(child_name,words[1]);
		// htmlbuilder2->add_children(child_name, words[0])->add_children(child_name,words[1]);
		
		cout << "== fluent interface builder=="<<endl;
		cout << htmlbuilder.root.str();

	}

};

/*사용자에게 빌더 클래스를 사용해야한단는 것을 알리는 방법*/
namespace HowToNotifyUsersToUseBuilderClass{

	typedef ::ProblemCase::HtmlElement HtmlElement;
	// typedef ::FluentInterfaceBuilderCase::HtmlBuilder HtmlBuilder;

	struct HtmlBuilder : ::FluentInterfaceBuilderCase::HtmlElement{

		HtmlElement root;
		HtmlBuilder(string root_name){root.name = root_name;}

		/* 3. 빌더가 아닌 원래 클래스를 생성할 수 있도록 하기 */
		HtmlBuilder& add_children(string child_name, string child_text){
			root.elements.emplace_back(HtmlElement(child_name, child_text));
			return *this;
		}
		operator HtmlElement() const {return root;}
	};

	struct EnhancedHtmlElement : HtmlElement{
		string name;
		string text;
		/* 1. 팩터리 메서드르를 두어 빌더를 생성할 수 있도록 하기 */
		static unique_ptr<HtmlBuilder> build(const string& root_name){
			return make_unique<HtmlBuilder>(root_name);
		}

		/* 2. 모든 생성자를 숨기기 */
		protected : 
			EnhancedHtmlElement() {}
			EnhancedHtmlElement(const string& name, const string& text) : name(name), text(text) {};
	};

	void how_to_notify_uses_to_use_builder_class(){
		using namespace std;
		string root_name = "ul";
		string child_name = "li";
		string words[2] = {"Hello", "World!"};
		auto htmlbuilder = EnhancedHtmlElement::build(root_name);
		HtmlElement e = htmlbuilder->add_children(child_name,words[0]).add_children(child_name,words[1]);
		cout << "== how_to_notify_uses_to_use_builder_class =="<<endl;
		// cout << htmlbuilder->root.str();
		cout << e.str() << endl;

	}
}



namespace groovy_style{
	struct Tag {
		std::string name;
		std::string text;
		std::vector<Tag> children;
		std::vector<std::pair<std::string,std::string>> attributes;

		friend std::ostream& operator<<(std::ostream& os, const Tag& tag){
			
			if(!tag.attributes.empty()){
				os << "<" << tag.name<< " ";
				for (auto& it : tag.attributes){
					os << it.first <<"="<<it.second <<"";
				}
				os << ">" << std::endl;

			}else{
				os << "<" << tag.name <<">" << std::endl;
			}
			os << tag.text << std::endl;
			for(auto& it : tag.children){
				 os << it;
			}
			os << "</" << tag.name << ">" << std::endl;
			return os;
		};


		protected : 
			Tag(const std::string& name, const std::string& text):name(name), text(text){};
			Tag(const std::string& name, const std::vector<Tag>& child) : name(name), children(child){};

	};

	struct P : Tag {
		std::string this_name = "p";
		explicit P(const std::string& text) : Tag("p",text){}
		P(std::initializer_list<Tag> children) : Tag("p",children){}
	};


	struct IMG : Tag{
		explicit IMG(const std::string& url) : Tag("img",""){
			attributes.emplace_back(make_pair("src",url));
		};
	};


	void do_groovy_style(){
		cout << "== groovy_style =="<<std::endl;

		std::cout << 
		P{
			IMG{"http://url"}
		} << std::endl;
	}
}


namespace compositeBuilderCase{
	class PersonBuilder;
	class PersonAddressBuilder;
	class PersonJobBuilder;
	class Person{

		std::string street_address, post_code,city;
		std:: string company_name, position;
		int annual_income = 0;

		Person(){}

		public : 
			static PersonBuilder create();

			Person(Person&& other) 
				: street_address(other.street_address),
				post_code(other.post_code),
				city(other.city),
				company_name(other.company_name),
				position(other.position),
				annual_income(other.annual_income){};

		friend class PersonBuilder;
		friend class PersonAddressBuilder;
		friend class PersonJobBuilder;
	};

	class PersonBuilderBase{
		protected:
			Person& person;
			explicit PersonBuilderBase(Person& person) : person(person){}
		public : 
			operator Person() const{
				return std::move(person);
			}
			PersonAddressBuilder lives() const;
			PersonJobBuilder works() const;
	};
	class PersonAddressBuilder : public PersonBuilderBase{
		typedef PersonAddressBuilder Self;

		public :
			explicit PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

			Self& at(std::string street_address){
				person.street_address = street_address;
				return *this;
			}
			Self& with_postcode(std::string post_code){
				person.post_code = post_code;
				return *this;
			}
			Self& in(std::string city){
				person.city = city;
				return *this;
			}
	};
	class PersonJobBuilder : public PersonBuilderBase{
		typedef PersonJobBuilder Self;

		public : 
			explicit PersonJobBuilder(Person& person) : PersonBuilderBase(person){}

			Self& at(std::string company_name){
				person.company_name = company_name;
				return *this;
			};
			Self& as_a(std::string position){
				person.position = position;
				return *this;
			};
			Self& earning(int annual_income){
				person.annual_income = annual_income;
				return *this;
			};
	};
	class PersonBuilder : public PersonBuilderBase{
			Person p;
		public :
			PersonBuilder() : PersonBuilderBase(p){}

	};


	PersonBuilder Person::create(){
		return PersonBuilder();
	}

	PersonAddressBuilder PersonBuilderBase::lives() const {
		return PersonAddressBuilder(person);
	};

	PersonJobBuilder PersonBuilderBase::works() const{
		return PersonJobBuilder(person);
	}



	void do_composite_builder_case(){
		cout << "== composite_builder_case =="<<std::endl;

		Person p = Person::create()
			.lives().at("123 London Road")
				.with_postcode("SW1 1GB")
				.in("London")
			.works().at("PragmaSoft")
				.as_a("Consultant")
				.earning(10e6);
	}


};



int main(void){

	::ProblemCase::do_problem_case();
	::SimpleBuilderCase::do_simple_budilder_case();
	::FluentInterfaceBuilderCase::do_fluent_interface_budilder_case();
	::groovy_style::do_groovy_style();
	::compositeBuilderCase::do_composite_builder_case();

	return 0;
}