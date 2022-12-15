set(TESTPACKAGE core_tests)
project(${TESTPACKAGE} LANGUAGES CXX)
find_package(GTest CONFIG REQUIRED)

enable_testing()

include(GoogleTest)

add_executable(${TESTPACKAGE} FindVisitor.cpp)

target_link_libraries(${TESTPACKAGE} 
	PRIVATE
		GTest::gtest 
		GTest::gtest_main
		#GTest::gmock
		#GTest::gmock_main
		${PROJECT_NAMESPACE}::core
)

gtest_discover_tests(${TESTPACKAGE})
