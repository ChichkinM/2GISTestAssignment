import QtQuick 2.8
import QtQuick.Dialogs 1.0
import QtQuick.Controls 2.1

Item {
    readonly property bool hasUrl: doublegis.model.url != ""
    Button {
        id: selectFileButton
        anchors.centerIn: parent
        text: hasUrl ? "Изменить файл" : "Выбрать файл"
        onClicked: fileDialog.open()
    }

    Label {
        text: doublegis.model.url
        visible: hasUrl
    }

    Button {
        text: "Запустить"
        visible: hasUrl
        anchors{
            horizontalCenter: parent.horizontalCenter
            top: selectFileButton.bottom
            topMargin: 24
        }
        onClicked: doublegis.model.run()
    }

    FileDialog {
        id: fileDialog
        title: "Выберите файл"
        folder: shortcuts.home
        onAccepted: {
            doublegis.model.url = fileDialog.fileUrls[0]
        }
    }
}