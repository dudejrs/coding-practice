#include <iostream>
#include <sstream>
#include <string>
#include <initializer_list>

using namespace std;

namespace InvasionVistiorCase {

	struct Expression {
		virtual void print(ostringstream& oss) = 0;
		virtual ~Expression() = default;
	};

	struct AdditionExpression : Expression {
		Expression *left, *right;

		AdditionExpression(Expression* const left, Expression* right) 
			: left(left), right(right) {}

		~AdditionExpression() {
			delete left; delete right;
		}

		void print(ostringstream& oss) override{
			oss << "(";
			left->print(oss);
			oss << "+";
			right->print(oss);
			oss << ")";
		}
	};

	struct DoubleExpression : Expression {
		double value;
		explicit DoubleExpression(const double value) : value(value){}

		void print(ostringstream& oss) override {
			oss << value;
		}
	};

	void main(void){
		cout << "[InvasionVistiorCase]" << endl;


		auto e = new AdditionExpression {
			new DoubleExpression{1},
			new AdditionExpression {
				new DoubleExpression{2},
				new DoubleExpression{3}
				}
		};

		ostringstream oss;
		e->print(oss);
		cout << oss.str() << endl;

		cout << endl;
	}
	
}

namespace ReflectiveVistiorCase {

	struct Expression {
		virtual ~Expression() = default;
	};

	struct AdditionExpression : Expression {
		Expression *left, *right;

		AdditionExpression(Expression* const left, Expression* right) 
			: left(left), right(right) {}

		~AdditionExpression() {
			delete left; delete right;
		}

	};

	struct DoubleExpression : Expression {
		double value;
		explicit DoubleExpression(const double value) : value(value){}

	};

	struct ExpressionPrinter {
		void print(Expression * e){

			if(auto de = dynamic_cast<DoubleExpression*>(e)){
				oss << de->value;
			}else if(auto ae = dynamic_cast<AdditionExpression*>(e)){
				oss << "(";
				print(ae->left);
				oss << "+";
				print(ae->right);
				oss << ")";
			}
		}

		string str() const {return oss.str() ;}

		private :
			ostringstream oss;
	};

	void main(void){
		cout << "[ReflectiveVistiorCase]" << endl;

		auto e = new AdditionExpression {
			new DoubleExpression{1},
			new AdditionExpression{
				new DoubleExpression{2},
				new DoubleExpression{3}
			}
		};

		ExpressionPrinter ep;
		ep.print(e);
		cout << ep.str() << endl;

		cout << endl;
	}
}


namespace ConventionalVisitorCase {

	struct ExpressionVisitor;
	struct AdditionExpression;
	struct DoubleExpression;

	struct Expression {
		virtual ~Expression() = default;
		virtual void accept(ExpressionVisitor* visitor) = 0;

	};

	struct ExpressionVisitor {
		virtual void visit(AdditionExpression* ae) = 0;
		virtual void visit(DoubleExpression* de) = 0;
	};



	struct AdditionExpression : Expression {
		Expression *left, *right;

		AdditionExpression(Expression* const left, Expression* right) 
			: left(left), right(right) {}

		~AdditionExpression() {
			delete left; delete right;
		}

		void accept(ExpressionVisitor* visitor) override {
			visitor->visit(this);
		}

	};


	struct DoubleExpression : Expression {
		double value;
		explicit DoubleExpression(const double value) : value(value){}

		void accept(ExpressionVisitor* visitor) override {
			visitor->visit(this);
		}

	};

	struct ExpressionPrinter : ExpressionVisitor{
		ostringstream oss;
		string str() const {return oss.str();}

		void visit(AdditionExpression* ae){
			cout << "(";
			ae->left->accept(this);
			cout << "+";
			ae->right->accept(this);
			cout << ")";
		}

		void visit(DoubleExpression* de){
			cout << de->value;
		}

	};

	struct ExpressionEvaluator : ExpressionVisitor{
		double result = 0;
		double evaluate(Expression* expression){
			return result;
		}

		void visit(AdditionExpression* ae){
			ae->left->accept(this); 
			auto tmp = result;
			ae->right->accept(this);
			result += tmp;
		}

		void visit(DoubleExpression* de){
			result = de->value;
		}
	};

	void main(void){
		cout << "[ConventionalVistiorCase]" << endl;

		auto e = new AdditionExpression {
			new DoubleExpression{1},
			new AdditionExpression{
				new DoubleExpression{2},
				new DoubleExpression{3}
			}
		};

		ExpressionPrinter ep;
		ep.visit(e);
		cout << ep.str() << "=" ;

		ExpressionEvaluator ev;
		ev.visit(e);
		cout << ev.evaluate(e) << endl;

		cout << endl;
	}
}

int main(void){

	InvasionVistiorCase::main();
	ReflectiveVistiorCase::main();
	ConventionalVisitorCase::main();
	
	return 0;
}