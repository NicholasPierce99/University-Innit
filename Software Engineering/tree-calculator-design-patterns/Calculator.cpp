
/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Calculator.h"
//constructor, takes in builder, visitor, infix string, and a stack of nodes
Calculator::Calculator(Expr_Tree_Builder builder, Eval_Expr_Tree visitor, std::string infix, Stack<Expr_Node *> postfix_nodes) 
:builder(builder),
visitor(visitor),
root_(nullptr),
infix(infix),
postfix_nodes(postfix_nodes){

}
Calculator::~Calculator(){
}

//returns true if infix token is an operator
bool Calculator::is_operator(std::string s){
    if (s == "*" || s == "/" || s == "%" || s == "+" || s == "-"){
        return true;
    }
    return false;
}
//get the priority of the current token, *, /, % have the highest priority
int Calculator::get_priority(std::string s){
	if(s == "*" || s == "/" || s == "%") {
		return 2;
	}
	if(s == "+" || s == "-"){
		return 1;
	}
	return 0;
}
//I know this method is kinda hacky
//get priority of the variable
int Calculator::get_priority_var(std::string s) {
	if(s == "a") {
		return 25;
	}
	else if (s == "b"){
		return 24;
	}
	else if (s == "c"){
		return 23;
	}
	else if (s == "d") {
		return 22;
	}
	else if (s == "e") {
		return 21;
	}
	else if (s == "f") {
		return 20;
	}
	else if (s == "g") {
		return 19;
	}
	else if (s == "h") {
		return 18;
	}
	else if (s == "i") {
		return 17;
	}
	else if (s == "j") {
		return 16;
	}
	else if (s == "k") {
		return 15;
	}
	else if (s == "l") {
		return 14;
	}
	else if(s == "m") {
		return 13;
	}
	else if (s == "n"){
		return 12;
	}
	else if (s == "o") {
		return 11;
	}
	else if (s == "p") {
		return 10;
	}
	else if(s == "q") {
		return 9;
	}
	else if (s == "r") {
		return 8;
	}
	else if(s == "s") {
		return 7;
	}
	else if(s == "t") {
		return 6;
	}
	else if (s == "u") {
		return 5;
	}
	else if(s == "v") {
		return 4;
	}
	else if(s == "w"){
		return 3;
	}
	else if(s == "x") {
		return 2;
	}
	else if(s == "y") {
		return 1;
	}
	else if(s == "z"){
		return 0;
	}
}
//convert the current expression to an infix to postfix expression using 2 string stacks (I finally fixed my stack to work with strings)
void Calculator::infix_to_postfix(){
	 //use the calculator algorithm to define operations
        //1.If e is operand, then append to end of postfix expression
        //2.If e is operator, & (stack is empty or e of greater precedence than top of stack), then push e on stack. 
        //Else pop from stack & append to postfix until e has greater precedence than top of stack or empty, 
        //then push e on stack3.If e is a parenthesis, pop elements from stack and append until found matching open parenthesis 
	
	//string stream used for input
	std::istringstream input(infix);
	std::string token;
	
	//stack of strings to manipulate expression
	Stack <std::string> operators;
	Stack <std::string> output;
	Stack <std::string> variables;
	
	//while there are more tokens, do calculator algorithm
	while (!input.eof ()) {
		input >> token;
		
		if(is_operator(token)){
			
			if(!operators.is_empty()){
				
				if(is_operator(operators.top())){
					
					while(!operators.is_empty() && get_priority(operators.top()) >= get_priority(token)){
						
						output.push(operators.top());
						operators.pop();
					}
				}
			}
			operators.push(token);
		}
		else if(token == "("){
			operators.push(token);
		}
		else if(token == ")"){
			
			while(operators.top() != "("){
				output.push(operators.top());
				operators.pop();
			}
			
			operators.pop();
		}
		else{
			if(isalpha(token[0])) {
				std::tolower(token[0]);
				if(variables.is_empty()){
					variables.push(token);
				}
				//handle alphabetical order
				else if(get_priority_var(token) < get_priority_var(variables.top())) {
					output.push(token);
				}
				else{
					output.push(token);
				}
			}
			else {
				//if token is an operand
				output.push(token);
			}
		}
	}
	
	while(!operators.is_empty()){
		output.push(operators.pop());
	}
	while(!output.is_empty()){
		operators.push(output.pop());
	}
	while(!variables.is_empty()) {
		operators.push(variables.pop());
	}
	//eval the current operator stack
	//builder builds root node from tokens in the postfix stack
	while(!operators.is_empty()){
		if(isdigit(operators.top()[0])) {
            builder.build_number_node(std::stoi(operators.top()), postfix_nodes);
        }
        else if(isalpha(operators.top()[0])) {
            std::string temp;
            std::cout << "please input a value for the variable" <<std::endl;
			std::cin >> temp;
			try{
				builder.build_number_node(std::stoi(temp), postfix_nodes);
			}
			catch(...){
				std::cout << "invalid input" << std::endl;
			}
        }
        else if(operators.top() == "+") {
            builder.build_add_node(postfix_nodes);
        }
        else if (operators.top() == "-") {
            builder.build_subtract_node(postfix_nodes);
        }
        else if (operators.top() == "*") {
            builder.build_multiply_node(postfix_nodes);
        }
        else if (operators.top() == "/") {
            builder.build_divide_node(postfix_nodes);
        }
        else if (operators.top() == "%") {
            builder.build_divide_node(postfix_nodes);
        }
		operators.pop();
    }

	//retrieve visitor
	//accept visitor at root
	//visitor traverses tree
	Expr_Node * root_ = builder.get_root(postfix_nodes);
	root_->accept(visitor);
	std::cout << visitor.result() << std::endl;
}


