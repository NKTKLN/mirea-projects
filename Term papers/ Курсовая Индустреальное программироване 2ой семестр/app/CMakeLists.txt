cmake_minimum_required (VERSION 3.11)

# --- Dependencies -------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
  GIT_PROGRESS TRUE
  GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(ftxui)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)
# ------------------------------------------------------------------------------

project(factory-emulator
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(factory-emulator 
  src/main.cpp
  src/models.cpp
  src/models.h
  src/system.cpp
  src/system.h
  src/interface.cpp
  src/interface.h
  src/environment.h
)

target_include_directories(factory-emulator PRIVATE src)

target_compile_features(factory-emulator PRIVATE cxx_std_20)

target_link_libraries(factory-emulator
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE fmt::fmt
)
