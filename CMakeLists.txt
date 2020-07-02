cmake_minimum_required(VERSION 3.16)

# If you were using built in find package module and cant modify the find package module,
# just append to search directory that will search by cmake
# Append directories to CMAKE_PREFIX_PATH to tell cmake to search for library on this additional path ( for built in find package module )
# https://stackoverflow.com/questions/25395880/cmake-set-default-search-path
#list(APPEND CMAKE_PREFIX_PATH "/tmp/test" "/another/library/path")


project(fetcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(CURLP REQUIRED)


add_executable(fetcher main.cpp)

# Example using hardcoded value

#set(LIBRARIES
#        "C:/Users/slier/Desktop/curlpp/lib/libcurlpp.a"
#        "C:/Users/slier/Desktop/Devs/curl/lib/libcurl_imp.lib")

#target_include_directories(Fetcher PRIVATE "C:/Users/slier/Desktop/curlpp/include")
#target_link_libraries(Fetcher PRIVATE ${LIBRARIES})

# Example using find_package ( variables )
target_include_directories(fetcher PRIVATE ${CURLP_INCLUDE_DIRS})
target_link_libraries(fetcher PRIVATE ${CURLP_LIBRARIES})