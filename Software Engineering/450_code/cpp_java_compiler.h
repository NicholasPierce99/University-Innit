#ifndef CPP_JAVA_COMPILER 
#define CPP_JAVA_COMPILER

#include <stdlib.h>
#include "subprocess.hpp"
#include <sys/types.h> 
#include <unistd.h> 

//compiler object for c++ and java
//cd to current directory
//run make on current directory
//run make run
class cpp_java_compiler{
	private:
		std::string working_path;
		std::string shell_command;
	
	public:
		cpp_java_compiler(std::string working_path, std::string suffix);
		~cpp_java_compiler();
		
		//run cd and compile on sub folder
		void cd_compile();

		//edit permissions on a folder
		void edit_permissions();
		//aseemble shell command
		void build_shell_command(std::string suffix);

		//return current working path
		std::string get_working_path();
};

#endif