cmake_minimum_required(VERSION 2.8)
project(slam-MapGen)

set(CMAKE_CXX_STANDARD 11)

# config logging (auto-generation for different release build)
MESSAGE("Generating logging_util.h for logging")
configure_file("src/util/logging/logging_util.h.in" "${CMAKE_SOURCE_DIR}/src/util/logging/logging_util.h")

# Eigen
find_package(Eigen3 REQUIRED)
include_directories(
        ${EIGEN3_INCLUDE_DIR}
)
# OpenCV
find_package( OpenCV REQUIRED)
# DBoW2
find_package( DBoW2 REQUIRED)
include_directories(${DBoW2_INCLUDE_DIRS})
find_package( DLib REQUIRED)
include_directories(${DLib_INCLUDE_DIRS})
# Pangolin
find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})
ADD_DEFINITIONS(-DPANGOLIN)


#PCL
find_package(PCL 1.2 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Ceres Solver
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})



# src
include_directories(src/common
        src/loop-closure
        src/util/config
        src/util/io
        src/util/logging
        src/tools
        src/visualization
        src/DBoW2-ext
        src/surface_recon
        third-party/ORB2_SLAM
        src/bundle-adjustment
        lib/soil/src
        )

#Simple OpenGL Image Library
file(GLOB soil_src lib/soil/src/*.c)
set(lib_src ${lib_src} ${soil_src})


# common
file(GLOB common_src src/common/*(.h|.cpp))
file(GLOB dow2_ext_src src/DBoW2-ext/*(.h|.cpp))
file(GLOB visualization_src src/visualization/*(.h|.cpp))
file(GLOB orb2_src third-party/ORB2_SLAM/*(.h|.cpp))
file(GLOB surface_recon_src src/surface_recon/*)
file(GLOB loop_detector_src src/loop-closure/*(.h|.cpp))
file(GLOB logging_src src/util/logging/*.cpp)
file(GLOB config_src src/util/config/*.cpp)
file(GLOB io_src src/util/io/*.cpp)

set(all_src ${common_src}
        ${dow2_ext_src}
        ${visualization_src}
        ${orb2_src}
        ${surface_recon_src}
        ${loop_detector_src}
        ${logging_src}
        ${config_src}
        ${io_src}
        ${lib_src}
        src/bundle-adjustment/bundle_ajustment.cpp
        )

## Loop-detector
#add_executable(loop_closing src/tests/loop_closing.cpp
#        ${loop_detector_src}
#        ${common_src}
#        ${dow2_ext_src}
#        ${logging_src}
#        ${config_src}
#        ${orb2_src}
#        ${io_src}
#        )
#target_link_libraries( loop_closing ${OpenCV_LIBS}
#        ${DBoW2_LIBS}
#        ${DLib_LIBS}
#        ${CERES_LIBRARIES}
#        )

# Vocabulary Converter
add_executable(voc_converter src/tools/VocabularyConverter.cpp ${logging_src} ${dow2_ext_src})
target_link_libraries(
        voc_converter
        ${OpenCV_LIBS}
        ${DBoW2_LIBS}
        ${DLib_LIBS}
        )

MESSAGE("logging_src: ${logging_src}")

#add_executable(view_test src/tests/view_test.cpp
#        ${common_src}
#        ${logging_src}
#        ${visualization_src})
#target_link_libraries(view_test ${OpenCV_LIBS}
#        ${Pangolin_LIBRARIES}
#        ${DBoW2_LIBS})
#
#add_executable(surface_recon src/tests/surface_recon.cpp
#        ${common_src}
#        ${logging_src}
#        ${config_src}
#        ${visualization_src}
#        ${surface_recon_src}
#        )
#target_link_libraries(surface_recon ${OpenCV_LIBS}
#        ${Pangolin_LIBRARIES}
#        ${DBoW2_LIBS}
#        ${PCL_LIBRARIES})

add_executable(map_generator src/map_generator.cpp
        ${all_src}
        )
target_link_libraries(map_generator
        ${OpenCV_LIBS}
        ${Pangolin_LIBRARIES}
        ${DBoW2_LIBS}
        ${DLib_LIBS}
        ${PCL_LIBRARIES}
        ${CERES_LIBRARIES}
        )

#message("all_src: ${all_src}")

## =================== playground ===================
#add_subdirectory(playground)