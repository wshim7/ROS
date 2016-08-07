cmake_minimum_required(VERSION 2.8.3)
project(roscir)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs sensor_msgs roslib cir_msgs cmake_modules)
find_package(TinyXML REQUIRED)

catkin_package(
  INCLUDE_DIRS src
  LIBRARIES roscir
  CATKIN_DEPENDS roscpp std_msgs sensor_msgs  cir_msgs
  DEPENDS TinyXML
)


MESSAGE("${TinyXML_INCLUDE_DIRS}")

add_definitions(-D__GNUC_)

include_directories(include ${catkin_INCLUDE_DIRS}
${catkin_INCLUDE_DIRS}
${PROJECT_SOURCE_DIR}/src
${TinyXML_INCLUDE_DIRS}
)

link_directories(${catkin_LIBRARY_DIRS})

##############################################################################
# Sources
##############################################################################

add_library(roscir 
	src/roscir/env/Config.cpp
	src/roscir/exception/ParseException.cpp
	src/roscir/exception/TimeoutException.cpp
	src/roscir/exception/ArrayOutOfBoundException.cpp
	src/roscir/exception/ConnectException.cpp
	src/roscir/exception/NullPointerException.cpp
	src/roscir/exception/IOException.cpp
	src/roscir/exception/FileNotFoundException.cpp
	src/roscir/exception/NoSuchElementException.cpp
	src/roscir/exception/NumberFormatException.cpp
	src/roscir/exception/Exception.cpp
	src/roscir/device/data/BatteryData.cpp
	src/roscir/device/data/PanTiltPosition.cpp
	src/roscir/device/data/PsdData.cpp
	src/roscir/device/data/RollBendPosition.cpp
	src/roscir/device/data/GyroData.cpp
	src/roscir/device/data/UltrasonicData.cpp
	src/roscir/device/data/WheelEncoderData.cpp
	src/roscir/device/data/ArmData.cpp
	src/roscir/device/data/TouchButtonData.cpp
	src/roscir/device/client/CHeadFaceClient.cpp
	#src/roscir/device/client/CRollBendClient.cpp
	#src/roscir/device/client/CBatteryClient.cpp
	#src/roscir/device/client/CTouchButtonClient.cpp
	src/roscir/device/client/CPsdClient.cpp
	src/roscir/device/client/CWheelClient.cpp
	src/roscir/device/client/DeviceClient.cpp
	src/roscir/device/client/CGyroClient.cpp
	src/roscir/device/client/CArmClient.cpp
	src/roscir/device/client/CPanTiltClient.cpp
	src/roscir/device/client/CLightEmittingDiodeClient.cpp
	src/roscir/device/client/CWheelEncoderClient.cpp
	src/roscir/device/client/CUltraClient.cpp
)
target_link_libraries(roscir ${catkin_LIBRARIES} ${TinyXML_LIBRARIES})

install(TARGETS roscir
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(DIRECTORY include/roscir/  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}  FILES_MATCHING PATTERN "*.h")
install(DIRECTORY src/roscir/  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}  FILES_MATCHING PATTERN "*.h")
install(DIRECTORY config  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION} )


add_executable(wheel_tester
	src/tests/wheel_tester.cpp
)
target_link_libraries(wheel_tester roscir ${catkin_LIBRARIES} 
)
install(TARGETS wheel_tester  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(arm_tester
	src/tests/arm_tester.cpp
)
target_link_libraries(arm_tester roscir ${catkin_LIBRARIES} 
)
install(TARGETS arm_tester  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

#add_executable(battery_tester
#	src/tests/battery_tester.cpp
#)
#target_link_libraries(battery_tester roscir ${catkin_LIBRARIES} 
#)
#install(TARGETS battery_tester  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(gyro_tester
	src/tests/gyro_tester.cpp
)
target_link_libraries(gyro_tester roscir ${catkin_LIBRARIES} 
)
install(TARGETS gyro_tester  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(led_tester
	src/tests/LedTester.cpp
)
target_link_libraries(led_tester roscir ${catkin_LIBRARIES} 
)
install(TARGETS led_tester  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(pantilt_tester
	src/tests/pantilt_tester.cpp
)
target_link_libraries(pantilt_tester roscir ${catkin_LIBRARIES} 
)
install(TARGETS pantilt_tester  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

#add_executable(touch_tester	src/tests/Touch_tester.cpp)
#target_link_libraries(touch_tester roscir ${catkin_LIBRARIES})
#install(TARGETS touch_tester  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(serial_tester
	src/tests/ofwriter.cpp
	src/tests/ofSerial.cpp
)
target_link_libraries(serial_tester roscir ${catkin_LIBRARIES} 
)
install(TARGETS serial_tester  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})