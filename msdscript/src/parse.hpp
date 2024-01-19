//
// Created by Jun Li on 2/20/23.
//
#pragma once

#include "expr.hpp"


#ifndef EXPR_PARSE_H
#define EXPR_PARSE_H

void consume(std::istream &in, int expect);
void skip_whitespace(std::istream &in);
PTR(Expr)parse_str(std::string s);

PTR(Expr)parse_num(std::istream &in);
PTR(Expr)parse_val(std::istream &in);
std::string parse_keyword(std::istream &in);
PTR(Expr)parse_let(std::istream &in);
PTR(Expr)parse_if(std::istream &in);
PTR(Expr)parse_function(std::istream &in);

PTR(Expr)parse_expr(std::istream &in);
PTR(Expr)parse_comparg(std::istream &in);
PTR(Expr)parse_addend(std::istream &in);
PTR(Expr)parse_multicand(std::istream &in);
PTR(Expr)parse_inner(std::istream &in);

#endif //EXPR_PARSE_H
