import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.0

import Fingerboard 1.0

Rectangle {
    property bool verifyStarted: false
    property bool verifyCompleted: false
    property bool verifyErrored: false

    width: 600
    height: 700

    Connections {
        target: AppState

        function onVerifyCompleted() {
            verifyCompleted = true;
        }

        function onVerifyErrored() {
            verifyErrored = true;
        }
    }

    ColumnLayout {
        width: parent.width

        Item {
            width: 200
            height: width
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 75

            CircularProgressBar {
                lineWidth: 6
                value: verifyCompleted || verifyErrored ? 1 : 0
                size: parent.width
                animationDuration: 200
                secondaryColor: Material.color(Material.Grey, Material.Shade300)
                primaryColor: getColor()

                function getColor() {
                    if (verifyCompleted) {
                        return Material.color(Material.Green)
                    } else if (verifyErrored) {
                        return Material.color(Material.Red, Material.Shade300)
                    } else {
                        return Material.color(Material.Blue)
                    }
                }
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
                    color: getColor()

                    function getColor() {
                        if (verifyCompleted) {
                            return Material.color(Material.Green)
                        } else if (verifyErrored) {
                            return Material.color(Material.Red, Material.Shade300)
                        } else {
                            return Material.color(Material.Grey, Material.Shade600)
                        }
                    }
                }
            }
        }

        Label {
            text: "" // Finger.name(selectedEnrollingFinger)
            font.pixelSize: 12
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 16
            color: Material.color(Material.Grey)
        }

        Label {
            text: getText()
            font.pixelSize: 30
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 32
            color: getColor()

            function getText() {
                if (verifyStarted && !verifyCompleted && !verifyErrored) {
                    return "Verifying";
                } else if (verifyStarted && verifyErrored) {
                    return "No Match";
                } else if (verifyStarted && verifyCompleted) {
                    return "Matched";
                }
            }

            function getColor() {
                if (verifyCompleted) {
                    return Material.color(Material.Green);
                } else if (verifyErrored) {
                    return Material.color(Material.Red, Material.Shade300);
                } else {
                    return Material.color(Material.Blue, Material.Shade600);
                }
            }
        }

        Label {
            visible: verifyStarted
            text: AppState.verifyStatusString
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 128
            font.pixelSize: 15
            color: Material.color(Material.Grey, Material.Shade500)
        }

        Button {
            visible: !verifyStarted
            Layout.preferredWidth: 128
            Layout.preferredHeight: 45
            text: "<font color='white'>START</font>"
            font.pixelSize: 10
            font.bold: true
            hoverEnabled: true
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 185

            Material.elevation: 0
            Material.background: Material.Blue

            onClicked: {
                if (FingerboardCppInterface.verifyFp()) {
                    verifyStarted = true;
                }
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
