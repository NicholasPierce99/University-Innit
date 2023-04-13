#ifndef TEST_CASE_240_NO_MAKE
#define TEST_CASE_240_NO_MAKE

#include "test_case_240.h"
class test_case_240_no_make: public test_case_240{
    private:

    public:
        test_case_240_no_make(std::string working_path, std::string executable);
        ~test_case_240_no_make();
        void view_files();
        void execute();
};

#endif