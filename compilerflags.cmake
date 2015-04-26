####################################################################################################
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
####################################################################################################
#
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -Wcast-align -Wcast-qual -Werror -Wextra \
-Wno-unused-parameter -Wshadow -Wwrite-strings -fno-common -fno-omit-frame-pointer \
-fno-optimize-sibling-calls -fno-strict-aliasing -fsigned-char -fstrict-overflow \
-Wno-ignored-qualifiers -Wno-array-bounds -Wno-empty-body"
) # SET CMAKE_C_FLAGS
#
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wcast-align -Wcast-qual -Werror -Wextra \
-Wnon-virtual-dtor -Wno-unused-parameter -Wshadow -Wwrite-strings -fno-omit-frame-pointer \
-fno-optimize-sibling-calls -fno-strict-aliasing -fsigned-char -fstrict-overflow \
-Wno-ignored-qualifiers -Wno-c++0x-compat -Wno-array-bounds -Wno-empty-body"
) # SET CMAKE_CXX_FLAGS
message("${CMAKE_CXX_FLAGS}")
