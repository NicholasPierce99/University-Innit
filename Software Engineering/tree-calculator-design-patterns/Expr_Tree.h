/**
 * Honor Pledge:
 *
 * I pledge that I have neither given nor received any help
 * on this assignment.
 */
//==============================================================================

#include <map>
#include <string>
#include "Expr_Node.h"

class Expr_Tree {
    public:
        Expr_Tree();
        ~Expr_Tree();

    private:
        std::map<int, Expr_Node> tree_;

};