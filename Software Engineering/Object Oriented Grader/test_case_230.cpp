#include "test_case_230.h"

test_case_230::test_case_230(){
}
test_case_230::~test_case_230(){
}
//assemble shell command executed by system
std::string test_case_230::build_shell_command(std::string command_prefix, std::string working_path, std::string command_suffix){
    build_output_pipe();
    build_input_pipe();
    return command_prefix.append(working_path);
}
//build stdout redirect
void test_case_230::build_output_pipe(){
    this->output_pipe = " > ";
    this->output_pipe.append("output.txt");
}
//build stdin redirect
void test_case_230::build_input_pipe(){
    this->input_pipe = " < ";
    this->input_pipe.append("input.txt");
}
