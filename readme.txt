
"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"

cl /EHsc /I../src /I.. /I../include /I../include/gtest gtest.cc gtest_main.cc gtest-death-test.cc gtest-filepath.cc gtest-matchers.cc gtest-port.cc gtest-printers.cc gtest-test-part.cc gtest-typed-test.cc ..\findpairs\findpairs.cpp