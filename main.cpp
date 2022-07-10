#include "src/Regex.h"
#include <iostream>

using namespace std;

int main() {
  string regex;
  cout << "Please type in the regular expression:" << endl;
  cin >> regex;
  unordered_set<char> alphabet;
  Regex reg(regex);
  // cout << reg.completedExpression << endl << reg.reversePolishNotation << endl;
  string str = "";
  while (true) {
    cout << "Please type in the string (type in 'q' to quit):" << endl;
    cin >> str;
    if (str == "q") break;
    if (reg.check(str)) cout << "Accepted." << endl << endl;
    else cout << "Refused." << endl << endl;
  }
  return 0;
}