import QtQuick 2.15
import QtQuick.Controls 1.4 as Controls1
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Fingerboard 1.0

Controls1.ApplicationWindow {
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
        FingerboardCppInterface.init();
    }

    Controls1.SplitView {
        anchors.fill: parent
        orientation: Qt.Vertical

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true            
        }

        LogPanel {
            visible: showLogs

            Layout.fillWidth: true
            height: 300
        }
    }
}
