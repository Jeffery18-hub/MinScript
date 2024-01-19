//
// Created by Jun Li on 2/27/23.
//


#include "exec.h"
#include <stdlib.h>
#include <iostream>
#define ITERATIONS 100

std::string random_expr_string();

int main(int argc, char **argv) {

    if (argc == 1) {
        std::cout << "No arguments. Please check your input and run again." << std::endl;
        return 1;
    }

    if (argc ==2){
        const char * const script_argv_interp[] = { argv[1], "--interp" };
        const char * const script_argv_print[] = { argv[1], "--print" };
        for (int i = 0; i < ITERATIONS; ++i) {
            std::string in = random_expr_string();
            std::cout << i+1 << " Trying " << in << "\n";
            ExecResult result_interp = exec_program(argc, script_argv_interp, in);
            ExecResult result_print = exec_program(argc, script_argv_print, in);
            ExecResult result_again_interp = exec_program(argc, script_argv_interp, result_print.out);


            if (result_interp.out != result_again_interp.out) {
                throw std::runtime_error("different result for interp of the same msdscript\n"
                "result_interp: " + result_interp.out + "\n"+
                "result_interp_again: "+ result_again_interp.out);
            }

        }
    }

    if (argc == 3) {

        const char *const script1_argv_interp[] = {argv[1], "--interp"};
        const char *const script2_argv_interp[] = {argv[2], "--interp"};
        const char *const script1_argv_print[] = {argv[1], "--print"};
        const char *const script2_argv_print[] = {argv[2], "--print"};

        for (int i = 0; i < ITERATIONS; i++) {
            std::string in = random_expr_string();
            std::cout << i + 1 << " Trying " << in << "\n";
            ExecResult result1_interp = exec_program(2, script1_argv_interp, in);
            ExecResult result2_interp = exec_program(2, script2_argv_interp, in);
            ExecResult result1_print = exec_program(2, script1_argv_print, in);
            ExecResult result2_print = exec_program(2, script2_argv_print, in);


            std::cout << "result1_interp: " << result1_interp.out;
            std::cout << "result2_interp: " << result2_interp.out;


            if (result1_interp.out != result2_interp.out)
                throw std::runtime_error("different result for interp:\n"
                "result1: "+ result1_interp.out+
                "result2: "+result2_interp.out);



            std::cout << "result1_print: " << result1_print.out;
            std::cout << "result2_print: " << result2_print.out;


            if (result1_print.out != result2_print.out)
                throw std::runtime_error("different result for print:\n"
                                         "result1: "+ result1_print.out+"\n"
                                         "result2: "+result2_print.out);



        }
    }

    if (argc > 3) {
        std::cout << "Too many arguments. Please check your input and run again." << std::endl;
        return 1;
    }

    return 0;
}

std::string random_expr_string() {
    if ((rand() % 10) < 6)
        return std::to_string(rand());
    else return random_expr_string() + "+" + random_expr_string();
}