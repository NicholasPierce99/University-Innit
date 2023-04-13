/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Eval_Expr_Tree.h"
#include "Expr_Tree_Builder.h"
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <map>

//wrapper class for objects
class Calculator {
    public:
        Calculator(Expr_Tree_Builder builder, Eval_Expr_Tree visitor, std::string infix, Stack<Expr_Node *> postfix_nodes);
        ~Calculator();
		int get_priority(std::string s);
		bool is_operator(std::string s);
		void infix_to_postfix();
        void eval_expr();
		int get_priority_var(std::string s);
    private:
        Expr_Tree_Builder builder;
        Eval_Expr_Tree visitor;
        Expr_Node * root_;
        std::string infix;
		Stack<Expr_Node *> postfix_nodes;

};