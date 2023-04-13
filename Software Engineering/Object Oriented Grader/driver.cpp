#include "test_case_builder.h"

//main method, creates builder based on class
int main (){
    std::string class_name;
    std::string base_black;
    std::string make;
    std::string file_name;
    std::string executable;

    std::cout << "is this grading session for 230 or 240?" << std::endl;
    std::cin >> class_name;
    if(class_name.compare("240") == 0){
        std::cout << "is this grading session for base or black belts?" << std::endl;
        std::cin >> base_black;

        std::cout << "does this project use make? Y | N" << std::endl;
        std::cin >> make;
        if(make.compare("N") == 0){
            std::cout << "enter the name of the file we're looking for" << std::endl;
            std::cin >> file_name;
            std::cout << "enter a name for the executable" << std::endl;
            std::cin >> executable;
        }
    }
    else{
        base_black = "";
    }
    test_case_builder * tcb = new test_case_builder(class_name, base_black);
    if(class_name.compare("240") == 0){
        if(make.compare("N") == 0){
            tcb->build_execute_240_no_make_testcase(file_name, executable);
        }
        else{
            tcb->build_execute_240_make_testcase();
        }
    }
    if(class_name.compare("230") == 0){
        tcb->build_execute_230_testcase();
    }


    delete tcb;
    return 0;
}