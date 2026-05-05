#
# Audacity: A Digital Audio Editor
#

# Cross-cutting C++ types and utilities that don't belong to any one feature
# module. Mirrors the role of muse_framework's `global` at the app level.

declare_module(shared)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/axis/axisscale.h
    ${CMAKE_CURRENT_LIST_DIR}/axis/numberscale.h
)

setup_module()
