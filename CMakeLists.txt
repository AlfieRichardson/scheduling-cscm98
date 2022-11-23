cmake_minimum_required(VERSION 3.23)
project(scheduling_cscm98)

set(CMAKE_CXX_STANDARD 14)

include_directories(cw-scheduling-processes)

add_executable(scheduling_cscm98
        "cw-scheduling-processes/CW Scheduling Processes.cpp"
        cw-scheduling-processes/Parameters.h
        cw-scheduling-processes/Processor.cpp
        cw-scheduling-processes/Processor.h
        cw-scheduling-processes/Scheduler.cpp
        cw-scheduling-processes/Scheduler.h
        cw-scheduling-processes/Task.cpp
        cw-scheduling-processes/Task.h)
