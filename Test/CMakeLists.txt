add_executable(AsterTest Main.cpp)
add_test(NAME AsterTest COMMAND Test)
target_link_libraries(AsterTest Aster)
add_custom_command(TARGET AsterTest POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Test/Assets $<TARGET_FILE_DIR:AsterTest>/Assets)