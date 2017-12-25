cmake_minimum_required(VERSION 3.8)
project(ex5)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(lib/googletest-release-1.8.0)

include_directories(lib/googletest-release-1.8.0/googletest/include)
include_directories(lib/googletest-release-1.8.0/googlemock/include)

set(TEST_FILES Tests/main.cpp Board.cpp Board.h Cell.cpp Cell.h DisplayGameOnConsole.cpp DisplayGameOnConsole.h HumanPlayer.cpp HumanPlayer.h GameLogic.cpp GameLogic.h Point.cpp Point.h HumanEnemyGameFlow.cpp HumanEnemyGameFlow.h DisplayGame.h Player.h AbstractGameLogic.h AIPlayer.cpp AIPlayer.h GameFlow.h AIEnemyGameFlow.cpp AIEnemyGameFlow.h Tests/GameLogicTest.cpp Tests/GameLogicTest.h Tests/HumanEnemyGameFlowTest.cpp Tests/HumanEnemyGameFlowTest.h Tests/AIEnemyGameFlowTest.cpp Tests/AIEnemyGameFlowTest.h Tests/AIPlayerTest.cpp Tests/AIPlayerTest.h)
set(SOURCE_FILES main.cpp Board.cpp Board.h Cell.cpp Cell.h DisplayGameOnConsole.cpp DisplayGameOnConsole.h HumanPlayer.cpp HumanPlayer.h GameLogic.cpp GameLogic.h Point.cpp Point.h HumanEnemyGameFlow.cpp HumanEnemyGameFlow.h DisplayGame.h Player.h AbstractGameLogic.h AIPlayer.cpp AIPlayer.h GameFlow.h AIEnemyGameFlow.cpp AIEnemyGameFlow.h RemotePlayer.cpp RemotePlayer.h RemoteEnemyGameFlow.cpp RemoteEnemyGameFlow.h)

add_executable(ex5.out ${SOURCE_FILES})
add_executable(test_main ${TEST_FILES})

target_link_libraries(ex5.out gtest gtest_main)
target_link_libraries(test_main gtest gtest_main)