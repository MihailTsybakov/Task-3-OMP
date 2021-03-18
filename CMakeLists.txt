cmake_minimum_required(VERSION 3.1)

project(Task_3_Sem_4)

include_directories(${PROJECT_SOURCE_DIR})

set(TASK_3_SRC main.cpp Create.cpp CIntN.cpp Autotest.cpp exceptions.cpp CIntN_hori.cpp CIntN_vert.cpp Factory.cpp)
set(TASK_3_HDR CIntN.h Create.h Autotest.h Timer.h CIntN_vert.h CIntN_hori.h Factory.h)

add_executable(${PROJECT_NAME} ${TASK_3_SRC} ${TASK_3_HDR})