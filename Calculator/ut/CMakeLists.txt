
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

include_directories(../plugins)

add_executable(tests test.cpp ../Parser.cpp ../Sorter.cpp ../Calculator.cpp)
target_link_libraries(tests PRIVATE 
    Catch2::Catch2WithMain)
