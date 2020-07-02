set(
        PATHS
        /usr
        /usr/local
        /opt
        /opt/local
        C:/Users/slier/Desktop/Devs/curl
        C:/Users/slier/Desktop/Devs/curlpp
)

set(
        LIBRARIES
        curlpp
        curl_imp
)

find_path(
        CURLP_INCLUDE_DIRS curlpp/cURLpp.hpp
        PATH_SUFFIXES include
        PATHS ${PATHS}
)

foreach (LIBRARY ${LIBRARIES})

    string(TOUPPER ${LIBRARY} LIBRARY_COMPONENT)

    find_library(
            ${LIBRARY_COMPONENT}_LIB ${LIBRARY}
            PATH_SUFFIXES lib
            PATHS ${PATHS}
    )

    if (${LIBRARY_COMPONENT}_LIB)
        list(APPEND CURLP_LIBRARIES ${${LIBRARY_COMPONENT}_LIB})
    endif ()

endforeach ()

#Handle arguements
include(FindPackageHandleStandardArgs)

#Make sure all the variable is being set, otherwise error out using DEFAULT_MSG
find_package_handle_standard_args(CURLP DEFAULT_MSG CURLP_INCLUDE_DIRS CURLP_LIBRARIES)

message("########################")
message(STATUS ${CURLP_INCLUDE_DIRS})
message(STATUS ${CURLP_LIBRARIES})
message("########################")