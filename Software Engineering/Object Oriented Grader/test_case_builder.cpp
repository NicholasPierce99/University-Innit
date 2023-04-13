#include "test_case_builder.h"


//set class name, if it's a base or black belt, build file manipulator
test_case_builder::test_case_builder(std::string class_name, std::string base_black){
    this->class_name = class_name;
    this->base_black = base_black;
    fp = new file_manipulator();
}
//delete object pointers
test_case_builder::~test_case_builder(){
    delete tc;
    delete cjc;
}
//compiles and runs available files in all sub-directories
//for 240 cpp and java files
//runs all available files
//view all files in vim
void test_case_builder::build_execute_240_make_testcase(){
    result = fp->ls_output("-");
    for(auto x: result){
        path = x;
        path.append("/");
        path.append(base_black);

        std::cout << x << std::endl;
        cjc = new cpp_java_compiler(path, "; make");
        cjc->cd_compile();
        cjc->edit_permissions();
        tc = new test_case_240_make(path);
        tc->execute();

        //sleep for 10000000 milliseconds to give the grader time to look at output
        usleep(500000);

        tc->view_files();
    }
    remove_files(result);
}
//compiles and executes executable in all sub-folders
//needs a filename and a name for the executable
//view all files in vim
void test_case_builder::build_execute_240_no_make_testcase(std::string file_name, std::string executable){
    result = fp->ls_output("-");
    std::string composite_command = "; g++ ";
    composite_command.append(file_name);
    composite_command.append(" -o ");
    composite_command.append(executable);

    std::string exe = "; ./";
    exe.append(executable);

    for(auto x: result){
        path = x;
        path.append("/");
        path.append(base_black);

        std::cout << x << std::endl;
        cjc = new cpp_java_compiler(path, composite_command);
        cjc->cd_compile();
        cjc->edit_permissions();
        tc = new test_case_240_no_make(path, exe);
        tc->execute();

        //sleep for 10000000 milliseconds to give the grader time to look at output
        usleep(500000);
        tc->view_files();
    }
    remove_files(result);
}
//retrieve all files with .py extension
//populate vector
//build a test case of each file
//execute
//view file in vim
void test_case_builder::build_execute_230_testcase(){
    result = fp->ls_output(".py");
    for(auto x: result){
        path = x;
        std::cout << x << std::endl;

        tc = new test_case_230_py(path);
        tc->execute();

        //sleep for 10000000 milliseconds to give the grader time to look at output

        usleep(500000);
        tc->view_files();
    }
    remove_files(result);
}
//run rm -rf on files in result
void test_case_builder::remove_files(std::vector<std::string> result){
    std::string response;
    std::cout << "would you like to remove these files? Y | N" << std::endl;
    std::cin >> response;
    if(response.compare("Y") == 0){
        std::string remove_file;
        for(auto x: result){
            remove_file = "rm -rf ";
            remove_file.append(x);
            std::cout << remove_file << std::endl;
            system(remove_file.c_str());
        }
        std::cout << "files removed!" << std::endl;
    }
}
