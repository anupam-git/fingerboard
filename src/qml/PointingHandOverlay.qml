import QtQuick 2.0

MouseArea {
    cursorShape: Qt.PointingHandCursor
    propagateComposedEvents: true

    onClicked: mouse.accepted = false;
    onPressed: mouse.accepted = false;
    onReleased: mouse.accepted = false;
    onDoubleClicked: mouse.accepted = false;
    onPositionChanged: mouse.accepted = false;
    onPressAndHold: mouse.accepted = false;
}
