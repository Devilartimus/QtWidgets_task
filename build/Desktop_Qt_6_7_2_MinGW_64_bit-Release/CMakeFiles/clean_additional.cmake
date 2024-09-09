# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Touchstone_Task_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Touchstone_Task_autogen.dir\\ParseCache.txt"
  "Touchstone_Task_autogen"
  )
endif()
