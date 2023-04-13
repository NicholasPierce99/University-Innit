#ifndef TEST_CASE_240_MAKE
#define TEST_CASE_240_MAKE

#include "test_case_240.h"
class test_case_240_make: public test_case_240{
    private:
        
    public:
        test_case_240_make(std::string working_path);
        ~test_case_240_make();
        void view_files();
        void execute();
  
};

#endif