import QtQuick 2.8
import QtQuick.Controls 2.1

Item {
    id: root
    property var model
    property int maxValue: 0

    Column {
        id: column
        anchors {
            fill: parent
            margins: 8
        }

        Repeater {
            id: repeater
            model: root.model

            delegate: MySimpleChartBarDelegate {
                width: column.width
                height: column.height / repeater.count
                modelEntry: model
            }
        }
    }
}