#include "Regex.h"
#include <queue>
#include <stack>
#include <assert.h>

Regex::Regex(unordered_set<char> alphabet_, string regex) {
  alphabet = alphabet_;
  completedExpression = "";
  for (unsigned int i = 0; i < regex.size()-1; ++i) {
    completedExpression += regex[i];
    if (isSymbol(regex[i]) && isSymbol(regex[i+1])) 
      completedExpression += '.';
    if ((regex[i] == '*' || regex[i] == ')') && isSymbol(regex[i+1]))
      completedExpression += '.';
    if ((isSymbol(regex[i]) || regex[i] == '*' || regex[i] == ')') && regex[i+1] == '(')
      completedExpression += '.';
  }
  completedExpression += regex[regex.size()-1];
  reversePolishNotation = convertToRPN(completedExpression);
  generateNFA(reversePolishNotation);
}

/*
Convert the regular expression to the reverse polish notation.
*/
string Regex::convertToRPN(string completedExpression) {
  queue<char> output;
  stack<char> operators;
  for (unsigned int i = 0; i < completedExpression.size(); ++i) {
    char a = completedExpression[i];
    if (isSymbol(a)) {
      output.push(a);
    } else if (a == '*') {
      output.push(a);
    } else if (a == '.') {
      while (!operators.empty() && operators.top() == '.') {
        char concate = operators.top();
        operators.pop();
        output.push(concate);
      }
      operators.push(a);
    } else if (a == '+') {
      while (!operators.empty() && operators.top() == '.') {
        char concate = operators.top();
        operators.pop();
        output.push(concate);
      }
      operators.push(a);
    } else if (a == '(') {
      operators.push(a);
    } else if (a == ')') {
      assert(!operators.empty() && "Mismatched parentheses.");
      while (operators.top() != '(') {
        char op = operators.top();
        operators.pop();
        output.push(op);
        assert(!operators.empty() && "Mismatched parentheses.");
      }
      operators.pop();
    }
  }
  while (!operators.empty()) {
    char op = operators.top();
    operators.pop();
    output.push(op);
  }
  string RPN = "";
  while (!output.empty()) {
    RPN += output.front();
    output.pop();
  }
  return RPN;
}

/*
Generate the corresponding NFA using Thompson's Algorithm.
*/
void Regex::generateNFA(string RPN) {
  stack<NFA> chain;
  for (unsigned int i = 0; i < RPN.size(); ++i) {
    char a = RPN[i];
    if (isSymbol(a)) {

      NFA::NFAState* s_ = new NFA::NFAState();
      NFA::NFAState* e_ = new NFA::NFAState();
      s_->outs[a] = unordered_set<NFA::NFAState*>{e_};
      NFA singleton(s_, e_);
      chain.push(singleton);

    } else if (a == '.') {

      NFA second = chain.top();
      chain.pop();
      NFA first = chain.top();
      chain.pop();
      if (first.e->outs.find('$') != first.e->outs.end()) {
        unordered_set<NFA::NFAState*> epsilon = first.e->outs['$'];
        epsilon.insert(second.s);
        first.e->outs['$'] = epsilon;
      } else {
        first.e->outs['$'] = unordered_set<NFA::NFAState*>{second.s};
      }
      NFA combination(first.s, second.e);
      chain.push(combination);

    } else if (a == '+') {

      NFA first = chain.top();
      chain.pop();
      NFA second = chain.top();
      chain.pop();
      NFA::NFAState* s_ = new NFA::NFAState();
      NFA::NFAState* e_ = new NFA::NFAState();
      s_->outs['$'] = unordered_set<NFA::NFAState*>{first.s, second.s};
      first.e->outs['$'] = unordered_set<NFA::NFAState*>{e_};
      second.e->outs['$'] = unordered_set<NFA::NFAState*>{e_};
      NFA combination(s_, e_);
      chain.push(combination);

    } else if (a == '*') {

      NFA first = chain.top();
      chain.pop();
      NFA::NFAState* s_ = new NFA::NFAState();
      NFA::NFAState* e_ = new NFA::NFAState();
      s_->outs['$'] = unordered_set<NFA::NFAState*>{first.s, e_};
      e_->outs['$'] = unordered_set<NFA::NFAState*>{s_};
      first.e->outs['$'] = unordered_set<NFA::NFAState*>{e_};
      NFA combination(s_, e_);
      chain.push(combination);
      
    }
  }
  nfa = chain.top();
}

bool Regex::isSymbol(char token) {
  return token != '(' && token != ')' && token != '*' && token != '+' && token != '.';
}

bool Regex::check(string str) {
  unsigned int i = 0;
  queue<NFA::NFAState*> buffer;
  buffer.push(nfa.s);
  NFA::NFAState* sentinal = new NFA::NFAState();
  buffer.push(sentinal);
  while (buffer.front() != sentinal) {
    NFA::NFAState* q = buffer.front();
    buffer.pop();
    if (i == str.size()) {
      if (checkEpsilonReach(q)) {
        delete sentinal;
        return true;
      }
    }
    unordered_set<NFA::NFAState*> reach;
    epsilonReach(q, reach);
    for (NFA::NFAState* epsilonReach : reach) {
      for (NFA::NFAState* out : epsilonReach->outs[str[i]]) {
        buffer.push(out);
      }
    }
    if (buffer.front() == sentinal) {
      buffer.pop();
      buffer.push(sentinal);
      i++;
    }
  }
  delete sentinal;
  return false;
}

void Regex::epsilonReach(NFA::NFAState* q, unordered_set<NFA::NFAState*> &reach) {
  reach.insert(q);
  for (NFA::NFAState* out : q->outs['$']) {
    if (!reach.contains(out)) {
      epsilonReach(out, reach);
    }
  }
}

bool Regex::checkEpsilonReach(NFA::NFAState* q) {
  unordered_set<NFA::NFAState*> reach;
  epsilonReach(q, reach);
  for (NFA::NFAState* out : reach) {
    if (out == nfa.e) return true;
  }
  return false;
}