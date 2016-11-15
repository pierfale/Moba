project(moba_shared)

include(FindBoost)
find_package(Boost 1.58.0 REQUIRED signals)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE  source_files src/*)

add_library(${PROJECT_NAME} SHARED ${source_files})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
