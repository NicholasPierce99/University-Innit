#include "test_case_230_py.h"

//constructor for 230 py files
//create output dump file
//build shell command
test_case_230_py::test_case_230_py(std::string working_path){
    this->working_path = working_path;
    this->shell_command = build_shell_command("python ", this->working_path, "");
}
test_case_230_py::~test_case_230_py(){
}
//execute shell command
void test_case_230_py::execute(){
    try{
        system(shell_command.c_str());
    }
    catch(...){
        
    }
}
void test_case_230_py::create_output_file(){
    std::ofstream output("output.txt");
}
//run vim on the file for viewing
void test_case_230_py::view_files(){
    std::string temp = "vim ";
    temp.append(working_path);
    system(temp.c_str());
}
