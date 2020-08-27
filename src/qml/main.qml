import QtQuick 2.15
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Fingerboard 1.0

ApplicationWindow {
    width: 1400
    height: 800
    title: "Fingerboard"
    visible: true

    property bool operationInProgress: false

    ListModel {
        id: logs
    }

    Controls1.SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        Rectangle {
            Layout.fillWidth: true

            RowLayout {
                id: operations
                visible: true
                anchors.centerIn: parent

                Button {
                    text: "List"
                    onClicked: {
                        operationInProgress = true;
                        FingerboardCppInterface.listFp();
                    }
                    enabled: !operationInProgress
                }
                Button {
                    text: "Enroll"
                    onClicked: {
                        operationInProgress = true;
                        operations.visible = false;
                        fingers.visible = true;
                    }
                    enabled: !operationInProgress
                }
                Button {
                    text: "Verify"
                    onClicked: {
                        operationInProgress = true;
                        FingerboardCppInterface.verifyFp();
                    }
                    enabled: !operationInProgress
                }
                Button {
                    text: "Delete"
                    onClicked: {
                        operationInProgress = true;
                        FingerboardCppInterface.deleteFp();
                    }
                    enabled: !operationInProgress
                }
            }

            ColumnLayout {
                id: fingers
                visible: false
                anchors.centerIn: parent

                RowLayout {
                    Button {
                        text: "Left Thumb"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("left-thumb");
                        }
                    }
                    Button {
                        text: "Left Index Finger"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("left-index-finger");
                        }
                    }
                }
                RowLayout {
                    Button {
                        text: "Left Middle Finger"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("left-middle-finger");
                        }
                    }
                    Button {
                        text: "Left Ring Finger"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("left-ring-finger");
                        }
                    }
                }
                RowLayout {
                    Button {
                        text: "Left Little Finger"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("left-little-finger");
                        }
                    }
                    Button {
                        text: "Right Thumb"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("right-thumb");
                        }
                    }
                }
                RowLayout {
                    Button {
                        text: "Right Index Finger"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("right-index-finger");
                        }
                    }
                    Button {
                        text: "Right Middle Finger"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("right-middle-finger");
                        }
                    }
                }
                RowLayout {
                    Button {
                        text: "Right Ring Finger"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("right-ring-finger");
                        }
                    }
                    Button {
                        text: "Right Little Finger"
                        Layout.minimumWidth: 150
                        onClicked: {
                            operations.visible = true;
                            fingers.visible = false;
                            FingerboardCppInterface.enrollFp("right-little-finger");
                        }
                    }
                }
            }
        }

        ListView {
            id: logPane

            width: 900
            clip: true
            interactive: true
            model: logs

            ScrollBar.vertical: ScrollBar { active: true; visible: true }

            delegate: Label {
                width: parent.width
                text: model.text
                font.family: 'monospace'
            }
        }
    }

    Connections {
        target: FingerboardCppInterface

        function onLog(msg) {
            logs.append({
                text: msg
            });
            logPane.positionViewAtEnd();
        }

        function onOperationComplete() {
            operationInProgress = false;
        }
    }

    Component.onCompleted: FingerboardCppInterface.init();
}
