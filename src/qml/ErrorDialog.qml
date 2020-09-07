import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15

Dialog {
    property alias errorString: errorLabel.text

    visible: true
    modal: true
    implicitWidth: 400
    z: 10

    font.pixelSize: 10

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    footer: DialogButtonBox {
        Button {
            flat: true
            text: "OK"
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
            font.pixelSize: 10
            font.bold: true
            hoverEnabled: true

            PointingHandOverlay {
                anchors.fill: parent
            }
        }        
    }

    ColumnLayout {
        Label {
            text: "ERROR"
            font.pixelSize: 15
            font.bold: true
            topPadding: 16
            bottomPadding: 16
            leftPadding: 12
        }

        Label {
            id: errorLabel

            font.pixelSize: 12
            leftPadding: 12
        }
    }

}
