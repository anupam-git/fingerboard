import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

import Fingerboard 1.0

Dialog {
    modal: true
    implicitWidth: 400
    z: 10

    font.pixelSize: 10

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    footer: DialogButtonBox {
        Button {
            flat: true
            text: "CANCEL"
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
            font.pixelSize: 12
            font.bold: true
            hoverEnabled: true

            PointingHandOverlay {
                anchors.fill: parent
            }
        }
        Button {
            flat: true
            text: "<font color='"+Material.color(Material.Red)+"'>DELETE</font>"
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
            font.pixelSize: 12
            font.bold: true
            hoverEnabled: true

            Material.accent: Material.Red

            PointingHandOverlay {
                anchors.fill: parent
            }
        }
    }

    onAccepted: {
        FingerboardCppInterface.deleteFp();
    }

    Connections {
        target: AppState

        function onDeleteCompleted() {
            FingerboardCppInterface.listFp();
        }
    }

    ColumnLayout {
        Label {
            text: "Delete Fingerprints"
            font.pixelSize: 16
            font.bold: true
            topPadding: 16
            bottomPadding: 16
            leftPadding: 12
        }

        Label {
            text: "Are you sure you wish to delete <b>ALL</b> fingerprints ?"
            font.pixelSize: 14
            leftPadding: 12
        }
    }

}
