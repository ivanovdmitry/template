This is template C++11 project.

#Compilation
To compile on Windows (MinGW) apply patch gtest_windows_mingw_patch.diff to 3party/googletest.

#Note:
if cmake throw: 
```
Could not find a package configuration file provided by "Qt5OpenGL" with any of the following names:
    Qt5OpenGLConfig.cmake
    qt5opengl-config.cmake
```

try to install:
```
$ apt-get install libqt5opengl5-dev
```
