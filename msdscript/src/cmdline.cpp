//
// Created by Jun Li on 2/21/23.
//

#include "string"
#include "iostream"
#include "cmdline.hpp"
#include "parse.hpp"
#include "expr.hpp"
#include "Env.h"

#define CATCH_CONFIG_RUNNER

#include "catch.h"

void use_arguments(int argc, char * argv[]){
    if (argc == 1){
        return;
    }
    if (argc > 1){
        bool test = false;
        for (int i = 1; i < argc; i++){
            std::string args = argv[i];
            if (args == "--help"){
                std::cout<<"Valid command lines: '--test' '--interp' '--print' '--pretty-print'."<<"\n";
                exit(0);
            }
            else if (args == "--test"){
                if (test == false){
                    if (Catch::Session().run(1,argv) != 0){
                        std::cerr << "Tests failed!" << "\n";
                        exit(1);
                    }
                    test = true;
                }
                else{
                    std::cout << "Tested already!" <<"\n";
                    exit(1);
                }
            }
            else if (args == "--interp"){
               PTR(Expr)input = parse_expr(std::cin);
                PTR(Val) value = input->interp(Env::empty);
                std::cout << value->to_string() << "\n";
            }
            else if (args == "--print"){
               PTR(Expr)input = parse_expr(std::cin);
                input->print(std::cout);
            }
            else if (args == "--pretty-print"){
               PTR(Expr)input = parse_expr(std::cin);
                std::cout << input->to_pretty_string();
            }
            else {
                std::cerr << "Invalid Argument\n";
                exit(1);
            }
            std::cout << "\n";
        }
    }
}
