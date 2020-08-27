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

    ListModel {
        id: logs
    }

    Controls1.SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        Rectangle {
            Layout.fillWidth: true

            RowLayout {
                anchors.centerIn: parent

                Button {
                    text: "List"
                    onClicked: FingerboardCppInterface.listFp()
                }
                Button {
                    text: "Enroll"
                    onClicked: FingerboardCppInterface.enrollFp()
                }
                Button {
                    text: "Delete"
                    onClicked: FingerboardCppInterface.deleteFp()
                }
                Button {
                    text: "Verify"
                    onClicked: FingerboardCppInterface.verifyFp()
                }
            }
        }

        ListView {
            id: logPane

            width: 700
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
    }

    Component.onCompleted: FingerboardCppInterface.init();
}
