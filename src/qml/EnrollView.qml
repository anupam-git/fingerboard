import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.0

import Fingerboard 1.0

Rectangle {
    property int stageCounter: 0
    property bool enrollStarted: false
    property bool enrollCompleted: false
    property bool enrollErrored: false

    width: 600
    height: 700

    Connections {
        target: AppState

        function onEnrollStatusChanged(status) {
            switch (status) {
                case AppState.ENROLL_STAGE_PASSED:
                    stageCounter++;
                    break;
            }
        }

        function onEnrollCompleted() {
            enrollCompleted = true;
            FingerboardCppInterface.listFp();
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
                value: enrollCompleted ? 1 : stageCounter/FingerboardCppInterface.numEnrollStages
                size: parent.width
                animationDuration: 200
                secondaryColor: Material.color(Material.Grey, Material.Shade300)
                primaryColor: getColor()

                function getColor() {
                    if (enrollCompleted) {
                        return Material.color(Material.Green)
                    } else if (enrollErrored) {
                        return Material.color(Material.Red, Material.Shade300)
                    } else {
                        return Material.color(Material.Blue)
                    }
                }
            }

            Image {
                width: 128
                height: 128
                source: "qrc:/fingerprint.svg"
                smooth: true
                anchors.centerIn: parent

                ColorOverlay {
                    anchors.fill: parent
                    source: parent
                    color: getColor()

                    function getColor() {
                        if (enrollCompleted) {
                            return Material.color(Material.Green)
                        } else if (enrollErrored) {
                            return Material.color(Material.Red, Material.Shade300)
                        } else {
                            return Material.color(Material.Grey, Material.Shade600)
                        }
                    }
                }
            }
        }

        Label {
            text: Finger.name(selectedEnrollingFinger)
            font.pixelSize: 12
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 16
            color: Material.color(Material.Grey)
        }

        Label {
            visible: enrollStarted && !enrollCompleted
            text: `Stage ${stageCounter+1}\/${FingerboardCppInterface.numEnrollStages}`
            font.pixelSize: 30
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 32
            color: Material.color(Material.Blue, Material.Shade600)
        }

        Label {
            visible: enrollCompleted
            text: `Completed`
            font.pixelSize: 30
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 32
            color: Material.color(Material.Green)
        }

        Label {
            visible: enrollStarted
            text: AppState.enrollStatusString
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 128
            font.pixelSize: 15
            color: Material.color(Material.Grey, Material.Shade500)
        }

        Button {
            visible: !enrollStarted
            Layout.preferredWidth: 128
            Layout.preferredHeight: 45
            text: "<font color='white'>START</font>"
            font.pixelSize: 12
            font.bold: true
            hoverEnabled: true
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 185

            Material.elevation: 0
            Material.background: Material.Blue

            onClicked: {
                if (FingerboardCppInterface.enrollFp(selectedEnrollingFinger)) {
                    enrollStarted = true;
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
