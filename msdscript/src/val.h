//
// Created by Jun Li on 3/14/23.
//
#ifndef MSDSCRIPT_VAL_H
#define MSDSCRIPT_VAL_H

#include <stdio.h>
#include <string>
#include "pointer.h"
#include "Env.h"

class Expr;
class Env;

CLASS(Val){
public:
    virtual bool equals(PTR(Val) val) = 0;
    //virtual PTR(Expr) to_expr() = 0;
    virtual PTR(Val) add_to(PTR(Val) val) = 0;
    virtual PTR(Val) mult_with(PTR(Val) val) = 0;
    virtual std::string to_string() = 0;
    virtual PTR(Val) call(PTR(Val) actual_arg) = 0;
};

class NumVal : public Val{
public:
    int val;
    NumVal (int val);

    bool equals(PTR(Val) val) ;
    //PTR(Expr) to_expr();
    PTR(Val) add_to(PTR(Val) val) ;
    PTR(Val) mult_with(PTR(Val) val) ;
    std::string to_string() ;
    PTR(Val) call(PTR(Val) actual_arg) ;
};

class BoolVal : public Val{
public:
    bool val;
    BoolVal (bool val);

    bool equals(PTR(Val) val) ;
    //PTR(Expr) to_expr();
    PTR(Val) add_to(PTR(Val) val) ;
    PTR(Val) mult_with(PTR(Val) val) ;
    std::string to_string() ;
    PTR(Val) call(PTR(Val) actual_arg) ;
};

class FunVal: public Val {
public:
    std::string formal_arg;
    PTR(Expr) body;
    PTR(Env) env;

    FunVal(std::string formal_arg, PTR(Expr) body, PTR(Env) env);

    bool equals(PTR(Val) val) ;
    PTR(Val) add_to(PTR(Val) val) ;
    PTR(Val) mult_with(PTR(Val) val) ;
    //PTR(Expr) to_expr() ;
    std::string to_string() ;
    PTR(Val) call(PTR(Val) actual_arg) ;
};


#endif //MSDSCRIPT_VAL_H
