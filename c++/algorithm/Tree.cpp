#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <random>

#define TEST_CASES 10
#define MIN_LENGTH 5
#define MAX_LENGTH 15

using namespace std;

struct Node {
	Node* parent;
	vector<Node*> children;
	int value;

	Node(Node* parent, int value) : parent(parent), value(value){}
	~Node(){
		for(int i =0; i< children.size(); i++)
			delete children[i];
	}

	void add_children(Node* n){
		children.push_back(n);
	}
};

struct Tree {
	Node* root;

	Tree(Node* root) : root(root){}
	~Tree(){
		delete root;
	}

	void insert(Node* parent, Node* cur){
		parent->children.push_back(cur);
	}
	
	int height(){
		return height(root);
	}

	int height(Node* cur){
		int h = 0;
		for(int i=0; i<cur->children.size(); i++)
			h = max(h , 1 + height(cur->children[i]));
		return h;
	}

	vector<int> preorder(){
		stack<Node*> s;
		s.push(root);

		vector<int> ret;

		while(!s.empty()){
			Node* cur =  s.top();
			ret.push_back(cur->value);
			s.pop();

			if(!cur->children.empty()){
				for(auto i= cur->children.rbegin(); i != cur->children.rend(); i++)
					s.push(*i);
			}
		}

		return ret;
	}

};

struct TreeBuilder {
	
	Tree* t;

	TreeBuilder() : t(new Tree(new Node(nullptr, 0))) {}
	~TreeBuilder() {delete t;}

	TreeBuilder& set_root(Node* root){

		delete t->root;
		t->root = root;
		return *this;
	}

	TreeBuilder& set_children(Node* parent, Node* children){
		parent->add_children(children);
		children->parent = parent;
		return *this;
	}

	Tree* build(){
		Tree* ret = t; 
		t = new Tree(new Node(nullptr,0));
		
		return ret;
	}

};


Tree& initialize(default_random_engine& gen){
	vector<Node*> nodes;

	int n = gen() % (MAX_LENGTH - MIN_LENGTH + 1) + MIN_LENGTH;
	for(int i=0; i<n; i++)
		nodes.push_back(new Node(nullptr,i));

	TreeBuilder builder;
	builder.set_root(nodes[0]);
	cout << "["<< n << "]"<< endl;
	
	for(int i=0; i<n/2; i++){
		if(2*i+1< n)
			builder.set_children(nodes[i], nodes[2*i+1]);
		if(2*i+2< n)
			builder.set_children(nodes[i], nodes[2*i+2]);
	}

	Tree* ret = builder.build();

	return *ret;
}



int main(void){

	default_random_engine gen(43);

	for(int it = 0; it < TEST_CASES; it++){
		Tree ret = initialize(gen);

		vector<int> preorder_nodes = ret.preorder();
		for(auto i : preorder_nodes)
			cout << i << " ";
		cout << endl;


	}

	return 0;
}