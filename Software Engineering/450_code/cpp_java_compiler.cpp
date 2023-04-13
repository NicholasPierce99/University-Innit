#include "cpp_java_compiler.h"

//constructor, sets working path and builds shell command
cpp_java_compiler::cpp_java_compiler(std::string working_path, std::string suffix){
    this->working_path = working_path;
    build_shell_command(suffix);
}
cpp_java_compiler::~cpp_java_compiler(){

}
//build shell command
void cpp_java_compiler::build_shell_command(std::string suffix){
    shell_command = "cd ";
    shell_command.append(working_path);
    shell_command.append(suffix);
}
//cd to the current working directory
//run make
void cpp_java_compiler::cd_compile(){
    system(shell_command.c_str());
}
//edit permissions to allow make run
void cpp_java_compiler::edit_permissions(){
    std::string permission = "chmod 755 -R ";
    permission.append(working_path);
    system(permission.c_str());
}
//return working directory
std::string cpp_java_compiler::get_working_path(){
    return working_path;
}