#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

#define M_ 500
#define Q_ 100 

using namespace std;

int n=0, m=0, q=0;
double** T;
double** M;

int choice [Q_+2][M_+2];
double cache [Q_+2][M_+2];

map<string,int> dict;
vector<string> tokens;

vector<string>& split(const string& s){
	vector<string>* ret = new vector<string> ();
	stringstream ss(s);
	string buf;

	while(getline(ss,buf,' ')){
		ret->push_back(buf);
	}

	return *ret;
}

void initialize(fstream& fd){
	string buf; 

	
	getline(fd,buf);
	vector<string> mAndQ = split(buf);
	
	m = stoi(mAndQ[0]);
	q = stoi(mAndQ[1]);
	
	T = new double* [m+1];
	for(int i=0; i<m+1; i++) T[i] = new double[m+1];

	M = new double* [m+1];
	for(int i=0; i<m+1; i++) M[i] = new double[m+1];

	getline(fd,buf);
	vector<string> terms = split(buf);
	int i=0;

	tokens.push_back("");
	for(auto term : terms) {
		dict.insert(make_pair(term,i+1));
		tokens.push_back(term);
		i++;
	}
	
	for(int i=0; i<m+1; i++){
		getline(fd,buf);
		vector<string>& tmp = split(buf);
		for(int j=0; j<m; j++){
			T[i][j+1] = stod(tmp[j]);
		}
	}

	for(int i=1; i<m+1; i++){
		getline(fd,buf);
		vector<string>& tmp = split(buf);
		for(int j=0; j<m; j++){
			M[i][j+1] = stod(tmp[j]);
		}
	}
}

vector<string>& get_words(const string& s){
	vector<string>& v = split(s);

	n = stoi(v[0]);
	v.erase(begin(v));
	
	return v;	
}


double recognize(int count, int previous_word, vector<string>& v){
	
	if(count == n) return 0;
	double& ret = cache[count][previous_word];
	// if(ret != 1.0) return ret;

	int mismatched = dict[v[count]];

 	ret = -1e200;
	int& best = choice[count][previous_word];

	for(int i=0; i<m+1; i++){
		double tmp = recognize(count+1,i,v) + T[previous_word][i] + M[i][mismatched];
		if(ret < tmp){
			ret = tmp;
			best = i;
		}
	}

	return ret;
}

void reconstruct(int count, int previous_word, vector<string>& v){
	int next = choice[count][previous_word];
	v.push_back(tokens[next]);
	if(count < n-1)
		reconstruct(count+1, next, v);
	return ;
}


vector<string>& solve(vector<string>& v){
	vector<string>* ret = new vector<string>();

	recognize(0,0,v);
	reconstruct(0,0,*ret);

	return *ret;
}

int main(void){

	fstream fd("data/광학문자인식.txt");
	string buf;
	initialize(fd);
	


	while(q > 0 ){
		memset(cache, 1.0, sizeof(cache));
		memset(choice, -1, sizeof(choice));

		getline(fd,buf);	
		vector<string> v = get_words(buf);

		vector<string> answer = solve(v);
		for(auto& word: answer) {
			cout << word << " ";
		}
		cout << endl;

		q--;
	}


	return 0;
}
 
