cmake_minimum_required(VERSION 3.0)
project(receiver)
set(CMAKE_CXX_STANDARD 17)


add_library(Receiver-v1 SHARED
include/main.h
ext_work.h
multiword_types.h
receiver22a.h
receiver22a_private.h
receiver22a_types.h
rtGetInf.h
rtGetNaN.h
rt_logging.h
rtmodel.h
rt_nonfinite.h
rtw_continuous.h
rtw_solver.h
rtwtypes.h
tmwtypes.h
receiver22a.cpp
rtGetInf.cpp
rtGetNaN.cpp
rt_nonfinite.cpp
)

target_include_directories(Receiver-v1 PUBLIC include)


# target_link_libraries(YourExecutableName PUBLIC ${Boost_LIBRARIES}) # Замените Boost_LIBRARIES на имя вашей внешней библиотеки


