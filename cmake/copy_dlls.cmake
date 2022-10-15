include(CMakePrintHelpers)

LIST(APPEND pre_exclude_regexes "api-ms-.*") # windows API
LIST(APPEND pre_exclude_regexes "ext-ms-.*") # windows API
LIST(APPEND pre_exclude_regexes "ieshims.dll") # windows API
LIST(APPEND pre_exclude_regexes "emclient.dll") # windows API
LIST(APPEND pre_exclude_regexes "_app.dll") # windows API
LIST(APPEND pre_exclude_regexes "devicelockhelpers.dll") # windows API

LIST(APPEND post_exclude_regexes ".*Windows[\\/]system32.*") # windows system dlls
LIST(APPEND post_exclude_regexes "_app.dll") # windows API

file(GLOB_RECURSE dirs LIST_DIRECTORIES true "${DIR}/deps/*" "${DIR}/out/*")

file(GET_RUNTIME_DEPENDENCIES 
            DIRECTORIES ${dirs}
            RESOLVED_DEPENDENCIES_VAR deps
            EXECUTABLES ${FILE}
            PRE_EXCLUDE_REGEXES ${pre_exclude_regexes}
            POST_EXCLUDE_REGEXES ${post_exclude_regexes}
)

#message(${dirs})

foreach(_file ${deps})

message(${_file})

file(INSTALL
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
    TYPE SHARED_LIBRARY
    FILES "${_file}"
)
endforeach()