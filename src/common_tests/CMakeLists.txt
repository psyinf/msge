set(TESTPACKAGE common_tests)
project(${TESTPACKAGE} LANGUAGES CXX)
find_package(GTest CONFIG REQUIRED)

enable_testing()

include(GoogleTest)

add_executable(${TESTPACKAGE} StringToolsTest.cpp CommonTest.cpp)

target_link_libraries(${TESTPACKAGE} 
	PRIVATE
		GTest::gtest 
		GTest::gtest_main
		#GTest::gmock
		#GTest::gmock_main
		${PROJECT_NAMESPACE}::common
)

gtest_discover_tests(${TESTPACKAGE})
