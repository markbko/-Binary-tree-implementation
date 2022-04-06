#include "bet.h"

BET::BET() : root { nullptr } { }

BET::BET(const string postfix) : root { nullptr } {
  buildFromPostfix(postfix);
}

BET::BET(const BET& bet) : root { nullptr } {
  root = clone(bet.root);
} 

BET::~BET() {
  makeEmpty(root);
}

bool BET::buildFromPostfix(const string postfix) {
  istringstream iss(postfix);
  stack<BinaryNode*> stack;
  string character;
  
  if(!empty()) {
    makeEmpty(root);
  }
  
  // textbook steps
  while(iss >> character) {
    BinaryNode *r, *l;
    BinaryNode *node = new BinaryNode(character, nullptr, nullptr);
    // The first two symbols are operands, so we create one-node trees and push pointers to them onto a stack
    if(isOperand(character)) {
      stack.push(node);
    } else if(isOperator(character)) {
      // Next, a + is read, so two pointers to trees are popped, a new tree is formed, and a pointer to it is pushed onto the stack
      
      if(stack.size() < 2) {
            cout << "Wrong postfix expression" << endl;
            if(!empty()) {
            makeEmpty(root);
            }
            return false;
        }
        else{
            //  so two pointers to trees are popped, a new tree is formed,
            r = stack.top();
            stack.pop();
            node->right = r;

            //expression flipped if left is first
            l = stack.top();
            stack.pop();
            node->left = l;
        }
      // and a pointer to it is pushed onto the stack
      stack.push(node);
    }
  }
    
  // Error checking
  if(stack.empty() == true) {
    cout << "Wrong postfix expression" << endl;
    if(!empty()) {
    makeEmpty(root);
    }
    return false;
  }

  // the last symbol is read, two trees are merged, and a pointer to the final tree is left on the stack
  root = stack.top();
  stack.pop();
  return true;
}

const BET & BET::operator= (const BET & bet) {
  root = bet.clone(bet.root);
  return *this;
}

void BET::printInfixExpression() {
  printInfixExpression(root);
  cout << endl;
}

void BET::printPostfixExpression() {
  printPostfixExpression(root);
  cout << endl;
}

size_t BET::size() {
  return size(root);
}

size_t BET::leaf_nodes() {
  return leaf_nodes(root);
}

bool BET::empty() {
  if(root == nullptr) {
    return true;
  } else {
    return false;
  }
}

bool BET::isOperator(const string & element) {
  return(element == "+" || element == "-" || element == "/" || element == "*");
}

bool BET::isOperand(const string & element) {
  return((element >= "A" && element <= "Z") || (element >= "a" && element <= "z") || (element >= "0" && element <= "9"));
}

void BET::printInfixExpression(BET::BinaryNode *n){
    //https://en.m.wikipedia.org/wiki/Binary_expression_tree
    if(n != nullptr){
        if(isOperator(n->element) && n != root)
        {
            cout << "( ";
        }
        printInfixExpression(n->left);
        cout << n->element << " ";
        printInfixExpression(n->right);
        if(isOperator(n->element) && n != root)
        {
            cout << ") ";
        }
    }
}

void BET::makeEmpty(BinaryNode* &t) {
  if(t != nullptr) {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  t = nullptr;
}

BET::BinaryNode * BET::clone(BinaryNode *t) const {
  if(t != nullptr) 
  {
    return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
  } 
  else 
  {
      return nullptr;
  }
}

void BET::printPostfixExpression(BinaryNode *n) {
  if(n != nullptr) {
    printPostfixExpression(n->left);
    printPostfixExpression(n->right);
    cout << n->element << " ";
  }
}

size_t BET::size(BinaryNode *t) {
    if(t != nullptr)
	{
        return(size(t->left) + size(t->right) + 1);
	}
	else
	{
		return 0;
	}
}

size_t BET::leaf_nodes(BET::BinaryNode *t){
    if (t != nullptr) {
        if (t->left == nullptr && t->right == nullptr)
        {
            return 1;
        }
        else
        {
            return leaf_nodes(t->left) + leaf_nodes(t->right);
        }
    }
    else
    {
        return 0;
    }
}

int BET::checkPrecedence(string str)
{
	if(str == "("|| str == ")")
		return (3);
	else if(str == "*" || str == "/")
		return (2);
	else if(str == "+" || str == "-")
		return (1);
	else
		return 0;
}