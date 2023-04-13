#include "test_case_240_make.h"

//build shell command in constructor
test_case_240_make::test_case_240_make(std::string working_path){
    this->working_path = working_path;
    shell_command = build_shell_command("cd ", working_path, "; make run");
}
test_case_240_make::~test_case_240_make(){
}
//execute shell command
void test_case_240_make::execute(){
    system(shell_command.c_str());
}
//view files in a directory stream
//use :Ex when inside of a file to exit back to directory stream
void test_case_240_make::view_files(){
    std::string temp = build_shell_command("cd ", working_path, "; vim .");
    system(temp.c_str());
}