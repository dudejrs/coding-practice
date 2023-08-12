#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <random>

#define TEST_CASES 10
#define MIN_LENGTH 5
#define MAX_LENGTH 15
#define MAX_VALUE 100

using namespace std;

struct Node {
	Node* parent;
	Node* left; 
	Node* right;
	int value;

	Node(Node* parent, int value) : parent(parent), left(nullptr), right(nullptr), value(value){}
	Node(Node* parent, Node* left, Node* right, int value) : parent(parent), left(left), right(right), value(value){}
	~Node(){ 
		if(left) delete left;
		if(right) delete right;
	}
};


struct BinaryTree {
	Node* root;

	BinaryTree(Node* root) : root(root){}
	~BinaryTree(){delete root;}

	void set_left_child(Node* parent, Node* left ){
		parent->left = left;
		left->parent = parent;
		return;
	}
	void set_right_child(Node* parent, Node* right ){
		parent->right = right;
		right->parent = parent;
		return;
	}


	Node* _search(Node* cur, int value){
		if(value < cur->value )
			return _search(cur->left, value);
		if(value > cur->value) return cur;
			return _search(cur->right, value);
		return cur;
	}

	Node* search(int value){
		return _search(root, value);
	}

	void _insert(Node* cur, Node* newer){

		if(newer->value < cur->value){
			if(!cur->left) return set_left_child(cur, newer);
			return _insert(cur->left, newer);
		}

		if(!cur->right) return set_right_child(cur, newer);

		return _insert(cur->right, newer);
	}

	void insert(Node* newer){
		return _insert(root, newer);	
	}

};


struct BinaryTreeBuilder {

	BinaryTree* tree; 

	BinaryTreeBuilder() : tree(new BinaryTree(new Node(nullptr, 0))) {}
	BinaryTreeBuilder(Node* root) : tree(new BinaryTree(root)){}
	~BinaryTreeBuilder(){ delete tree;}

	BinaryTreeBuilder& set_root(int value){
		tree->root->value = value;
		return *this;
	}

	BinaryTreeBuilder& insert(int value){
		tree->insert(new Node( nullptr, value));
		return *this;
	};

	BinaryTree& build(){

		BinaryTree* ret = tree;
		tree = new BinaryTree(nullptr);

		return *ret;
	}
};

void preorder(Node* cur ,vector<int>& a){
	if(!cur) return;
	a.push_back(cur->value);
	preorder(cur->left, a);
	preorder(cur->right, a);
}

void inorder(Node* cur ,vector<int>& a){
	if(!cur) return;
	inorder(cur->left, a);
	a.push_back(cur->value);
	inorder(cur->right, a);
}



BinaryTree& initialize(default_random_engine& gen){

	uniform_int_distribution<int> dis(0, MAX_VALUE);
	int n = gen() % (MAX_LENGTH- MIN_LENGTH + 1) + MIN_LENGTH;

	BinaryTreeBuilder builder;

	builder.set_root(dis(gen));
	for(int i=0; i<n-1; i++) builder.insert(dis(gen));

	BinaryTree* tree = &builder.build();

	return *tree;
}

string solve(vector<int>& pre, vector<int>& in){
	
	
	return "";
}

int main(void){

	default_random_engine gen(43);

	for(int it = 0; it < TEST_CASES; it++){

		BinaryTree tree = initialize(gen);
		vector<int> p1, p2;
		preorder(tree.root, p1);
		inorder(tree.root, p2);
		cout << solve(p1,p2) << endl;
	}

	return 0;
}