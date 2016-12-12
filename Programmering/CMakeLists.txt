cmake_minimum_required(VERSION 3.4)
project(Projekt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Sound/sound.h Sound/sound.cpp TextHandler/TextHandler.h TextHandler/TextHandler.cpp Frame/Frame/Frame.cpp Frame/Frame/Frame.h DFT/DFT.cpp DFT/DFT.h CustomRecorder/CustomRecorder.cpp CustomRecorder/CustomRecorder.h DtmfFinder/DtmfFinder.cpp DtmfFinder/DtmfFinder.h CSMAca/CSMAca/csmaCA.cpp CSMAca/CSMAca/csmaCA.h)
add_executable(Projekt ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Projekt ${SFML_LIBRARIES})
endif()