find_program (RE2C re2c
              PATHS /usr /usr/local /opt /opt/local $ENV{RE2C_DIR}
              PATH_SUFFIXES re2c/bin bin )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(RE2C DEFAULT_MSG RE2C)

mark_as_advanced(RE2C)

if(RE2C_FOUND)

else(RE2C_FOUND)
    message(FATAL_ERROR "re2c was not found.")
endif(RE2C_FOUND)
