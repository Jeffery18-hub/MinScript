//
// Created by Jun Li on 4/11/23.
//

#pragma once
#ifndef MSDSCRIPT_ENV_H
#define MSDSCRIPT_ENV_H


#include "pointer.h"
#include "val.h"

class Val;

CLASS(Env) {
public:
    static PTR(Env) empty;
    virtual PTR(Val) lookup(std::string find_name) = 0;
};

class EmptyEnv : public Env {
public:
    EmptyEnv();
    PTR(Val) lookup(std::string find_name);
};

class ExtendedEnv : public Env {
public:
  std::string name;
  PTR(Val) val;
  PTR(Env) rest;

  ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest);

  PTR(Val) lookup(std::string find_name);
};


#endif //MSDSCRIPT_ENV_H
