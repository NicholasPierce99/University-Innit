a.out: driver.o cpp_java_compiler.o file_manipulator.o test_case.o test_case_230.o test_case_240.o test_case_240_make.o test_case_240_no_make.o test_case_230_py.o test_case_builder.o
	g++ driver.o cpp_java_compiler.o file_manipulator.o test_case.o test_case_230.o test_case_240.o test_case_240_make.o test_case_240_no_make.o test_case_230_py.o test_case_builder.o -o a.out

driver.o: driver.cpp
	g++ -c driver.cpp -o driver.o -std=c++11

cpp_java_compiler.o: cpp_java_compiler.cpp
	g++ -c cpp_java_compiler.cpp -o cpp_java_compiler.o -std=c++11

file_manipulator.o: file_manipulator.cpp
	g++ -c file_manipulator.cpp -o file_manipulator.o -std=c++11

test_case.o: test_case.cpp
	g++ -c test_case.cpp -o test_case.o -std=c++11

test_case_230.o: test_case_230.cpp
	g++ -c test_case_230.cpp -o test_case_230.o -std=c++11

test_case_240.o: test_case_240.cpp
	g++ -c test_case_240.cpp -o test_case_240.o -std=c++11

test_case_240_make.o: test_case_240_make.cpp
	g++ -c test_case_240_make.cpp -o test_case_240_make.o -std=c++11
test_case_240_no_make.o: test_case_240_no_make.cpp
	g++ -c test_case_240_no_make.cpp -o test_case_240_no_make.o -std=c++11

test_case_230_py.o: test_case_230_py.cpp
	g++ -c test_case_230_py.cpp -o test_case_230_py.o -std=c++11

test_case_builder.o: test_case_builder.cpp
	g++ -c test_case_builder.cpp -o test_case_builder.o -std=c++11

run:
	./a.out
clean:	
	rm -f cpp_java_compiler.o driver.o file_manipulator.o test_case.o test_case_230.o test_case_240_make.o test_case_240_no_make.o test_case_230_py.o test_case_builder.o a.out