cmake_minimum_required(VERSION 3.0)
project(transmitter)
set(CMAKE_CXX_STANDARD 17)


add_library(Transmitter-v1 SHARED
include/main.h
ext_work.h
multiword_types.h
rt_logging.h
rtmodel.h
rtw_continuous.h
rtw_solver.h
rtwtypes.h
tmwtypes.h
transmitter22a.h
transmitter22a_private.h
transmitter22a_types.h
transmitter22a.cpp
)

target_include_directories(Transmitter-v1 PUBLIC include)


# target_link_libraries(YourExecutableName PUBLIC ${Boost_LIBRARIES}) # Замените Boost_LIBRARIES на имя вашей внешней библиотеки


