find_program(TREECC treecc
                PATHS /usr /usr/local /opt /opt/local $ENV{TREECC_DIR}
                PATH_SUFFIXES treecc/bin bin
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(TREECC DEFAULT_MSG TREECC)

mark_as_advanced(TREECC)

if(NOT TREECC_FOUND)
    message(FATAL_ERROR "treecc was not found.")
endif()