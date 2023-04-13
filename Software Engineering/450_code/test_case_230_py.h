#ifndef TEST_CASE_230_PY
#define TEST_CASE_230_PY

#include "test_case_230.h"
class test_case_230_py: public test_case_230{
    private:
        
    public:
        test_case_230_py(std::string working_path);
        ~test_case_230_py();
        void view_files();
        void execute();
        void create_output_file();
};

#endif