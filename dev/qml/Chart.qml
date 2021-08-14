import QtQuick 2.8
import QtQuick.Controls 2.1

Item {
    MySimpleChart {
        height: parent.height
        anchors{
            left: parent.left
            right: parent.right
        }

        model: doublegis.model.proxy
        maxValue: doublegis.model.primary.maxCount
    }
}
