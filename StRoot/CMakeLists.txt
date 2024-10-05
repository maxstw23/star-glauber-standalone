cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(StGlauberStandalone)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net MathMore EG)
include(${ROOT_USE_FILE})
add_definitions(${ROOT_CXX_FLAGS})

add_subdirectory(StFastGlauberMcMaker)
add_subdirectory(StCentralityMaker)
add_subdirectory(StGlauberAnalysisMaker)
add_subdirectory(StGlauberTree)
add_subdirectory(StGlauberUtilities)

add_definitions(-D_VANILLA_ROOT_)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")
set(PROJECT_NAME STGLAUBERSTANDALONE)

set(STGLAUBERSTANDALONE_INCLUDE_DIRECTORIES
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/StFastGlauberMcMaker"
  "${CMAKE_CURRENT_SOURCE_DIR}/StCentralityMaker"
  "${CMAKE_CURRENT_SOURCE_DIR}/StGlauberAnalysisMaker"
  "${CMAKE_CURRENT_SOURCE_DIR}/StGlauberTree"
  "${CMAKE_CURRENT_SOURCE_DIR}/StGlauberUtilities"
  ${ROOT_INLCUDE_DIRS}
)

include_directories(${STGLAUBERSTANDALONE_INCLUDE_DIRECTORIES})

set(STGLAUBERSTANDALONE_INCLUDE_LIBRARIES
  StFastGlauberMcMaker
  StGlauberAnalysisMaker
  StCentralityMaker
  StGlauberTree
  StGlauberUtilities
  ${ROOT_LIBRARIES}
)

add_executable(addNcollVsNpart "${CMAKE_CURRENT_SOURCE_DIR}/../addNcollVsNpart.C")
target_link_libraries(addNcollVsNpart ${STGLAUBERSTANDALONE_INCLUDE_LIBRARIES})
add_executable(doFastGlauberMcMaker "${CMAKE_CURRENT_SOURCE_DIR}/../doFastGlauberMcMaker.C")
target_link_libraries(doFastGlauberMcMaker ${STGLAUBERSTANDALONE_INCLUDE_LIBRARIES})
add_executable(doAnalysisMaker "${CMAKE_CURRENT_SOURCE_DIR}/../doAnalysisMaker.C")
target_link_libraries(doAnalysisMaker ${STGLAUBERSTANDALONE_INCLUDE_LIBRARIES})
add_executable(doNbdFitMaker "${CMAKE_CURRENT_SOURCE_DIR}/../doNbdFitMaker.C")
target_link_libraries(doNbdFitMaker ${STGLAUBERSTANDALONE_INCLUDE_LIBRARIES})
add_executable(doPlotMaker "${CMAKE_CURRENT_SOURCE_DIR}/../doPlotMaker.C")
target_link_libraries(doPlotMaker ${STGLAUBERSTANDALONE_INCLUDE_LIBRARIES})
