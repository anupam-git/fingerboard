set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(
  FINGERBOARD_SRCS

  main.cpp

  interfaces/fingerboard_cpp_interface.cpp

  utils/logger.cpp
  utils/appstate.cpp
)

set(
  FINGERBOARD_QML

  qml/qml.qrc
  assets/assets.qrc
)

qt5_add_dbus_interfaces(
  FPRINTD_DBUS_INTERFACES

  fprintd-dbus-interface-xml/fprintddevice.xml
  fprintd-dbus-interface-xml/fprintdmanager.xml
)

add_executable(
  ${PROJECT_NAME}

  ${FINGERBOARD_QML}
  ${FINGERBOARD_SRCS}

  ${FPRINTD_DBUS_INTERFACES}
)
target_link_libraries(    
  ${PROJECT_NAME}
  PRIVATE

  Qt5::Core
  Qt5::Qml
  Qt5::Quick
  Qt5::DBus
  Qt5::QuickControls2
)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
