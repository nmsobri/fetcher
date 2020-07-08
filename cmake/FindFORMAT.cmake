set(
        PATHS
        /usr
        /opt
        /usr/local
        /opt/local
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/fmt
)

set(
        LIBRARIES
        fmt
)

find_path(
        FORMAT_INCLUDE_DIRS fmt/format.h
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
        list(APPEND FORMAT_LIBRARIES ${${LIBRARY_COMPONENT}_LIB})
    endif ()

endforeach ()

#Handle arguements
include(FindPackageHandleStandardArgs)

#Make sure all the variable is being set, otherwise error out using DEFAULT_MSG
find_package_handle_standard_args(CURLP DEFAULT_MSG CURLP_INCLUDE_DIRS CURLP_LIBRARIES)

message("#################################")
message(STATUS ${FORMAT_INCLUDE_DIRS})
message(STATUS ${FORMAT_LIBRARIES})
message("#################################")