//
// Created by Jun Li on 3/14/23.
//

#include "val.h"
#include "expr.hpp"
#include "Env.h"

NumVal::NumVal(int val) {
    this->val = val;
}

bool NumVal::equals(PTR(Val) val) {
    PTR(NumVal)num_val = CAST(NumVal)(val);
    if (num_val == nullptr){
        return false;
    }
    return this->val == num_val->val;
}

//PTR(Expr) NumVal::to_expr() {
//    return NEW(NumExpr)(this->val);
//}

PTR(Val) NumVal::add_to(PTR(Val) val) {
    PTR(NumVal) num_val = CAST(NumVal)(val);
    if (num_val == nullptr){
        throw std::runtime_error("null pointer");
    }
    return NEW(NumVal)(this->val + num_val->val);
}

PTR(Val) NumVal::mult_with(PTR(Val)val) {
    PTR(NumVal) num_val = CAST(NumVal)(val);
    if (num_val == nullptr){
        throw std::runtime_error("null pointer");
    }
    return NEW(NumVal)(this->val * num_val->val);
}

std::string NumVal::to_string() {
    return std::to_string(this->val);
}

PTR(Val) NumVal:: call(PTR(Val) actual_arg){
    throw std::runtime_error("NumVal cannot use call");
}

BoolVal::BoolVal(bool val) {
    this->val = val;
}

bool BoolVal::equals(PTR(Val)val) {
    PTR(BoolVal) bool_val = CAST(BoolVal)(val);
    if (bool_val == nullptr){
        return false;
    }
    return this->val == bool_val->val;
}

//PTR(Expr) BoolVal::to_expr() {
//    return NEW(BoolExpr)(this->val);
//}

PTR(Val)BoolVal::add_to(PTR(Val)val) {
    throw std::runtime_error("BoolVal cannot use add_to");
}

PTR(Val)BoolVal::mult_with(PTR(Val)val) {
    throw std::runtime_error("BoolVal cannot use mult_with");
}

std::string BoolVal::to_string() {
    return this->val ? "_true" : "_false";
}

PTR(Val) BoolVal:: call(PTR(Val) actual_arg){
    throw std::runtime_error("BoolVal cannot use call");
}


FunVal::FunVal(std::string formal_arg, PTR(Expr)body, PTR(Env)env) {
    this -> formal_arg = formal_arg;
    this -> body = body;
    this -> env = env;
}

bool FunVal::equals(PTR(Val)val) {
    PTR(FunVal)n = CAST(FunVal)(val);
    if (n == NULL) return false;
    else {
        return (this -> formal_arg == n -> formal_arg &&
                this -> body -> equals(n -> body));
    }
}

PTR(Val)FunVal::add_to(PTR(Val)val) {
    throw std::runtime_error("Error: Invalid input.");
}

PTR(Val)FunVal::mult_with(PTR(Val)val) {
    throw std::runtime_error("Error: Invalid input");
}

//PTR(Expr) FunVal::to_expr() {
//    return NEW(FunExpr)(this -> formal_arg, this -> body);
//}

std::string FunVal::to_string() {
    return ("_fun (" + this -> formal_arg + ") " +
            this -> body -> to_string());
}

PTR(Val)FunVal::call(PTR(Val)actual_arg) {
    PTR(ExtendedEnv) new_env = NEW(ExtendedEnv)(this -> formal_arg, actual_arg, this -> env);
    return this -> body -> interp(new_env);
}
