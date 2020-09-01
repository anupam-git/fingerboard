import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.0

import Fingerboard 1.0

Rectangle {
    width: 600
    height: 700

    ColumnLayout {
        width: parent.width

        Item {
            width: 200
            height: width
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 75

            CircularProgressBar {
                lineWidth: 6
                value: 1.0
                size: parent.width
                secondaryColor: "#e0e0e0"
                primaryColor: Material.color(Material.Red)
            }

            Image {
                width: 100
                height: 100
                source: "qrc:/fingerprint.svg"
                smooth: true
                anchors.centerIn: parent

                ColorOverlay {
                    anchors.fill: parent
                    source: parent
                    color: Material.color(Material.Red, Material.Shade500)
                }
            }
        }

        Label {
            visible: false
            text: "Verifying"
            font.pixelSize: 30
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 32
            color: Material.color(Material.Grey, Material.Shade700)
        }

        Label {
            visible: false
            text: "Touch/Swipe your finger to Verify"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 128
            font.pixelSize: 12
            color: Material.color(Material.Grey, Material.Shade500)
        }

        Button {
            Layout.preferredWidth: 128
            Layout.preferredHeight: 45
            text: "<font color='white'>START</font>"
            font.pixelSize: 10
            font.bold: true
            hoverEnabled: true
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 128

            Material.elevation: 0
            Material.background: Material.Blue

            onClicked: {
                console.log("Start Verifying");
            }

            PointingHandOverlay {
                anchors.fill: parent
            }
        }
    }

    Button {
        flat: true
        icon.source: "qrc:/back.svg"
        icon.color: Material.color(Material.Grey, Material.Shade500)
        anchors {
            left: parent.left
            leftMargin: 16
            top: parent.top
            topMargin: 16
        }
        hoverEnabled: true

        onClicked: {
            appstack.pop();
        }

        PointingHandOverlay {
            anchors.fill: parent
        }
    }
}
