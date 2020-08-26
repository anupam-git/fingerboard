import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Fingerboard 1.0

ApplicationWindow {
    width: 640
    height: 480
    title: "Fingerboard"
    visible: true

    RowLayout {
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
