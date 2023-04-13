#include "test_case_240.h"

test_case_240::test_case_240(){
}
test_case_240::~test_case_240(){
}
std::string test_case_240::build_shell_command(std::string command_prefix, std::string working_path, std::string command_suffix){
    return command_prefix.append(working_path).append(command_suffix);
}