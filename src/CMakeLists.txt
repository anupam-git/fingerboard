set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(
  FINGERBOARD_SRCS

  main.cpp

  interfaces/fingerboard_cpp_interface.cpp

  utils/logger.cpp
)

set(
  FINGERBOARD_QML

  qml/qml.qrc
)

add_executable(
  ${PROJECT_NAME}

  ${FINGERBOARD_QML}
  ${FINGERBOARD_SRCS}
)
target_link_libraries(    
  ${PROJECT_NAME}
  PRIVATE

  Qt5::Core
  Qt5::Qml
  Qt5::Quick
)
