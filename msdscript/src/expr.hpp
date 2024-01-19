/**
* \file
* \brief expr.hpp is the header file for the expr.cpp
*
* you can use this file to implement your expression classes
* \author Jun Li
*/

#pragma once

#ifndef expr_hpp
#define expr_hpp

#include <stdio.h>
#include <string>
#include "val.h"
#include "pointer.h"
#include "Env.h"

/*!\brief
* Expr class to represent an expression.
*
* This is a virtual class which is the base class for all expressions.
*/
class Val;

typedef enum{
    prec_none,
    prec_add,
    prec_mult,
    prec_let,
    prec_eq,
    }Precedence_t;

CLASS(Expr) {
public:
    virtual ~Expr() {};
    virtual bool equals(PTR(Expr) e) = 0;
    virtual PTR(Val) interp(PTR(Env) env) = 0;
    virtual bool has_variable() = 0;
    virtual void print(std::ostream &outputStream) = 0;
    virtual void pretty_print(std::ostream &outputStream) = 0;
    virtual void pretty_print_at(std::ostream &outputStream, Precedence_t parent_prec, long *pos) = 0;

    std::string to_string();
    std::string to_pretty_string();

};

/*!\brief
* NumExpr expression class to represent a number
*
* you can use this class to represent a number
*/

class NumExpr : public Expr {
public:
    int val; ///< the value of the number
    Precedence_t prec;

    NumExpr(int val);


    /**
    *\brief to check if two expressions are equal
    *\param e the expression to be compared
    *\return true if the two expressions are equal, false otherwise
    */
    bool equals(PTR(Expr) e);

    /**
    *\brief to interpret the expression
    *\return the value of the expression
    */
    PTR(Val) interp(PTR(Env) env);

    /**
    *\brief to check if the expression has a variable
    *\return true if the expression has a variable, false otherwise
    */
    bool has_variable();

    void print(std::ostream &outputStream);
    void pretty_print(std::ostream &outputStream);
    void pretty_print_at(std::ostream &outputStream, Precedence_t parent_prec, long* pos);
};

/*!\brief
* AddExpr expression class to represent an addition
*
* you can use this class to represent an addition and it inherits from Expr
*/
class AddExpr : public Expr {
public:
    PTR(Expr) lhs; ///< the left hand side of the addition
    PTR(Expr) rhs; ///< the right hand side of the addition
    Precedence_t prec;

    AddExpr(PTR(Expr)lhs, PTR(Expr) rhs);


    /**
    *\brief to check if two expressions are equal
    *\param e the expression to be compared
    *\return true if the two expressions are equal, false otherwise
    */
    bool equals(PTR(Expr) e);

    /**
    *\brief to interpret the expression
    *\return the value of the expression
    */
    PTR(Val) interp(PTR(Env) env);

    /**
    *\brief to check if the expression has a variable
    *\return true if the expression has a variable, false otherwise
    */
    bool has_variable();
    void print(std::ostream &outputStream);
    void pretty_print(std::ostream &outputStream);
    void pretty_print_at(std::ostream &outputStream, Precedence_t parent_prec, long* pos);
};

/*!\brief
* MultExpr expression class to represent a multiplication
*
* you can use this class to represent a multiplication and it inherits from Expr
*/
class MultExpr : public Expr {
public:
    PTR(Expr) lhs; ///< the left hand side of the multiplication
    PTR(Expr) rhs; ///< the right hand side of the multiplication
    Precedence_t prec;

    MultExpr(PTR(Expr)lhs, PTR(Expr)rhs);

    /**
    *\brief to check if two expressions are equal
    *\param e the expression to be compared
    *\return true if the two expressions are equal, false otherwise
    */
    bool equals(PTR(Expr) e);

    /**
    *\brief to interpret the expression
    *\return the value of the expression
    */
   PTR(Val) interp(PTR(Env) env);

    /**
    *\brief to check if the expression has a variable
    *\return true if the expression has a variable, false otherwise
    */
    bool has_variable();

    /**
    *\brief to substitute a variable with an expression
    *\param s the variable to be substituted
    *\param e the expression to be substituted
    *\return the expression after substitution
    */
    void print(std::ostream &outputStream);
    void pretty_print(std::ostream &outputStream);
    void pretty_print_at(std::ostream &outputStream, Precedence_t parent_prec, long*pos);
};

/*!\brief
* VarExpr class to represent a variable
*
* you can use this class to represent a variable and it inherits from Expr
*/
class VarExpr : public Expr {
public:
    std::string s; ///< the name of the variable
    Precedence_t prec;

    VarExpr(std::string s);

    /**
    *\brief to check if two expressions are equal
    *\param expr the expression to be compared
    *\return true if the two expressions are equal, false otherwise
    */
    bool equals(PTR(Expr) expr);

    /**
    *\brief to interpret the expression
    *\return the value of the expression
    */
    PTR(Val) interp(PTR(Env) env);

    /**
    *\brief to check if the expression has a variable
    *\return true if the expression has a variable, false otherwise
    */
    bool has_variable();


    void print(std::ostream &outputStream);
    void pretty_print(std::ostream &outputStream);
    void pretty_print_at(std::ostream &outputStream, Precedence_t parent_prec, long*pos);
};

class LetExpr : public Expr {
public:
    std::string name;
    PTR(Expr)rhs;
    PTR(Expr) body;

    LetExpr(std::string name, PTR(Expr) rhs, PTR(Expr)body);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &outputStream);
    void pretty_print(std::ostream &outputStream);
    void pretty_print_at(std::ostream &outputStream, Precedence_t parent_prec, long*pos);
    };

class BoolExpr : public Expr {
public:
    bool b;

    BoolExpr(bool b);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &outputStream);
    void pretty_print(std::ostream &outputStream);
    void pretty_print_at(std::ostream &outputStream, Precedence_t parent_prec, long* pos);
    };


class IfExpr : public Expr {
public:
    PTR(Expr)condition;
    PTR(Expr)then_;
    PTR(Expr)else_;

    IfExpr(PTR(Expr)cond, PTR(Expr)then, PTR(Expr)else_);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &outputStream);
    void pretty_print(std::ostream &outputStream);
    void pretty_print_at(std::ostream &outputStream, Precedence_t parent_prec, long* pos);

    };

class EqExpr : public Expr {
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;

    EqExpr(PTR(Expr)lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
    PTR(Val) interp(PTR(Env) env);
    bool has_variable();
    void print(std::ostream &outputStream);
    void pretty_print(std::ostream &outputStream);
    void pretty_print_at(std::ostream &outputStream, Precedence_t parent_prec, long* pos);
    };

class FunExpr: public Expr {
public:
    std::string formal_arg;
    PTR(Expr) body;

    FunExpr (std::string formal_arg, PTR(Expr) body);
    bool equals(PTR(Expr) e) ;
    PTR(Val) interp(PTR(Env) env) ;
    bool has_variable() ;
    void print(std::ostream& out) ;
    void pretty_print(std::ostream &out) ;
    void pretty_print_at(std::ostream &out,Precedence_t p,long* position) ;
};


class CallExpr: public Expr {
public:
    PTR(Expr) to_be_called;
    PTR(Expr) actual_arg;

    CallExpr (PTR(Expr) to_be_called, PTR(Expr) actual_arg);
    bool equals(PTR(Expr) e) ;
    PTR(Val) interp(PTR(Env) env) ;
    bool has_variable() ;
    void print(std::ostream& out);
    void pretty_print(std::ostream &out);
    void pretty_print_at(std::ostream &out,Precedence_t prec,long*position) ;

};


#endif /* expr_hpp */
