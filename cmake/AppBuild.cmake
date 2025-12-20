# 這是當此專案被作為 Root 專案時的設定
message(STATUS "EPD Lib: Building as Root Project")

# 包含 Library 建置設定
include(${CMAKE_CURRENT_LIST_DIR}/LibBuild.cmake)

# 加入範例程式
add_subdirectory(example)
