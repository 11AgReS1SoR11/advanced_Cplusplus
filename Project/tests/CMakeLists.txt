Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(SOURS ${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(SRC_LIST_TESTS ut.cpp)

add_executable(tests ${SRC_LIST_TESTS})

target_include_directories(tests PUBLIC ${SOURS})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
