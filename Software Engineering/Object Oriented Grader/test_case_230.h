#ifndef TEST_CASE_230
#define TEST_CASE_230

#include "test_case.h"
class test_case_230: public test_case{
    protected:
        std::string output_pipe;
        std::string input_pipe;
    public:
        virtual ~test_case_230();
        test_case_230();
        virtual void execute() = 0;
        virtual void view_files() = 0;
        std::string build_shell_command(std::string command_prefix, std::string working_path, std::string command_suffix);
        void build_output_pipe();
        void build_input_pipe();
        void view_file();
};

#endif