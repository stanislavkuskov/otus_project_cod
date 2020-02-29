cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(cod VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(cod VERSION 0.0.0)
endif()

find_package(OpenCV REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(cod main.cpp src/streamer.cpp src/streamer.h src/detector.cpp src/detector.h)

target_link_libraries(cod dlib)
target_link_libraries(cod openblas)

set_target_properties(cod PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

install(TARGETS cod RUNTIME DESTINATION bin)

target_link_libraries(cod ${OpenCV_LIBS})

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT kuskov.stanislav@gmail.com)

include(CPack)


