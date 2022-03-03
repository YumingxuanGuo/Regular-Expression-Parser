#include "src/Regex.h"
#include <iostream>

using namespace std;

int main() {
  string regex;
  cout << "Please type in the regular expression:" << endl;
  cin >> regex;
  unordered_set<char> alphabet;
  Regex reg(alphabet, regex);
  cout << reg.reversePolishNotation << endl;
  string str;
  cout << "Please type in the string:" << endl;
  cin >> str;
  if (reg.check(str)) cout << "Accepted." << endl;
  else cout << "Refused." << endl;
  return 0;
}