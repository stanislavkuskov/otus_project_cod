cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(cod VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(cod VERSION 0.0.0)
endif()

project(cod)

#find_package(OpenCV REQUIRED)

add_executable(cod main.cpp)

set_target_properties(cod PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

#target_link_libraries(cod ${OpenCV_LIBS})

install(TARGETS cod RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT kuskov.stanislav@gmail.com)

include(CPack)