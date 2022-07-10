#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Regex {
  private:
    /**
     * @brief Non-deterministic finite automata class.
     * 
     */
    class NFA {
      public:

        /**
         * @brief NFA state class.
         * 
         */
        class NFAState {
          public:
            // Paths that go out from the state.
            unordered_map<char, unordered_set<NFAState*>> outs;
        };

        NFAState* s;  // The start state.
        NFAState* e;  // The end state.

        /**
         * @brief Default constructor.
         */
        NFA() {};

        /**
         * @brief Constructor with the start state and end state.
         * 
         */
        NFA(NFAState* s_, NFAState* e_) : s(s_), e(e_) {}

        /**
         * @brief Destructor helper function.
         * 
         */
        void clear();
    };

    // The NFA corresponding to the regular expression.
    NFA nfa;

    // The completed regular expression with all concatenation operators.
    string completedExpression;

    /**
     * @brief Converts the regular expression to the reverse polish notation.
     * 
     * @param completedExpression The completed regular expression.
     * @return The reverse polish notation.
     */
    string convertToRPN(string completedExpression);

    /**
     * @brief Generates the corresponding NFA using Thompson's Algorithm.
     * 
     * @param RPN The reverse polish notation.
     */
    void generateNFA(string RPN);

    /**
     * @brief Checks whether the character is a symbol or an operator.
     * 
     * @param token The character.
     * @return true if token is a symbol.
     * @return false if token is an operator.
     */
    bool isSymbol(char token);

    /**
     * @brief Records the epsilon-reach of a state as a set of states.
     * 
     * @param q The starting state.
     * @param reach The corresponding set of states.
     */
    void recordEpsilonReach(NFA::NFAState* q, unordered_set<NFA::NFAState*> &epsilonReach);

    /**
     * @brief Checks if the epsilon-reach of a state contains the accepting state.
     * 
     * @param q The starting state.
     * @return true
     * @return false 
     */
    bool checkAcceptance(NFA::NFAState* q);

  public:
    /**
     * @brief Default constructor
     * 
     * @param regex The regular expression.
     */
    Regex(string regex);
    
    /**
     * @brief Compares whether two regular expression describe the same language.
     * 
     * @param rhs 
     * @return true 
     * @return false 
     */
    bool operator==(const Regex &rhs) const;

    /**
     * @brief Checks whether a string matches the given regular expression.
     * 
     * @param str 
     * @return true 
     * @return false 
     */
    bool check(string str);
};

/*
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
        NFA() {}
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
*/