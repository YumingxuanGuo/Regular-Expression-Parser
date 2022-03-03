#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Regex {
  public:
    unordered_set<char> alphabet;
    string completedExpression;
    string reversePolishNotation;

    string convertToRPN(string completedExpression);
    bool isSymbol(char token);

  private:
    class NFA {
      public:
        class NFAState {
          public:
            unordered_map<char, unordered_set<NFAState*>> outs;
        };
      
      public:
        unordered_set<char> alphabet_NFA;
        unordered_set<NFAState*> Q;
        NFAState* s;
        NFAState* e;
        unordered_set<NFAState*> A;
        unordered_set<NFAState*> delta(NFAState* q, char a);
      
      public:
        NFA() {/* Nothing */}
        NFA(NFAState* s_, NFAState* e_) : s(s_), e(e_) {}
        void clear();
    };
  
    class DFA {
      private:
        class DFAState {
          private:
            unordered_map<char, DFAState*> outs;
        };
      
      private:
        unordered_set<char> alphabet_DFA;
        unordered_set<DFAState*> Q;
        DFAState* s;
        unordered_set<DFAState*> A;
        DFAState* delta(DFAState* q, char a);
    };

  private:
    NFA nfa;
    DFA dfa;

    void generateNFA(string RPN);
  
  public:
    Regex(unordered_set<char> alphabet_, string regex);
    bool operator==(const Regex &rhs) const;
    bool check(string str);
    void epsilonReach(NFA::NFAState* q, unordered_set<NFA::NFAState*> &reach);
    bool checkEpsilonReach(NFA::NFAState* q);
};