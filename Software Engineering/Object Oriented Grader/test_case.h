#ifndef TEST_CASE
#define TEST_CASE

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

class test_case{
    protected:
        std::string working_path;
        std::string shell_command;
    public:
        //abstract execute
        //child class test cases will execute
        virtual ~test_case();
        test_case();
        virtual void execute() = 0;
        virtual void view_files() = 0;
        virtual std::string build_shell_command(std::string command_prefix, std::string working_path, std::string command_suffix) = 0;
};

#endif