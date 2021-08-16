import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import Status 1.0

Item {
    MySimpleChart {
        id: chart
        height: parent.height
        anchors{
            left: parent.left
            right: parent.right
        }

        model: doublegis.model.proxy
        maxValue: doublegis.model.primary.maxCount
        visible: doublegis.model.status != Status.NotRunning
    }

    Label {
        anchors.centerIn: parent
        visible: !chart.visible
        text: "Выберите файл и запустите подсчет статистики"
        font.pixelSize: 20
        color: Material.color(Material.Grey)
    }
}
