#include <regex>
#include <string>
#include <vector>

using namespace std;

regex r1{"[0-9]{1,3}(?:,?[0-9])*"};

bool solution(string amountText) { return regex_search(amountText, r1); }