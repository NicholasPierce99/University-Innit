#include "file_manipulator.h"
/*algorithm for retrieving data from subprocess
1. open subprocess
2. create string stream buffer
3. use std out rd buffer to create string stream
4. read content from ss into string variable
5. check stream files, populate vector
*/

//constructor
//creates subprocess and reads contents of it into string 
file_manipulator::file_manipulator(){
    //open subprocess
    subprocess::popen cmd("ls", {"-p"});
    buffer << cmd.stdout().rdbuf() << std::endl;
    directory_files = buffer.str();
}
file_manipulator::~file_manipulator(){

}
//returns a vector of ls filenames 
std::vector<std::string> file_manipulator::ls_output(std::string ext){
    //opens string stream of the ls output
    std::stringstream ss(directory_files);

    //check if strings we're looking for are in the stream
    while(ss >> directory){
        if(directory.find(ext) != std::string::npos){
            sub_directories.push_back(directory);
        }
    }
    return sub_directories;
}
//returns a vector of ls filenames
std::vector<std::string> file_manipulator::ls_output(std::string ext1, std::string ext2){
    //opens string stream of the ls output
    std::stringstream ss(directory_files);

    //check if strings we're looking for are in the stream
    while(ss >> directory){
        if(directory.find(ext1) != std::string::npos || directory.find(ext2) != std::string::npos){
            sub_directories.push_back(directory);
        }
    }
    return sub_directories;
}