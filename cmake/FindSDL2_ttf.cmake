# This module defines:
#
# SDL2_TTF_INCLUDE_DIR
# SDL2_TTF_LIBRARY
# SDL2_TTF_FOUND
#

find_path(SDL2_TTF_INCLUDE_DIR NAMES SDL_ttf.h PATH_SUFFIXES SDL2)

find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2_ttf REQUIRED_VARS SDL2_TTF_LIBRARY SDL2_TTF_INCLUDE_DIR)

mark_as_advanced(SDL2_TTF_INCLUDE_DIR SDL2_TTF_LIBRARY)
