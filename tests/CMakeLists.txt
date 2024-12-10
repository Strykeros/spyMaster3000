if(BUILD_TESTING)
  add_executable(singleBlock.test singleBlock.test.cpp)
  target_link_libraries(singleBlock.test PRIVATE GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(singleBlock.test)
endif()
