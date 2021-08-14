import QtQuick 2.8
import QtQuick.Controls 2.1
import Status 1.0

Item {
    implicitHeight: 40

    HorizontalLine {}

    Label {
        text: {
            var percent = (doublegis.model.processedSize / doublegis.model.fullSize) * 100
            percent = parseInt(percent, 10)
            return percent + "% (" + doublegis.model.processedSize +
                   " / " + doublegis.model.fullSize + ")"
        }
        visible: doublegis.model.status == Status.Running ||
                 doublegis.model.status == Status.Done
        anchors{
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 8
        }
    }
}