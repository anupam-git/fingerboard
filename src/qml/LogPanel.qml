import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Fingerboard 1.0

Item {
    Connections {
        target: FingerboardCppInterface

        function onLog(logLevel, msg) {
            logsModel.append({
                logLevel: logLevel,
                text: msg
            });
            logPane.positionViewAtEnd();
        }
    }

    ListModel {
        id: logsModel
    }

    ColumnLayout {
        anchors.fill: parent

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

