#ifndef BET_H
#define BET_H
#include <stack>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class BET {
  
  public:
    BET();  // default constructor (build empty tree)
    BET(const string postfix);  // constructor that builds tree based on postfix expression
    BET(const BET&);  // copy constructor
    ~BET(); // destructor
  
    bool buildFromPostfix(const string postfix);  // build tree based on postfix expression
    const BET & operator= (const BET &);  // assignment operator
    
    void printInfixExpression();// print infix form
    void printPostfixExpression(); // print postfix form
    size_t size();// return the number of nodes in the tree 
    size_t leaf_nodes();// return the number of leaf nodes in the tree
    bool empty();// return true if the tree is empty, else false
    bool isOperator(const string & exp);
    bool isOperand(const string & exp);
    int checkPrecedence(string expression);
  
  private:
    struct BinaryNode {
      string element;
      BinaryNode *left;
      BinaryNode *right;
      
      BinaryNode (const string & e, BinaryNode *l, BinaryNode *r)
        : element(e), left(l), right(r) { }
    };
  
    BinaryNode *root;
    
    void printInfixExpression(BinaryNode *n);// print infix expression (handles adding parentheses)
    void makeEmpty(BinaryNode* &t);// deletes all nodes in subtree pointed to by t
    BinaryNode * clone(BinaryNode *t) const;// clone all nodes in subtree pointed to by t
    void printPostfixExpression(BinaryNode *n); // print postfix expression
    size_t size(BinaryNode *t);// returns number of nodes in subtree pointed to by t
    size_t leaf_nodes(BinaryNode *t);// return number of leaf nodes in the subtree pointed to by t
  
};

#include "bet.hpp"

#endif