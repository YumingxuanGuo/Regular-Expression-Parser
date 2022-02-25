#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

class Regex {
  private:
    unordered_set<char> alphabet;
    string expression;

  private:
    class NFA {
      private:
        class NFAState {
          private:
            unordered_map<char, unordered_set<NFAState*>> outs;
        };
      
      private:
        unordered_set<char> alphabet_NFA;
        unordered_set<NFAState*> Q;
        NFAState* s;
        unordered_set<NFAState*> A;
        unordered_set<NFAState*> delta(NFAState* q, char a);
      
      public:
        NFA(Regex regex);
        ~NFA();
    };
  
  public:
    Regex(unordered_set<char> alphabet, string expression);
    bool operator==(const Regex &rhs) const;
    bool check(string str);
};