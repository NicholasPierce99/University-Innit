/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Calculator.h"
#include <stdlib.h>

//need to move parts into a wrapper(for now I'm going to use c functions)
//need to deal with parens, will do this as a token system instead of using separate paren nodes
//working on using the map for alphabetical order
int main() {

	
	//running boolean
	bool running = true;
	
	std::cout << "welcome to the calculator" << std::endl;
    std::cout << "please input numbers, (), variables,  or operators, delimmited by spaces, or type QUIT to quit" << std::endl;
	
	//input string
	std::string expr;
	while(running){
		
		getline(std::cin, expr);
		
		if(expr == "QUIT") {
			running = false;
			std::cout << "thanks for calculating!" << std::endl;
		}
		else {
			//catch invalid expressions
			try{
			Stack<Expr_Node *> s;
			Expr_Tree_Builder builder;
			Eval_Expr_Tree visitor;
			Calculator calculator(builder, visitor, expr, s);
			

			calculator.infix_to_postfix();
			}
			catch(Stack<Expr_Node *>::empty_exception){
				std::cout << "invalid expression :(" << std::endl;
			}
		}
	}
}
