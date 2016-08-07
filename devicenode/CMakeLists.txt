cmake_minimum_required(VERSION 2.8.3)
project(devicenode)

##############################################################################
# Catkin
##############################################################################

find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs std_msgs roscir cir_msgs cmake_modules tf)
find_package(TinyXML REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES devicenode
  CATKIN_DEPENDS roscpp sensor_msgs std_msgs roscir tf
)

add_definitions(-DROS_BUILD_SHARED_LIBS=1)

include_directories(include ${catkin_INCLUDE_DIRS}
${TinyXML_INCLUDE_DIRS}
${PROJECT_SOURCE_DIR}/src
)

link_directories(${catkin_LIBRARY_DIRS} 
)

##############################################################################
# Sources
##############################################################################

add_executable(devicenode 
	src/reactive/erobot/session/EBatteryCore.cpp
	src/reactive/erobot/session/EUltraCore.cpp
	src/reactive/erobot/session/EArmCore.cpp
	src/reactive/erobot/session/ETouchCore.cpp
	src/reactive/erobot/session/EWheelCore.cpp
	src/reactive/erobot/session/EGyroCore.cpp
	src/reactive/erobot/session/EWheelEncoderCore.cpp
	src/reactive/erobot/session/EPantiltCore.cpp
	src/reactive/erobot/session/ELEDCore.cpp
	src/reactive/erobot/session/ERobotSerialConnector.cpp
	src/reactive/erobot/session/EPSDCore.cpp
	src/reactive/erobot/ERobotCore.cpp
	src/reactive/erobot/utility/ERobotFunctionFactory.cpp
	src/reactive/mero/driver/RS232.cpp
	src/reactive/mero/driver/MeroNeckDriver.cpp
	src/reactive/mero/driver/MeroFaceDriver.cpp
	src/reactive/mero/driver/MeroLEDDriver.cpp
	src/reactive/mero/driver/MeroTouchDriver.cpp
	src/reactive/mero/driver/MeroLEDTouchConnector.cpp
	src/reactive/mero/utility/MeroFunctionFactory.cpp
	src/reactive/fri/rs232ch0/NeckRS232.cpp
	src/reactive/fri/rs232ch0/HeadFaceRS232.cpp
	src/reactive/fri/rs232ch0/FRI_RS232.cpp
	src/device/odif/wheel/WheelERobot.cpp
	src/device/odif/wheel/WheelServer.cpp
	src/device/odif/wheel/WheelServerMock.cpp
	src/device/odif/pantilt/PanTiltServer.cpp
	src/device/odif/pantilt/PanTiltERobot.cpp
	src/device/odif/pantilt/PanTiltServerMock.cpp
	src/device/odif/pantilt/PanTiltMero.cpp
	src/device/odif/pantilt/CPanTiltFRIRTAI.cpp
	src/device/odif/rollbend/RollBendSeverMock.cpp
	src/device/odif/rollbend/RollBendServer.cpp
	src/device/odif/rollbend/RollBendMero.cpp
	src/device/odif/rollbend/CRollBendFRIRTAI.cpp
	src/device/odif/headface/HeadFaceServer.cpp
	src/device/odif/headface/HeadFaceMPAvatar.cpp
	src/device/odif/headface/HeadFaceMero.cpp
	src/device/odif/headface/HeadFaceServerMock.cpp
	src/device/odif/headface/HeadFaceFRI.cpp
	src/device/odif/arm/ArmERobot.cpp
	src/device/odif/arm/ArmServer.cpp
	src/device/odif/arm/ArmServerMock.cpp
	src/device/odif/led/LEDERobot.cpp
	src/device/odif/led/LEDMero.cpp
	src/device/odif/led/LEDServer.cpp
	src/device/odif/led/LEDSeverMock.cpp
	src/device/server/handler/BatteryHandler.cpp
	src/device/server/handler/WheelHandler.cpp
	src/device/server/handler/GyroHandler.cpp
	src/device/server/handler/WheelEncoderHandler.cpp
	src/device/server/handler/PantiltHandler.cpp
	src/device/server/handler/TouchHandler.cpp
	src/device/server/handler/UltrasonicHandler.cpp
	src/device/server/handler/ArmHandler.cpp
	src/device/server/handler/PSDHandler.cpp
	src/device/server/handler/LEDHandler.cpp
	src/device/server/handler/RollBendHandler.cpp
	src/device/server/handler/HeadFaceHandler.cpp
	src/device/server/HandlerPool.cpp
	src/device/server/DeviceServer.cpp
	src/device/idif/battery/BatteryServer.cpp
	src/device/idif/battery/BatteryMock.cpp
	src/device/idif/battery/BatteryERobot.cpp
	src/device/idif/psd/PsdMock.cpp
	src/device/idif/psd/PsdServer.cpp
	src/device/idif/psd/PsdERobot.cpp
	src/device/idif/psd/PsdERobotSimul.cpp
	src/device/idif/touch/TouchButtonServer.cpp
	src/device/idif/touch/TouchButtonERobot.cpp
	src/device/idif/touch/TouchButtonMero.cpp
	src/device/idif/touch/TouchButtonMock.cpp
	src/device/idif/ultrasonic/UltrasonicERobotSimul.cpp
	src/device/idif/ultrasonic/UltrasonicServer.cpp
	src/device/idif/ultrasonic/UltrasonicMock.cpp
	src/device/idif/ultrasonic/UltrasonicERobot.cpp
	src/device/idif/gyro/GyroMock.cpp
	src/device/idif/gyro/GyroERobotSimul.cpp
	src/device/idif/gyro/GyroServer.cpp
	src/device/idif/gyro/GyroERobot.cpp
	src/device/idif/wheelencoder/WheelEncoderERobotSimul.cpp
	src/device/idif/wheelencoder/WheelEncoderMock.cpp
	src/device/idif/wheelencoder/WheelEncoderERobot.cpp
	src/device/idif/wheelencoder/WheelEncoderServer.cpp
	src/reactive/util/motorlimit/RobotConfig.cpp
	src/reactive/util/motorlimit/XmlSettings.cpp
)
target_link_libraries(devicenode ${catkin_LIBRARIES} 
)
install(TARGETS devicenode  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
install(DIRECTORY config  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION} )

