To run the code,
The code is written in c++ with no external custom libraries, so can be compiled simply using any g++ compiler, without ny need for makefile.
•	select the binary file for the project to run the program.
•	Compiled files for version1 and version2 are added in the submission folder for windows and linux for convenience.
•	To make variations in the parameters for program, following paramters can be found on respective line in the *.cpp file:

populationsize; GenerationNum; Xhigh; Yhigh; Mutationrate : code line 8 to 12

fitness function; line 53

•	To disable selection criteria, comment code lines 215 to 217
•	To enable dynamic windowing for selection of mutataion rate change dynamicwindow variable and set the value from 0.0 to 1.0 //uncomment the code with dynamic window comment to use, highly not recomended due to memory issues

**Memory allocation might cause some random runs to produce stray results(observed when run on Ubuntu 18.04), just follow the instructions to close the program before closing the window and the following runs should work fine.