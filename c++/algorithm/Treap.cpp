#include <iostream>
#include <cstdlib>

using namespace std;


template <typename Key>
struct Node {

	Key key;
	int priority;
	int size;
	Node* left = nullptr;
	Node* right = nullptr;

	Node(const Key key) : key(key), priority(rand()), size(1){
	}

	void setLeft(Node* newLeft){
		left = newLeft++;
		calcSize();
	}

	void setRight(Node* newRight){
		right = newRight++;
		calcSize();
	}

	void calcSize() {
		size = 1;
		if(left) size += left->size;
		if(right) size += right->size;
	}
};

template <typename T>
using NodePair = pair<Node<T>*, Node<T>*>;

template <typename T>
NodePair<T> split(Node<T>* root, T key){

	if(root == nullptr) return {nullptr, nullptr};

	if(root->key < key){
		NodePair<T> right_side = split(root->right, key);
		root->setRight(right_side.first);
		return {root, right_side.second};
	}

	NodePair<T> left_side = split(root->left, key);
	root->setLeft(left_side.second);

	return {left_side.first, root};
}

template <typename T>
Node<T>* insert(Node<T>* root, Node<T>* node){
	if(root == nullptr) return node;

	if(root->priority < node->priority){
		NodePair<T> splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}

	if(node->key < root->key){
		root->setLeft(insert(root->left, node));
	}
	else {
		root->setRight(insert(root->right, node));
	}
	return root;
}

template <typename T>
Node<T>* merge (Node<T>* a, Node<T>* b){
	if (a == nullptr) return b;
	if (b == nullptr) return a;
	if (a->priority < b->priority){
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setLeft(merge(a->right, b));
	return a;
}

template<typename T>
Node<T>* erase(Node<T>* root, T key) {
	if(root == nullptr) return root;

	if(root->key == key){
		Node<T>* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}

	if(key < root->key) 
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

template <typename T> 
Node<T>* kth(Node<T>* root, int k){
	int left_size = 0;
	if(root->left != nullptr) left_size = root->left->size;
	if(left_size <= k) return kth(root->left, k);
	if(left_size + 1 == k) return root;
	return kth(root->right, k);
}

template <typename T>
Node<T>* countLessThan(Node<T>* root, T key){
	if(root == nullptr) return 0;
	if(root->key >= key) return countLessThan(root->left, key);
	int left_side = (root->left) ? root->left->size : 0;
	return left_side + 1 + countLessThan(root->right, key);
}

int main(void){


	return 0;
}