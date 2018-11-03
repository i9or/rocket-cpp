# This module defines:
#
# SDL2_INCLUDE_DIR
# SDL2_LIBRARY
# SDL2_FOUND
#

find_path(SDL2_INCLUDE_DIR NAMES SDL.h PATH_SUFFIXES SDL2)

find_library(SDL2_LIBRARY NAMES SDL2)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2 REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR)

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)
