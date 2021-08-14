import QtQuick 2.8
import QtQuick.Controls 2.1
import Qt.labs.platform 1.0
import Status 1.0

Item {
    implicitHeight: 60

    readonly property bool hasUrl: doublegis.model.url != ""
    Button {
        id: selectFileButton
        anchors{
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 8
        }
        enabled: doublegis.model.status != Status.Running
        text: hasUrl ? "Изменить файл" : "Выбрать файл"
        onClicked: fileDialog.open()
    }

    Item {
        clip: true
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: selectFileButton.right
            right: lauchButton.left
        }

        Label {
            text: doublegis.model.fileName
            visible: hasUrl
            anchors.centerIn: parent
        }
    }

    Button {
        id: lauchButton
        text: "Запустить"
        enabled: doublegis.model.status != Status.Running
        visible: hasUrl
        anchors{
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 8
        }
        onClicked: {
            if(doublegis.model.status != Status.Running) {
                doublegis.model.run()
            }
        }
    }

    FileDialog {
        id: fileDialog
        title: "Выберите файл"
        folder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
        onAccepted: {
            doublegis.model.url = fileDialog.file
        }
    }

    HorizontalLine {
        anchors.bottom: parent.bottom
    }
}