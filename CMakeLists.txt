cmake_minimum_required(VERSION 3.8)


include_directories(.)
add_subdirectory(gtest)

add_library(counted counted.h counted.cpp fault_injection.h fault_injection.cpp)

add_executable(std mman.cpp mman-win32.h std.cpp set.h)
target_link_libraries(std counted gtest)


#add_executable(khala_vladislav khala_vladislav.cpp khala_vladislav.h)
#target_link_libraries(khala_vladislav counted gtest)

#add_executable(berlin_andrei berlin_andrei.cpp berlin_andrei.h)
#target_link_libraries(berlin_andrei counted gtest)

#add_executable(yurchenko_artem yurchenko_artem.cpp yurchenko_artem.h)
#target_link_libraries(yurchenko_artem counted gtest)

#add_executable(zhdan_egor zhdan_egor.cpp zhdan_egor.h)
#target_link_libraries(zhdan_egor counted gtest)

#add_executable(drozdova_aleksandra drozdova_aleksandra.cpp drozdova_aleksandra.h)
#target_link_libraries(drozdova_aleksandra counted gtest)

#add_executable(kozelko_sergei kozelko_sergei.cpp kozelko_sergei.h)
#target_link_libraries(kozelko_sergei counted gtest)

#add_executable(terentiev_mikhail terentiev_mikhail.cpp terentiev_mikhail.h)
#target_link_libraries(terentiev_mikhail counted gtest)

#add_executable(postnikova_anastasia postnikova_anastasia.cpp postnikova_anastasia.h)
#target_link_libraries(postnikova_anastasia gtest)

#add_executable(krivopaltsev_dmitriy krivopaltsev_dmitriy.cpp krivopaltsev_dmitriy.h)
#target_link_libraries(krivopaltsev_dmitriy counted gtest)

#add_executable(nisht_konstantin nisht_konstantin.cpp nisht_konstantin.h)
#target_link_libraries(nisht_konstantin counted gtest)

#add_executable(bezborodov_pavel bezborodov_pavel.cpp bezborodov_pavel.h)
#target_link_libraries(bezborodov_pavel counted gtest)

#add_executable(sorokin_ivan sorokin_ivan.cpp sorokin_ivan.h)
#target_link_libraries(sorokin_ivan counted gtest)
