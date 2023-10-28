Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(SRC_LIST_TESTS ut.cpp)

add_executable(tests ${SRC_LIST_TESTS})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
# set_target_properties(tests PROPERTIES 
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)
