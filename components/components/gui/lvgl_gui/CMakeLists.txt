
file(GLOB_RECURSE srcs lvgl/src/*.c)

list(APPEND srcs "lvgl_gui.c")

set(incdirs "."
            "lvgl"
            "include"
            "lvgl/src")
idf_component_register(SRCS "${srcs}"
                        INCLUDE_DIRS "${incdirs}"
                        REQUIRES screen touch_panel esp_timer)

target_compile_definitions(${COMPONENT_LIB} INTERFACE LV_CONF_INCLUDE_SIMPLE=1)
