if(BUILD_TESTING)
  add_executable(test_caeser test.cpp)
  target_link_libraries(test_caeser PRIVATE GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(test_caeser)
endif()
