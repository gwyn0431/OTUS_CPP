cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(GraphicsEditor VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(GraphicsEditor VERSION 0.0.1)
endif()

# Enable testing and adding gtest to project
enable_testing()
add_subdirectory(../googletest googletest)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../googletest/include)
include_directories(${CMAKE_CURRENT_LIST_DIR})

set(
    ImplementationFiles 
    "Main.cpp" 
	"Launch.cpp" 
    "Controllers/ControllersManager.cpp" 
    "Controllers/ProjectActionsController.cpp"
    "Editor/Editor.cpp"
	"Editor/EditorLoop.cpp"
	"Widgets/EditorUI.cpp"
	"Widgets/Framework/Button.cpp"
	"Widgets/Project/ProjectActionsPanel.cpp"
	"Projects/ProjectManager.cpp"
	"Misc/CommandLine.cpp"
)
add_executable(GraphicsEditor ${ImplementationFiles}) 

set_target_properties(GraphicsEditor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    # Those are needed so gtest won't conflict with proj files runtime library mode, when compiling
    # with MSVC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MTd")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

    target_compile_options(GraphicsEditor PRIVATE
        /W4
    )
else ()
    target_compile_options(GraphicsEditor PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS GraphicsEditor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT gwyn0431@gmail.com)

include(CPack)

# Doxygen setup
# find_package(Doxygen)
# set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in)
# set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxyfile.in)
# configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

# add_custom_target( GenerateDoxygenDocumentation
#     COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#     COMMENT "Generating doxygen documentation."
# )