file(GLOB_RECURSE guider_ui_srcs LIST_DIRECTORIES false
     "${CMAKE_CURRENT_LIST_DIR}/ui/*.c")

set(srcs "main.c" "color_test.c" ${guider_ui_srcs})
set(include_dirs "." "ui" "ui/custom" "ui/generated")

idf_component_register(
    SRCS ${srcs}
    INCLUDE_DIRS ${include_dirs}
    REQUIRES driver espressif__button
)

# Optional: idf.py build -DAPP_ENABLE_COLOR_TEST=1
if(DEFINED APP_ENABLE_COLOR_TEST)
    target_compile_definitions(${COMPONENT_LIB} PRIVATE APP_ENABLE_COLOR_TEST=${APP_ENABLE_COLOR_TEST})
endif()
