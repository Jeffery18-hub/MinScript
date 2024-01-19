/**
* \file
* \brief expr.cpp is the implementation file for the expr.hpp
*
* there are four classes in this file: NumExpr, AddExpr, Mul, Var_Expr
* \author Jun Li
*/


#include "expr.hpp"
#include<iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include "val.h"


std::string Expr::to_string() {
    std::stringstream ss;
    THIS->print(ss);
    return ss.str();
}

std::string Expr::to_pretty_string() {
    std::stringstream ss;
    THIS->pretty_print(ss);
    return ss.str();
}

NumExpr::NumExpr(int val) {
    this->val = val;

}

bool NumExpr::equals(PTR(Expr) e) {
    PTR(NumExpr) n = CAST(NumExpr)(e);
    if (n == nullptr) {
        return false;
    } else {
        return this->val == n->val;
    }
}

PTR(Val) NumExpr::interp(PTR(Env) env) {
    return NEW(NumVal)(this->val);
}

bool NumExpr::has_variable() {
    return false;
}


void NumExpr::print(std::ostream &out) {
    out << this->val;
}

void NumExpr::pretty_print(std::ostream &out) {
    pretty_print_at(out, prec_none, 0);
}

void NumExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *positon) {
    out << this->val;
}

AddExpr::AddExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;

}

bool AddExpr::equals(PTR(Expr) e) {
    PTR(AddExpr) n = CAST(AddExpr)(e);
    if (n == nullptr) {
        return false;
    } else {
        return this->lhs->equals(n->lhs) && this->rhs->equals(n->rhs);
    }
}

PTR(Val)  AddExpr::interp(PTR(Env) env) {
    return ((this->lhs->interp(env))->add_to(this->rhs->interp(env)));
}

bool AddExpr::has_variable() {
    return this->lhs->has_variable() || this->rhs->has_variable();
}


void AddExpr::print(std::ostream &out) {
    out << "(";
    lhs->print(out);
    out << "+";
    rhs->print(out);
    out << ")";
}

void AddExpr::pretty_print(std::ostream &out) {
    long position = 0;
    long *posi_ptr = &position;
    pretty_print_at(out, prec_none, posi_ptr);

}

void AddExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *position) {
    if (p == prec_add || p == prec_mult || p == prec_let) {
        out << "(";
    }
    lhs->pretty_print_at(out, prec_add, position);
    out << " + ";
    rhs->pretty_print_at(out, prec_none, position);

    if (p == prec_add || p == prec_mult || p == prec_let) {
        out << ")";
    }
}


MultExpr::MultExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;

}

bool MultExpr::equals(PTR(Expr) e) {
    PTR(MultExpr) n = CAST(MultExpr)(e);
    if (n == NULL) {
        return false;
    } else {
        return this->lhs->equals(n->lhs) && this->rhs->equals(n->rhs);
    }
}

PTR(Val)  MultExpr::interp(PTR(Env) env) {
    return ((this->lhs->interp(env))->mult_with(this->rhs->interp(env)));
}

bool MultExpr::has_variable() {
    return this->lhs->has_variable() || this->rhs->has_variable();
}


void MultExpr::print(std::ostream &out) {
    out << "(";
    lhs->print(out);
    out << "*";
    rhs->print(out);
    out << ")";

}

void MultExpr::pretty_print(std::ostream &out) {
    long position = 0;
    long *posi_ptr = &position;
    pretty_print_at(out, prec_none, posi_ptr);

}

void MultExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *position) {
    if (p == prec_add || p == prec_mult || p == prec_let) {
        out << "(";
    }
    lhs->pretty_print_at(out, prec_mult, position);
    out << " * ";
    rhs->pretty_print_at(out, prec_none, position);
    if (p == prec_add || p == prec_mult || p == prec_let) {
        out << ")";
    }

}


VarExpr::VarExpr(std::string val) {
    this->s = val;
}

bool VarExpr::equals(PTR(Expr) e) {
    PTR(VarExpr) n = CAST(VarExpr)(e);
    if (n == nullptr) {
        return false;
    } else {
        return this->s == n->s;
    }
}

PTR(Val)  VarExpr::interp(PTR(Env) env) {
    return env->lookup(this->s);
}

bool VarExpr::has_variable() {
    return true;
}


void VarExpr::print(std::ostream &out) {
    out << this->s;

}

void VarExpr::pretty_print(std::ostream &out) {
    pretty_print_at(out, prec_none, 0);

}

void VarExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *position) {
    out << this->s;

}

LetExpr::LetExpr(std::string name, PTR(Expr) rhs, PTR(Expr) body) {
    this->name = name;
    this->rhs = rhs;
    this->body = body;
}

bool LetExpr::equals(PTR(Expr) e) {
    PTR(LetExpr) n = CAST(LetExpr)(e);
    if (n == nullptr) {
        return false;
    } else {
        return (this->name == (n->name) && this->rhs->equals(n->rhs)
                && this->body->equals(n->body));
    }
}

PTR(Val)  LetExpr::interp(PTR(Env) env) {
    PTR(Val) rhs_val = this->rhs->interp(env);
    PTR(Env) new_env = NEW(ExtendedEnv)(this->name, rhs_val, env);
    return this->body->interp(new_env);
}

bool LetExpr::has_variable() {
    return (this->rhs->has_variable() || this->body->has_variable());
}


void LetExpr::print(std::ostream &out) {
    out << "(_let ";
    out << this->name;
    out << "=";
    this->rhs->print(out);
    out << " _in ";
    this->body->print(out);
    out << ")";

}

void LetExpr::pretty_print(std::ostream &out) {
    long position = 0;
    long *posi_ptr = &position;
    pretty_print_at(out, prec_none, posi_ptr);

}

void LetExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *position) {
    if (p == prec_add || p == prec_mult || p == prec_let) {
        out << "(";
    }
    long curr_posi = out.tellp();
    long spaces = curr_posi - *position;
    out << " _let " << name << " = ";
    rhs->pretty_print_at(out, prec_none, position);
    out << "\n";
    *position = out.tellp();
    int spaces_count = 0;
    while (spaces_count < spaces) {
        out << " ";
        spaces_count++;
    }
    out << "_in ";
    body->pretty_print_at(out, prec_none, position);
    if (p == prec_add || p == prec_mult || p == prec_let) {
        out << ")";
    }
}

BoolExpr::BoolExpr(bool val) {
    this->b = val;

}

bool BoolExpr::equals(PTR(Expr) e) {
    PTR(BoolExpr) boolVal = CAST(BoolExpr)(e);
    if (boolVal == nullptr)
        return false;
    return this->b == boolVal->b;
}

PTR(Val)  BoolExpr::interp(PTR(Env) env) {
    return NEW(BoolVal)(this->b);
}

bool BoolExpr::has_variable() {
    return false;
}


void BoolExpr::print(std::ostream &out) {
    if (this->b == true) {
        out << "_true";
    } else {
        out << "_false";
    }
}

void BoolExpr::pretty_print(std::ostream &out) {
    pretty_print_at(out, prec_none, 0);
}

void BoolExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *position) {
    print(out);
}

EqExpr::EqExpr(PTR(Expr) lhs, PTR(Expr) rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool EqExpr::equals(PTR(Expr) e) {
    PTR(EqExpr) n = CAST(EqExpr)(e);
    if (n == NULL)
        return false;
    return lhs->equals(n->lhs) && rhs->equals(n->rhs);
}

PTR(Val) EqExpr::interp(PTR(Env) env) {
    return NEW(BoolVal)(this->lhs->interp(env)->equals(this->rhs->interp(env)));
}

bool EqExpr::has_variable() {
    return this->lhs->has_variable() || this->rhs->has_variable();
}


void EqExpr::print(std::ostream &out) {
    out << "(";
    this->lhs->print(out);
    out << "==";
    this->rhs->print(out);
    out << ")";
}

void EqExpr::pretty_print(std::ostream &out) {
    long position = 0;
    long *posi_ptr = &position;
    this->lhs->pretty_print_at(out, prec_eq, posi_ptr);
    out << " == ";
    this->rhs->pretty_print_at(out, prec_none, posi_ptr);
    //pretty_print_at(out,prec_eq,posi_ptr);

}

void EqExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *position) {
    if (p == prec_none) {
        this->lhs->pretty_print_at(out, prec_eq, position);
        out << " == ";
        this->rhs->pretty_print_at(out, prec_none, position);
    } else {
        out << "(";
        this->lhs->pretty_print_at(out, prec_eq, position);
        out << " == ";
        this->rhs->pretty_print_at(out, prec_none, position);
        out << ")";
    }
}

IfExpr::IfExpr(PTR(Expr) condition, PTR(Expr) then_part, PTR(Expr) else_part) {
    this->condition = condition;
    this->then_ = then_part;
    this->else_ = else_part;
}

bool IfExpr::equals(PTR(Expr) e) {
    PTR(IfExpr) n = CAST(IfExpr)(e);
    if (n == NULL) return false;
    return this->condition->equals(n->condition) &&
           this->then_->equals(n->then_) &&
           this->else_->equals(n->else_);
}

PTR(Val) IfExpr::interp(PTR(Env) env) {
    PTR(Val) con = this->condition->interp(env);
    PTR(BoolVal) casted_con = CAST(BoolVal)(con);

    if (casted_con->val)
        return then_->interp(env);
    else
        return else_->interp(env);
}

bool IfExpr::has_variable() {
    return this->condition->has_variable() ||
           this->then_->has_variable() ||
           this->else_->has_variable();
}


void IfExpr::print(std::ostream &out) {
    out << "(_if ";
    this->condition->print(out);
    out << " _then ";
    this->then_->print(out);
    out << " _else ";
    this->else_->print(out);
    out << ")";
}

void IfExpr::pretty_print(std::ostream &out) {
    long position = 0;
    long *posi_ptr = &position;
    pretty_print_at(out, prec_none, posi_ptr);
}

void IfExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *position) {
    if (p == prec_add || p == prec_mult || p == prec_let || p == prec_eq) {
        out << "(";
    }
    long curr_posi = out.tellp();
    long spaces = curr_posi - *position;
    out << " _if ";
    this->condition->pretty_print_at(out, prec_none, position);
    out << "\n";
    *position = out.tellp();
    int spaces_count = 0;
    while (spaces_count < spaces) {
        out << " ";
        spaces_count++;
    }
    out << "_then ";
    this->then_->pretty_print_at(out, prec_none, position);
    out << "\n";
    *position = out.tellp();
    spaces_count = 0;
    while (spaces_count < spaces) {
        out << " ";
        spaces_count++;
    }
    out << "_else ";
    this->else_->pretty_print_at(out, prec_none, position);
    if (p == prec_add || p == prec_mult || p == prec_let || p == prec_eq) {
        out << ")";
    }
}


FunExpr::FunExpr(std::string formal_arg, PTR(Expr) body) {
    this->formal_arg = formal_arg;
    this->body = body;
}

bool FunExpr::equals(PTR(Expr) e) {
    PTR(FunExpr) n = CAST(FunExpr)(e);
    if (n == NULL) return false;
    return (this->formal_arg == n->formal_arg &&
            this->body->equals(n->body));
}

PTR(Val) FunExpr::interp(PTR(Env) env) {
    return NEW(FunVal)(this->formal_arg, this->body, env);
}

void FunExpr::print(std::ostream &out) {
    out << "(_fun (" << this->formal_arg << ") ";
    this->body->print(out);
    out << ")";
}

bool FunExpr::has_variable() {}

void FunExpr::pretty_print(std::ostream &out) {}

void FunExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *position) {}

CallExpr::CallExpr(PTR(Expr) to_be_called, PTR(Expr) actual_arg) {
    this->to_be_called = to_be_called;
    this->actual_arg = actual_arg;
}

bool CallExpr::equals(PTR(Expr) e) {
    PTR(CallExpr) n = CAST(CallExpr)(e);
    if (n == NULL) return false;
    return (this->to_be_called->equals(n->to_be_called) &&
            this->actual_arg->equals(n->actual_arg));
}

PTR(Val) CallExpr::interp(PTR(Env) env) {
    return to_be_called->interp(env)->call(actual_arg->interp(env));
}


void CallExpr::print(std::ostream &out) {
    this->to_be_called->print(out);
    out << "(";
    this->actual_arg->print(out);
    out << ")";
}

bool CallExpr::has_variable() {

}

void CallExpr::pretty_print(std::ostream &out) {

}

void CallExpr::pretty_print_at(std::ostream &out, Precedence_t p, long *position) {

}



