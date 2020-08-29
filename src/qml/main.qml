import QtQuick 2.15
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Fingerboard 1.0

Controls1.ApplicationWindow {
    property bool operationInProgress: false
    property bool showLogs: false

    minimumWidth: 1600
    minimumHeight: 800
    title: "Fingerboard"
    visible: true
    menuBar: Controls1.MenuBar {
        Controls1.Menu {
            title: "&File"

            Controls1.MenuItem {
                text: "&Exit"
            }
        }
        Controls1.Menu {
            title: "&Tools"

            Controls1.MenuItem {
                text: "Show logs"
                checkable: true
                checked: showLogs
                shortcut: "Ctrl+L"
                onTriggered: {
                    showLogs = !showLogs;
                }
            }
        }
    }


    Component.onCompleted: {
        // AppState.state === AppState.INIT
        FingerboardCppInterface.init();
    }

    Connections {
        target: FingerboardCppInterface

        function onLog(logLevel, msg) {
            logsModel.append({
                logLevel: logLevel,
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

    Controls1.SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical

        Rectangle {
            Layout.fillHeight: true
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

        ColumnLayout {
            id: bottomPane
            visible: showLogs

            Layout.fillWidth: true
            height: 300

            Rectangle {
                Layout.fillWidth: true
                height: 50
                color: "#dfdfdf"

                RowLayout {
                    anchors {
                        top: parent.top
                        left: parent.left
                        bottom: parent.bottom
                    }

                    Label {
                        text: "Log Level"
                        Layout.margins: 10
                    }

                    ComboBox {
                        id: logLevelDropdown
                        Layout.fillHeight: true
                        Layout.margins: 10
                        currentIndex: 2

                        background: Rectangle {
                            color: "#fff"
                            implicitWidth: 150
                        }
                        model: ListModel {
                            id: logLevelModel

                            ListElement {
                                text: "ERROR"
                                level: Logger.ERROR
                            }
                            ListElement {
                                text: "WARNING"
                                level: Logger.WARNING
                            }
                            ListElement {
                                text: "INFO"
                                level: Logger.INFO
                            }
                            ListElement {
                                text: "DEBUG"
                                level: Logger.DEBUG
                            }
                            ListElement {
                                text: "VERBOSE"
                                level: Logger.VERBOSE
                            }
                        }
                        onCurrentIndexChanged: {
//                            console.log("Set log level to", logLevelModel.get(currentIndex).text);
                            logPane.forceLayout();
                        }
                        textRole: "text"

                        function selected() {
                            return logLevelModel.get(currentIndex);
                        }
                    }

                    CheckBox {
                        id: colorize

                        checked: true
                        text: "Colorize"
                    }
                }

                Button {
                    width: 50
                    height: 50
                    icon.name: "window-close"

                    anchors {
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }

                    onClicked: {
                        showLogs = false;
                    }
                }
            }

            ListView {
                id: logPane
                Layout.fillWidth: true
                Layout.fillHeight: true

                clip: true
                interactive: true
                model: logsModel

                ScrollBar.vertical: ScrollBar { active: true; visible: true }

                delegate: Label {
                    property bool shouldShow: model.logLevel <= logLevelDropdown.selected().level

                    width: parent.width
                    color: colorize.checked ? logPane.getColor(model.logLevel) : "black"
                    text: model.text
                    font.family: 'monospace'
                    height: shouldShow ? implicitHeight : 0
                    visible: shouldShow
                }

                function getColor(logLevel) {
                    switch (logLevel) {
                        case Logger.ERROR:
                            return "red";
                        case Logger.WARNING:
                            return "yellow";
                        case Logger.INFO:
                            return "blue";
                        case Logger.DEBUG:
                            return "black";
                        case Logger.VERBOSE:
                            return "grey";
                    }
                }
            }
        }
    }
}
