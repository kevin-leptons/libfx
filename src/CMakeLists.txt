file(GLOB LIBFX_ERROR_SRC_FILES fx_error/*.c)
add_library(fx_error SHARED ${LIBFX_ERROR_SRC_FILES})

file(GLOB LIBFX_TEST_SRC_FILES fx_test/*.c)
add_library(fx_test SHARED ${LIBFX_TEST_SRC_FILES})
target_link_libraries(fx_test fx_error)

file(GLOB LIBFX_ADT_SRC_FILES fx_adt/*.c)
add_library(fx_adt SHARED ${LIBFX_ADT_SRC_FILES})
target_link_libraries(fx_adt fx_error)

file(GLOB LIB_SRC_FILES fx/*.c)
add_library(fx SHARED ${LIB_SRC_FILES})
target_link_libraries(fx fx_error)

file(GLOB TEST_SRC_FILES test/*.c)
add_executable(run_test ${TEST_SRC_FILES})
target_link_libraries(run_test fx_test fx)

install(TARGETS fx DESTINATION /usr/lib)
