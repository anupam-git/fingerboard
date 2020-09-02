import QtQuick 2.15
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.0

import Fingerboard 1.0

ApplicationWindow {
    property bool showLogs: false
    property int selectedEnrollingFinger: -1

    id: appWindow
    minimumWidth: 1000
    minimumHeight: 800
    title: "Fingerboard"
    visible: true

    Material.theme: Material.Light
    Material.accent: Material.Blue

    Material.background: "#f5f5f5"

    Component.onCompleted: {
        FingerboardCppInterface.init();
    }

    Connections {
        target: AppState

        function onError(errorStatus, errorString) {
            var component = Qt.createComponent("ErrorDialog.qml");
            component.createObject(appWindow, { errorString: errorString });
        }
    }

    Menu {
        id: appMenu

        font.pixelSize: 12

        MenuItem {
            text: "Show Logs"
            checkable: true
            checked: showLogs

            Shortcut {
                sequence: "ctrl+l"
                onActivated: showLogs = !showLogs
            }

            onToggled: showLogs = !showLogs
        }

        MenuItem {
            text: "About"
            onTriggered: aboutDialog.open();
        }

        MenuItem {
            text: "Exit"
            onTriggered: Qt.quit();
        }
    }

    RoundButton {
        id: menuBtn

        width: 48
        height: 48
        flat: true
        icon.source: "qrc:/menu.svg"
        icon.color: Material.color(Material.Grey, Material.Shade700)
        icon.width: 18
        icon.height: 18
        hoverEnabled: true

        onClicked: {
            appMenu.popup(menuBtn.x + 5, menuBtn.y + menuBtn.height);
        }

        PointingHandOverlay {
            anchors.fill: parent
        }
    }

    Image {
        width: 24
        height: 24
        source: "qrc:/info.svg"
        anchors {
            right: parent.right
            top: menuBtn.top
            margins: 12
        }

        ColorOverlay {
            anchors.fill: parent
            source: parent
            color: Material.color(Material.Grey, Material.Shade700)
        }

        ToolTip.text: `<b>Device:</b> ${FingerboardCppInterface.deviceName}<br><b>Scan Type:</b> ${FingerboardCppInterface.scanType}<br><b>Enroll Stages:</b> ${FingerboardCppInterface.numEnrollStages}`

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onContainsMouseChanged: {
                parent.ToolTip.visible = containsMouse;
            }
        }
    }

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
            initialItem: initialView

            pushEnter: Transition {
                PropertyAnimation {
                    property: "x"
                    easing.type: appstack.easingType
                    from: appstack.width
                    to: 0
                    duration: appstack.animationDuration
                }
            }
            pushExit: Transition {
                PropertyAnimation {
                    property: "x"
                    easing.type: appstack.easingType
                    from: 0
                    to: -appstack.width
                    duration: appstack.animationDuration
                }
            }
            popEnter: Transition {
                PropertyAnimation {
                    property: "x"
                    easing.type: appstack.easingType
                    from: -appstack.width
                    to: 0
                    duration: appstack.animationDuration
                }
            }
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
        id: initialView

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
    AboutDialog {
        id: aboutDialog
    }
}

