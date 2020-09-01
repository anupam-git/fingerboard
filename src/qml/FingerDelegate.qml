import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.15
import QtGraphicalEffects 1.15

Rectangle {
    RowLayout {
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width

        Image {
            Layout.preferredWidth: 32
            Layout.preferredHeight: 32
            source: "qrc:/fingerprint.svg"
            Layout.margins: 10
            opacity: model.enrolled ? 1 : 0.5

            ColorOverlay {
                anchors.fill: parent
                source: parent
                color: model.enrolled ? "#7dc73f" : Material.color(Material.Grey)
            }
        }

        Label {
            Layout.fillWidth: true
            text: model.text
            font.pixelSize: 12
            color: Material.color(Material.Grey, Material.Shade600)
            opacity: model.enrolled ? 1 : 0.5
        }

        RoundButton {
            flat: true
            icon.source: model.enrolled ? "qrc:/edit.svg" : "qrc:/add.svg"
            icon.color: Material.color(Material.Grey)
            icon.width: 18
            icon.height: 18
            opacity: 0.5
            hoverEnabled: true

            onClicked: {
                selectedEnrollingFinger = model.finger;
                appstack.push(enrollView);
            }

            PointingHandOverlay {
                anchors.fill: parent
            }

        }
    }
}
