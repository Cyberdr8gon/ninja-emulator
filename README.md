# ninja-emulator
###A GBA emulator in ANSI C.


##Development Installation
To easier aid the multiplatform development of this project, a specific project structure will be expected by the build system before it will compile the project.

####Prerequisites
Windows  
Be sure you have installed Visual Studio 2015 and CMake.  
Have downloaded a development distribution of SDL2 2.0.5.  
  
MacOS  
Be sure you have installed XCode and CMake.  
Again, download a development distrobution of SDL2 2.0.5  

Linux  
While this is supported as a build target, we do not support this as a development enviroment at this time.  
This can be quickly added if someone wants it, one just has to add some If statements to the CMakeLists.txt.  

First, place a development installation of SDL in
```
ext/SDL2.0.5
```
such that the include directory is at
```
ext/SDL2.0.5/include
```
Then, run
``` 
mkdir bin build
```
this should generate the required bin for output binaries and build for your build system/IDE  
Then, place the SDL2.dll (or SDL2.so) in the bin directory.  
THIS IS VERY IMPORTANT OR IT WILL FAIL TO RUN.  
ALSO be sure that same file is no longer inside SDL2_DIR/lib.  
Then
``` 
cd build
```
and run
```
cmake ..
```
This will generate your platforms default build files.

Then, you should be able open a project file with XCode/Visual Studio.

##Notes for developers

If you need to add a file do NOT add it inside your IDE. Create the file in the src/include/test/whatever directory and then run cmake .. again. This will refresh your IDE project config file.
