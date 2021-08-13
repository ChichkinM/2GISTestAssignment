import QtQuick 2.8
import QtQuick.Controls 2.1
import Qt.labs.platform 1.1

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
        onAccepted: {
            doublegis.model.url = fileDialog.fileUrls[0]
        }
    }

    Label {
        text: {
            var percent = (doublegis.model.processedSize / doublegis.model.fullSize) * 100
            percent = parseInt(percent, 10)
            return percent + "% (" + doublegis.model.processedSize +
                   " / " + doublegis.model.fullSize + ")"
        }
        visible: hasUrl
        anchors.bottom: parent.bottom
    }
}