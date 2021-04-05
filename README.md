# CNN-Compiler
This is a repository featuring research work I've done designing a compiler for cnn projetcs to be ran on architectures designed by my team

includes - custom header files you may need to create for the project 
bins - This folder contains any compiler binaries or helper binaries to be executed
src - This folder contains teh source code for the project

TODO's
  1.  The first version of the compiler is almost fully functional. There's an error where the the numebr of instructions in memory are being cut short or printed 
     improperly.
  2.  Working on the createion of Make files that can compiler and run the programs with ease rather than typing long commands each time we want to run or compile a     
     binary
     
 NOTES:
  The Programs written thus far are produced on Linux machines and compiled with gcc, may need to remote into a UNIX server if your device is MAC or WINDOWS
    I believe there is a way to cross-compile Linux commands for mac and windows however the libraries we use may not be compatible for those systems
  
  The command to use when compiling main.c as of right now is "gcc -o bin main.c -lgsl -lgslcbilas"
  
  If your recieve the following error: "gsl/gsl_linalg.h" 
    try this command which helped me resolve it: "apt install libgsl0-dev"
    may need to run as root for the correct results
