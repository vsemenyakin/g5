CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(G5)
add_executable(CArray
	main.cpp
	carray/CArray.hpp
	carray/CArrayImpl.inl
	utils/ToString.hpp
	utils/ToString.cpp
	test/IntTest.hpp
	test/IntTest.cpp
	test/StringTest.hpp
	test/StringTest.cpp
	test/utils/TestUtils.hpp)
