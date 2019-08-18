#
# Copyright(c) 2018 The nanoFramework project contributors
# See LICENSE file in the project root for full license information.
#


#################################################################################################
# make sure that a valid path is set bellow                                                     #
# if this is for a class library it's OK to leave it as it is                                   #
# if this is an Interop module the path has to be set where the build can find the source files #
#################################################################################################

# native code directory
set(BASE_PATH_FOR_THIS_MODULE "${BASE_PATH_FOR_CLASS_LIBRARIES_MODULES}/nanoFramework.Hardware.Esp32.RMT.Tx")


# set include directories
list(APPEND nanoFramework.Hardware.Esp32.RMT.Tx_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Core")
list(APPEND nanoFramework.Hardware.Esp32.RMT.Tx_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/CLR/Include")
list(APPEND nanoFramework.Hardware.Esp32.RMT.Tx_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/HAL/Include")
list(APPEND nanoFramework.Hardware.Esp32.RMT.Tx_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/PAL/Include")
list(APPEND nanoFramework.Hardware.Esp32.RMT.Tx_INCLUDE_DIRS "${BASE_PATH_FOR_THIS_MODULE}")

# source files
set(nanoFramework.Hardware.Esp32.RMT.Tx_SRCS

    nanoFramework_Hardware_Esp32_RMT_Tx.cpp
    nanoFramework_Hardware_Esp32_RMT_Tx_nanoFramework_Hardware_Esp32_RMT_Tx_Transmitter_mshl.cpp
    nanoFramework_Hardware_Esp32_RMT_Tx_nanoFramework_Hardware_Esp32_RMT_Tx_Transmitter.cpp

)

foreach(SRC_FILE ${nanoFramework.Hardware.Esp32.RMT.Tx_SRCS})
    set(nanoFramework.Hardware.Esp32.RMT.Tx_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(nanoFramework.Hardware.Esp32.RMT.Tx_SRC_FILE ${SRC_FILE}
	    PATHS
	        "${BASE_PATH_FOR_THIS_MODULE}"
	        "${TARGET_BASE_LOCATION}"

	    CMAKE_FIND_ROOT_PATH_BOTH
    )
# message("${SRC_FILE} >> ${nanoFramework.Hardware.Esp32.RMT.Tx_SRC_FILE}") # debug helper
list(APPEND nanoFramework.Hardware.Esp32.RMT.Tx_SOURCES ${nanoFramework.Hardware.Esp32.RMT.Tx_SRC_FILE})
endforeach()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(nanoFramework.Hardware.Esp32.RMT.Tx DEFAULT_MSG nanoFramework.Hardware.Esp32.RMT.Tx_INCLUDE_DIRS nanoFramework.Hardware.Esp32.RMT.Tx_SOURCES)

