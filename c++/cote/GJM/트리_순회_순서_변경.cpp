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
	Node* left; 
	Node* right;
	int value;

	Node(Node* parent, int value) : parent(parent), left(nullptr), right(nullptr), value(value){}
	Node(Node* parent, Node* left, Node* right, int value) : parent(parent), left(left), right(right), value(value){}

};



int main(void){

	default_random_engine gen(43);

	for(int it = 0; it < TEST_CASES; it++){

	}

	return 0;
}