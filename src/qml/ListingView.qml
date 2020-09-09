import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import QtGraphicalEffects 1.12

import Fingerboard 1.0

Rectangle {
    property int ditchGap: 2

    width: 600

    Connections {
        target: FingerboardCppInterface

        // function onEnrolledFingerprintsList(fingerprints)
        onEnrolledFingerprintsList: {
            var enrolledFingersMap = {};

            for (var enrolledFinger in fingerprints) {
                enrolledFingersMap[fingerprints[enrolledFinger]] = true;
            }

            for (var i=0; i<leftHandFingers.count; i++) {
                leftHandFingers.setProperty(i, "enrolled", enrolledFingersMap[leftHandFingers.get(i).finger] || false);
            }

            for (var j=0; j<rightHandFingers.count; j++) {
                rightHandFingers.setProperty(j, "enrolled", enrolledFingersMap[rightHandFingers.get(j).finger] || false);
            }
        }
    }

    ListModel {
        id: leftHandFingers

        ListElement {
            text: "Left Thumb"
            finger: Finger.LEFT_THUMB
            enrolled: false
        }
        ListElement {
            text: "Left Index Finger"
            finger: Finger.LEFT_INDEX
            enrolled: false
        }
        ListElement {
            text: "Left Middle Finger"
            finger: Finger.LEFT_MIDDLE
            enrolled: false
        }
        ListElement {
            text: "Left Ring Finger"
            finger: Finger.LEFT_RING
            enrolled: false
        }
        ListElement {
            text: "Left Little Finger"
            finger: Finger.LEFT_LITTLE
            enrolled: false
        }
    }
    ListModel {
        id: rightHandFingers

        ListElement {
            text: "Right Thumb"
            finger: Finger.RIGHT_THUMB
            enrolled: false
        }
        ListElement {
            text: "Right Index Finger"
            finger: Finger.RIGHT_INDEX
            enrolled: false
        }
        ListElement {
            text: "Right Middle Finger"
            finger: Finger.RIGHT_MIDDLE
            enrolled: false
        }
        ListElement {
            text: "Right Ring Finger"
            finger: Finger.RIGHT_RING
            enrolled: false
        }
        ListElement {
            text: "Right Little Finger"
            finger: Finger.RIGHT_LITTLE
            enrolled: false
        }
    }

    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 150

            ColumnLayout {
                anchors.centerIn: parent

                Image {
                    source: "qrc:/applogo.svg"
                    smooth: true
                    Layout.alignment: Qt.AlignHCenter

                    ColorOverlay {
                        anchors.fill: parent
                        source: parent
                        color: Material.color(Material.Blue)
                    }
                }

                Label {
                    text: "Fingerboard"
                    font.pixelSize: 24
                    color: Material.color(Material.Grey, Material.Shade800)
                }
            }
        }

        GridLayout {
            width: parent.width
            columns: 2
            columnSpacing: ditchGap
            rowSpacing: ditchGap

            ColumnLayout {
                width: parent.width/2
                spacing: ditchGap
                Layout.margins: 0

                Rectangle {
                    Layout.fillWidth: true
                    height: 60

                    RowLayout {
                        anchors.centerIn: parent

                        Label {
                            text: "Left Hand"
                            font.pixelSize: 14
                            font.bold: true
                            color: Material.color(Material.Grey, Material.Shade600)
                        }
                    }
                }

                Repeater {
                    model: leftHandFingers

                    delegate: FingerDelegate {
                        Layout.fillWidth: true
                        height: 60
                    }
                }
            }

            ColumnLayout {
                width: parent.width/2
                spacing: ditchGap

                Rectangle {
                    Layout.fillWidth: true
                    height: 60

                    RowLayout {
                        anchors.centerIn: parent

                        Label {
                            text: "Right Hand"
                            font.pixelSize: 14
                            font.bold: true
                            color: Material.color(Material.Grey, Material.Shade600)
                        }
                    }
                }

                Repeater {
                    model: rightHandFingers

                    delegate: FingerDelegate {
                        Layout.fillWidth: true
                        height: 60
                    }
                }
            }
        }

        Button {
            Layout.fillWidth: true
            text: "<font color='white'>VERIFY FINGERPRINT</font>"
            font.pixelSize: 12
            font.bold: true
            bottomInset: 0
            topInset: 0
            hoverEnabled: true

            Material.elevation: 0
            Material.background: Material.Blue

            onClicked: {
                appstack.push(verifyView);
            }

            PointingHandOverlay {
                anchors.fill: parent
            }
        }
    }
}
