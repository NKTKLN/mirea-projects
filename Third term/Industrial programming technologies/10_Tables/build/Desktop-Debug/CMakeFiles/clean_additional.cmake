# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "10_Tables_autogen"
  "CMakeFiles/10_Tables_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/10_Tables_autogen.dir/ParseCache.txt"
  )
endif()
