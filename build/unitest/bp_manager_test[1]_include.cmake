if(EXISTS "/Users/wangyunlai.wyl/Documents/project/miniob-ce/build/unitest/bp_manager_test[1]_tests.cmake")
  include("/Users/wangyunlai.wyl/Documents/project/miniob-ce/build/unitest/bp_manager_test[1]_tests.cmake")
else()
  add_test(bp_manager_test_NOT_BUILT bp_manager_test_NOT_BUILT)
endif()
