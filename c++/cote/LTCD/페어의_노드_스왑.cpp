#include <iostream>
#include <random>

#define TEST_CASE 10
#define N 1000

using namespace std;


template <typename T>
struct Node {

	T value;
	Node<T>* next;


	Node(T value, Node<T>* next) : value(value), next(next) {}
	Node(T value) : Node(value, nullptr) {}
	Node() : Node(T(),nullptr){}

};


template <typename T>
Node<T>* generate(default_random_engine& gen){

	normal_distribution<float> dis(N/2, N/4);

	int n = floor(dis(gen));
	int cur = n; 

	Node<T>* prev = new Node<T>(cur--);

	while (cur > 0){
		prev = new Node<T>(cur--, prev);
	}


	return prev;
}

template <typename T>
void printNode(Node<T>* node){
	while (node){
			cout << node->value<< " ";
			node = node->next;
		}
		cout << endl;
}

template <typename T>
void deleteNode(Node<T>* node){
	while (node){
			Node<int>* cur = node;
			node = node->next;
			delete cur;
		}
}


template <typename T>
Node<T>* solve(Node<T>* node){
	Node<T>* root = new Node<T>();
	Node<T>* left = root;
	left->next = node;

	while(node && node->next){
		Node<T>* right = node->next;

		node->next = right->next;
		right->next = node;
		left->next = right;

		node = node->next;
		left = left->next->next;
	}

	Node<T>* ret = root->next;
	delete root;
	return ret;
}

int main(void){

	default_random_engine gen(43);

	for (int it = 0; it < TEST_CASE; it++){
		Node<int>* node = generate<int>(gen);

		node = solve(node);
		printNode(node);
		deleteNode(node);
	}

	return 0;
}