project(moba_server)

# Boost
include(FindBoost)
find_package(Boost 1.58.0 REQUIRED system thread)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

# MySQL
link_directories("${CMAKE_SOURCE_DIR}/lib/MySQL")
include_directories("${CMAKE_SOURCE_DIR}/lib/MySQL/include")

set(MOBA_SHARED_INCLUDE_PATH "../shared/src")
set(MOBA_SHARED_Lib_PATH "")
link_directories(${MOBA_SHARED_Lib_PATH})
include_directories(${MOBA_SHARED_INCLUDE_PATH})

file(GLOB_RECURSE  source_files src/*)

add_executable(${PROJECT_NAME} ${source_files})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} moba_shared)
target_link_libraries(${PROJECT_NAME} mysqlclient dl)

file(COPY ressources DESTINATION .)
file(COPY serv.conf DESTINATION .)
