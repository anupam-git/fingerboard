import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

Dialog {
    modal: true
    implicitWidth: 400
    font.pixelSize: 10
    z: 10


    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    footer: DialogButtonBox {
        Button {
            flat: true
            text: "OK"
            font.pixelSize: 10
            font.bold: true
            hoverEnabled: true
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole

            PointingHandOverlay {
                anchors.fill: parent
            }
        }
    }

    ColumnLayout {
        Label {
            text: "About"
            font.pixelSize: 24
            font.bold: true
            topPadding: 16
            bottomPadding: 16
            leftPadding: 12
        }

        Label {
            text: "A fprintd based fingerprint GUI for Linux"

            Layout.topMargin: 12
            font.pixelSize: 12
            leftPadding: 12
        }

        Label {
            text: "<b>Author :</b> Anupam Basak &lt;<a href='https://github.com/anupam-git'>GitHub</a>&gt;"
            onLinkActivated: Qt.openUrlExternally(link)

            Layout.topMargin: 32
            font.pixelSize: 12
            leftPadding: 12
        }
        Label {
            text: "<b>Repository :</b> <a href='https://github.com/anupam-git/fingerboard'>https://github.com/anupam-git/fingerboard</a>"
            onLinkActivated: Qt.openUrlExternally(link)

            enabled: true
            font.pixelSize: 12
            leftPadding: 12
        }
    }
}
