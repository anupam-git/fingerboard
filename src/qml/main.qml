import QtQuick 2.15
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

import Fingerboard 1.0

Controls1.ApplicationWindow {
    property bool showLogs: false

    minimumWidth: 1000
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
        FingerboardCppInterface.init();
    }
    Material.theme: Material.Light
    Material.accent: Material.Blue

    Controls1.SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical

        StackView {
            property int animationDuration: 300
            property int easingType: Easing.InOutExpo

            id: appstack
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 32
            initialItem: listView
//            initialItem: enrollView

            // @disable-check M16
            pushEnter: Transition {
                PropertyAnimation {
                    property: "x"
                    easing.type: appstack.easingType
                    from: appstack.width
                    to: 0
                    duration: appstack.animationDuration
                }
            }
            // @disable-check M16
            pushExit: Transition {
                PropertyAnimation {
                    property: "x"
                    easing.type: appstack.easingType
                    from: 0
                    to: -appstack.width
                    duration: appstack.animationDuration
                }
            }
            // @disable-check M16
            popEnter: Transition {
                PropertyAnimation {
                    property: "x"
                    easing.type: appstack.easingType
                    from: -appstack.width
                    to: 0
                    duration: appstack.animationDuration
                }
            }
            // @disable-check M16
            popExit: Transition {
                PropertyAnimation {
                    property: "x"
                    easing.type: appstack.easingType
                    from: 0
                    to: appstack.width
                    duration: appstack.animationDuration
                }
            }
        }

        LogPanel {
            visible: showLogs

            Layout.fillWidth: true
            height: 300
        }
    }

    Component {
        id: listView

        Item {
            ListingView {
                anchors.horizontalCenter: parent.horizontalCenter
            }

            RoundButton {
                anchors {
                    right: parent.right
                    bottom: parent.bottom
                    margins: 16
                }
                hoverEnabled: true
                padding: 18

                Material.background: Material.Red
                icon.source: "qrc:/delete.svg"
                icon.color: "white"

                z: 10

                onClicked: {
                    deleteDialog.visible = true;
                }

                PointingHandOverlay {
                    anchors.fill: parent
                }
            }
        }
    }

    Component {
        id: enrollView

        Item {
            EnrollView {
                 anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Component {
        id: verifyView

        Item {
            VerifyView {
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    DeleteDialog {
        id: deleteDialog
    }
}

