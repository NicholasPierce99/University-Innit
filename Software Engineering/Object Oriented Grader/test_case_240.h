#ifndef TEST_CASE_240
#define TEST_CASE_240

#include "test_case.h"

//abstract class for 240 test cases
class test_case_240: public test_case{
    private:
        
    public:
        virtual ~test_case_240();
        test_case_240();
        virtual void view_files() = 0;
        virtual void execute() = 0;
        std::string build_shell_command(std::string command_prefix, std::string working_path, std::string command_suffix);
};

#endif