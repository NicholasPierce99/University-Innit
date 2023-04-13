#include "test_case_240_no_make.h"

//build shell command in constructor
test_case_240_no_make::test_case_240_no_make(std::string working_path, std::string executable){
    this->working_path = working_path;
    shell_command = build_shell_command("cd ", working_path, executable);
}
test_case_240_no_make::~test_case_240_no_make(){
}

//execute shell command
void test_case_240_no_make::execute(){
    system(shell_command.c_str());
}
//view files
void test_case_240_no_make::view_files(){
    std::string temp = build_shell_command("cd ", working_path, "; vim .");
    system(temp.c_str());
}