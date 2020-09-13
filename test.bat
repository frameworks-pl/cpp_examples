IF "" == "%DEVENVDIR%" CALL "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
IF "" == "%1" GOTO no_param   
cl /EHsc /I../src /I.. /I../include /I../include/gtest gtest.cc gtest_main.cc gtest-death-test.cc gtest-filepath.cc gtest-matchers.cc gtest-port.cc gtest-printers.cc gtest-test-part.cc gtest-typed-test.cc ..\%1\%1.cpp
gtest.exe
GOTO end
:no_param
@ECHO Please provide name of the file to run
:end