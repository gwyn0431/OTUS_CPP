cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(IPFilter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(IPFilter VERSION 0.0.1)
endif()

# # Download and unpack googletest at configure time
# configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
# execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#   RESULT_VARIABLE result
#   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
# if(result)
#   message(FATAL_ERROR "CMake step for googletest failed: ${result}")
# endif()
# execute_process(COMMAND ${CMAKE_COMMAND} --build .
#   RESULT_VARIABLE result
#   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
# if(result)
#   message(FATAL_ERROR "Build step for googletest failed: ${result}")
# endif()

# # Prevent overriding the parent project's compiler/linker
# # settings on Windows
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# # Add googletest directly to our build. This defines
# # the gtest and gtest_main targets.
# add_subdirectory(
#     ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
#     ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
#     EXCLUDE_FROM_ALL)

# #configure_file(ProjectVersion.h.in ProjectVersion.h)

add_executable(ip_filter Main.cpp)
add_library(IPList IPList.cpp)
add_library(IPPool IPPool.cpp)


target_link_libraries(IPPool IPList)
target_link_libraries(ip_filter IPPool)
#add_executable(GTestProjectVersion GTestProjectVersion.cpp)

set_target_properties(ip_filter IPList IPPool PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

#target_include_directories(GTestProjectVersion PRIVATE "${CMAKE_BINARY_DIR}")

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /WX
    )
    target_compile_options(IPList PRIVATE
        /WX
    )
    target_compile_options(IPPool PRIVATE
        /WX
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(IPList PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(IPPool PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT gwyn0431@gmail.com)

include(CPack)

enable_testing()
#add_test(GTestProjectVersion GTestProjectVersion)