import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Fingerboard 1.0

Rectangle {
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
            color: "#f5f5f5"

            RowLayout {
                anchors {
                    top: parent.top
                    left: parent.left
                    bottom: parent.bottom
                }

                Label {
                    text: "Log Level"
                    Layout.margins: 10
                    font.pixelSize: 12
                }

                ComboBox {
                    id: logLevelDropdown
                    currentIndex: 2
                    font.pixelSize: 12

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
                    delegate: ItemDelegate {
                        width: parent.width
                        text: model.text
                        font.pixelSize: 12
                    }

                    function selected() {
                        return logLevelModel.get(currentIndex);
                    }
                }

                CheckBox {
                    id: colorize

                    checked: true
                    font.pixelSize: 12
                    text: "Colorize"
                    Material.primary: Material.Blue
                }
            }

            Button {
                width: 50
                height: 50
                icon.name: "window-close"
                flat: true

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
                color: colorize.checked ? logPane.getColor(model.logLevel) : Material.color(Material.Grey, Material.Shade800);
                text: model.text
                font.family: 'monospace'
                height: shouldShow ? implicitHeight : 0
                visible: shouldShow
            }

            function getColor(logLevel) {
                switch (logLevel) {
                    case Logger.ERROR:
                        return Material.color(Material.Red);
                    case Logger.WARNING:
                        return Material.color(Material.Orange);
                    case Logger.INFO:
                        return Material.color(Material.Blue);
                    case Logger.DEBUG:
                        return Material.color(Material.Grey, Material.Shade800);
                    case Logger.VERBOSE:
                        return Material.color(Material.Grey);
                }
            }
        }
    }
}

