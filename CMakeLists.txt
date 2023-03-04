# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS $ENV{IOT_SOLUTION_PATH}/components/usb/iot_usbh
                        $ENV{IOT_SOLUTION_PATH}/components/usb/iot_usbh_cdc
                        $ENV{IOT_SOLUTION_PATH}/components/usb/iot_usbh_modem
                        $ENV{IOT_SOLUTION_PATH}/components/led/led_indicator
                        )
include($ENV{IOT_SOLUTION_PATH}/component.cmake)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(usb_cdc_4g_module)