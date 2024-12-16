
# SPDX-License-Identifier: Apache-2.0 
# Copyright (c) 2024 nyashbox and Contributors

#
# enable address sanitizer for specific target
#
# arguments:
#    target - target, for which address sanitizer 
#    should be included
# 
# returns:
#    nothing
#
function(ukpm_target_enable_asan target)
    message(STATUS "[UKPM] Enabling address sanitizer for target: '${target}'")
    # compile options
    target_compile_options(${target} 
        PRIVATE 
            -fsanitize=address,undefined
            -fno-omit-frame-pointer)
    # link options
    target_link_libraries(${target} 
        PRIVATE 
            -fsanitize=address,undefined)
endfunction()
