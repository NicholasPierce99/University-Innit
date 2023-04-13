this project is an object oriented grader for 230/240 projects

in order to run this project, sample code has been given in folders labeled
    240_make, 240_no_make, and 230
    you must also have a working file transfer and terminal connection to tesla.cs.iupui.edu

running this project:
drag and drop the folder titled 450_code into tesla (file transfer winscp), change into this directory using cd 
run make clean if there are remaining .o files 
then proceed to run make 
this will compile the code as shown in the videos
now using a file transfer tool like winscp that the graders use for tesla:
    if the class is 230, simply drop in the .py files into the same directory as all of the cpp code
    if the class is 240, drop in the separate student named directories into the directory as all of the cpp code (not the sub-folders labeled base/blackbelt)
    (side note, we do this because unzipping is an expensive operation on tesla and the os unzippers are much faster, we've also pre-unzipped them to make running easier)
now simply run ./a.out while in the directory in the command line with all of the c++ code and you should be prompted for some options
    choose 230 if you dropped in 230 code
    choose 240 with base/blackbelt and make/no make:
        if no make, choose a .cpp to compile and .o to compile to
        
for 230, we're grading a simple knock knock joke assignment, just type a or some string for all of the responses, we see the output then open each file in vim
    to exit the vim, simply type ":wq" and if you accidentally go into insert mode, simply press escape then ":wq"
    some files don't interpret or may be stuck in an infinite loop that's ok!
        if a file doesn't interpret, we'll see why and if you're stuck in an infinite loop, just enter ctrl c like any other sub-process

for 240 without a make file, we're grading a simple functional horse race, just type in a seed for the race to start, we then see a view of all of the files in vim
    to begin, make sure you type the name of the filename horse.cpp and horse.o as the extension or the program doesn't know what to find!
    all of the students submissions are named horse.cpp so this is useful
    if a file needs more input, that's ok! it's running in a sub-process and you can enter what you like, or if it's in an infinite loop just hit ctrl c
    if it doesn't compile either, we will see it in the command line
    
for 240 with a make, we're grading an object oriented horse race, just type in a seed for the race to start, we then see a view of all of the files in vim
    to enter a file in the directory view, just hit enter and you can move through the file using the arrow keys, to exit back to the directory view, type ":Ex", to exit from directory view, type ":q"
    if a file needs more input from you, that's ok! it's running in a sub process and you can enter input as you'd like, or if it's stuck in an infinite loop, simply type ctrl c
    if it doesn't compile either, we will see it in the command line

*finally, there are tutorial videos included, good luck using the program!*