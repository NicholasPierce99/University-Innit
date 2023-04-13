#include "Expr_Node.h"
#include <memory>

class Unary_Expr_Node: public Expr_Node {
    public:
        Unary_Expr_Node(Expr_Node * n1);
        virtual ~Unary_Expr_Node();
        virtual int eval() = 0;
    protected:
        Expr_Node * child_;
};