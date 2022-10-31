set(TESTPACKAGE common_tests)
project(${TESTPACKAGE} LANGUAGES CXX)
find_package(GTest CONFIG REQUIRED)

enable_testing()

include(GoogleTest)

add_executable(${TESTPACKAGE} StringToolsTest.cpp)

target_link_libraries(${TESTPACKAGE} 
	PRIVATE
		GTest::GTest 
		${PROJECT_NAMESPACE}::common
)

gtest_discover_tests(${TESTPACKAGE})