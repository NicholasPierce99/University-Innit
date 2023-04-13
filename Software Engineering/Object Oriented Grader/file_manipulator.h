#ifndef FILE_MANIPULATOR
#define FILE_MANIPULATOR

#include <string>
#include <iostream>
#include <sstream>
#include "subprocess.hpp"

//ls file manipulator, captures output of ls
class file_manipulator{
    private:
        //string stream buffer to read output from subprocess
        std::stringstream buffer;
        std::string directory_files;
        std::string directory;
        std::vector<std::string> sub_directories;
        
    public:
        file_manipulator();
        ~file_manipulator();

        //ls output, returns vector of files (or directories)
        std::vector<std::string> ls_output(std::string ext);

        //ls output, returns vector of files (or directories)
        //overloaded argument to search for two specific directories
        std::vector<std::string> ls_output(std::string ext1, std::string ext2);
};

#endif