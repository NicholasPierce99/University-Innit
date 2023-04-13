#ifndef TEST_CASE_BUILDER
#define TEST_CASE_BUILDER

#include "cpp_java_compiler.h"
#include <string>
#include <iostream>
#include <sstream>
#include "test_case_240_make.h"
#include "test_case_240_no_make.h"
#include "test_case_230_py.h"
#include "file_manipulator.h"

//builder aggregate class
//builds and runs 230 and 240 test cases
class test_case_builder{
    private:
        std::string base_black;
        std::string class_name;
        std::string path;

        //file manipulator class pointer
        file_manipulator * fp;

        //polymorphic test case pointer
        test_case * tc;

        //necessary object for 240 test cases
        //compiles cpp/java files
        cpp_java_compiler * cjc;

        //resultant vector
        std::vector<std::string> result;

    public:
        test_case_builder(std::string class_name, std::string base_black);
        ~test_case_builder();
        void build_execute_240_make_testcase();
        void build_execute_240_no_make_testcase(std::string filename, std::string executable);
        void build_execute_230_testcase();
        void remove_files(std::vector<std::string> result);
};

#endif