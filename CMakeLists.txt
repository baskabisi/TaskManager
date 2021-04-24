cmake_minimum_required (VERSION 2.6)

project (TaskManager)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(TaskManager main.cpp TaskManager.cpp Task.cpp EvenCounter.cpp OddCounter.cpp)
target_link_libraries(TaskManager Threads::Threads)
