# This module defines:
#
# SDL2_IMAGE_INCLUDE_DIR
# SDL2_IMAGE_LIBRARY
# SDL2_IMAGE_FOUND
#

find_path(SDL2_IMAGE_INCLUDE_DIR NAMES SDL_image.h PATH_SUFFIXES SDL2)

find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SDL2_image REQUIRED_VARS SDL2_IMAGE_LIBRARY SDL2_IMAGE_INCLUDE_DIR)

mark_as_advanced(SDL2_IMAGE_INCLUDE_DIR SDL2_IMAGE_LIBRARY)
