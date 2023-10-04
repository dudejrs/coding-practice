#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std; 

namespace ArithmeticExpressionInterpreter{

	struct Token{
		
		enum Type {INTEGER, PLUS, MINUS, LPAREN, RPAREN} type;
		string text;

		explicit Token(Type type, const string& text) : type(type), text(text){}

		friend ostream& operator<< (ostream& os, const Token& other){
			return os << "`" << other.text << "`";
		}

	};

	vector<Token> lex(const string& input){
		vector<Token> ret;

		for(int i =0; i<input.size(); i++){
			switch(input[i]) {
				case '+' :
					ret.push_back(Token(Token::PLUS, "+"));
					break;
				case '-' :
					ret.push_back(Token(Token::MINUS, "-"));
					break;
				case '(' :
					ret.push_back(Token(Token::LPAREN, "("));
					break;
				case ')' :
					ret.push_back(Token(Token::RPAREN, ")"));
					break;
				default :
					ostringstream buffer;
					buffer << input[i];

					for(int j=i+1; j<input.size(); j++){
						if (!isdigit(input[j])) break;
						buffer << input[j];
						i++;
					}
					ret.push_back(Token(Token::INTEGER, buffer.str()));
			}
		}

		return ret;
	}

	struct Element {
		virtual int eval() const = 0;
	};

	struct Integer : Element{
		int value;

		explicit Integer(const int value) : value(value){}

		int eval()const override {
			return value;	
		}
	};

	struct BinaryOperation : Element{
		
		enum Type {ADDITION, SUBTRACTION} type;
		shared_ptr<Element> lhs, rhs;

		int eval()const override {
			if(type == ADDITION)
				return lhs->eval() + rhs->eval();
			return lhs->eval() - rhs->eval();
		}
	};

	struct EmptyElement : Element {
		int eval() const override{
			return 0;
		}
	};

	shared_ptr<Element> parse(const vector<Token>& tokens){
		auto result = make_unique<BinaryOperation>();
		bool have_lhs = false;

		for(int i=0; i<tokens.size(); i++){
			auto token = tokens[i];

			switch(token.type){
				case Token::INTEGER : {
						int value = stoi(token.text);
						auto integer = make_shared<Integer>(value);
						if(!have_lhs){
							result ->lhs= integer;
							have_lhs = true;
						}
						else
							result->rhs = integer;
					}
					break;

				case Token::PLUS : 
					result->type = BinaryOperation::ADDITION;
					break;

				case Token::MINUS :
					result->type = BinaryOperation::SUBTRACTION;
					break;
				case Token::LPAREN :{
					int j = i;
					for(;j<tokens.size();j++)
						if(tokens[j].type == Token::RPAREN) 
							break;
					vector<Token> subexpression(&tokens[i+1], &tokens[j]);
					auto element = parse(subexpression);
					if(!have_lhs){
						result->lhs = element;
						have_lhs = true;
					}else 
						result->rhs = element;
					i = j;
					break;
				}
				case Token::RPAREN :
					break;
			}
		}

		return result;
	}

	void main(void){

		vector<string> inputs = { "(13-4)-(12+1)","12+5", "(12+5)-3"};
		for(auto input : inputs){
			auto tokens = lex(input);
			auto parsed = parse(tokens);
			cout << parsed->eval() << endl;
		}

	}

};

int main(void){

	ArithmeticExpressionInterpreter::main();

	return 0;
}

