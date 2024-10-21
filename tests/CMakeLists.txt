if(BUILD_TESTING)
  add_executable(test_caeser test_caeser.cpp)
  target_link_libraries(test_caeser PRIVATE GTest::gtest_main)

  add_executable(test_sha256 test_sha256.cpp)
  target_link_libraries(test_sha256 PRIVATE GTest::gtest_main)

  add_executable(test_playfair test_playfair.cpp)
  target_link_libraries(test_playfair PRIVATE GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(test_caeser)
endif()
