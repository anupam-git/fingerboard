import QtQuick 2.15
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Styles 1.4

import Fingerboard 1.0

ApplicationWindow {
    width: 1400
    height: 800
    title: "Fingerboard"
    visible: true
    background: Rectangle {
        color: "#c2c2c2"
    }

    property bool operationInProgress: false

    Component.onCompleted: {
        // AppState.state === AppState.INIT
        FingerboardCppInterface.init();
    }

    Connections {
        target: FingerboardCppInterface

        function onLog(msg) {
            logsModel.append({
                text: msg
            });
            logPane.positionViewAtEnd();
        }

        function onOperationComplete() {
            operationInProgress = false;
        }
    }

    ListModel {
        id: logsModel
    }

    Item {
        id: root

        states: [
            State {
                when: AppState.state === AppState.INIT
                PropertyChanges {
                    target: operations
                    visible: false
                }
            },
            State {
                name: AppState.state === AppState.IDLE
                PropertyChanges {
                    target: operations
                    visible: true
                }
            },
            State {
                name: AppState.state === AppState.ERROR
            },
            State {
                name: AppState.state === AppState.ENROLLING
            },
            State {
                name: AppState.state === AppState.VERIFYING
            },
            State {
                name: AppState.state === AppState.DELETING
            }
        ]
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
            model: logsModel

            ScrollBar.vertical: ScrollBar { active: true; visible: true }

            delegate: Label {
                width: parent.width
                text: model.text
                font.family: 'monospace'
            }
        }
    }
}
