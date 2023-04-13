/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include "Eval_Expr_Tree.h"
#include "Number_Expr_Node.h"
#include "Subtract_Expr_Node.h"
#include "Add_Expr_Node.h"
#include "Modulo_Expr_Node.h"
#include "Divide_Expr_Node.h"
#include "Multiply_Expr_Node.h"

Eval_Expr_Tree::Eval_Expr_Tree() {
}
Eval_Expr_Tree::~Eval_Expr_Tree() {

}
void Eval_Expr_Tree::visit_add_node(Add_Expr_Node & node) {
    result_ = node.eval();
}
void Eval_Expr_Tree::visit_subtract_node(Subtract_Expr_Node & node) {
    result_ = node.eval();
}
void Eval_Expr_Tree::visit_multiply_node(Multiply_Expr_Node & node) {
    result_ = node.eval();
}
void Eval_Expr_Tree::visit_divide_node(Divide_Expr_Node & node) {
    result_ = node.eval();
}
void Eval_Expr_Tree::visit_modulo_node(Modulo_Expr_Node & node) {
    result_ = node.eval();
}
void Eval_Expr_Tree::visit_number_node(Number_Expr_Node & node) {

}

int Eval_Expr_Tree::result() const {
    return result_;
}