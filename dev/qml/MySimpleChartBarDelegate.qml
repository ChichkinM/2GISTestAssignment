import QtQuick 2.8
import QtQuick.Controls 2.1

Item {
    property var modelEntry
    readonly property int labelMaxWidth: 150

    Label {
        id: label
        width: labelMaxWidth
        anchors.verticalCenter: parent.verticalCenter
        elide: Label.ElideRight
        text: modelEntry.word
    }

    VerticalLine {
        id: separator
        anchors.left: label.right
    }

    Item {
        id: rightColumn
        height: parent.height
        anchors {
            left: separator.right
            right: parent.right
        }

        Rectangle {
            id: bar
            height: parent.height - 8
            anchors.verticalCenter: parent.verticalCenter
            width: ( modelEntry.count / root.maxValue ) * rightColumn.width
            color: Qt.rgba(Math.random(),Math.random(),Math.random(), 1)

            Pane {
                anchors{
                    fill: labelInBar
                }
            }
            Label {
                id: labelInBar
                anchors{
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                    rightMargin: 8
                }
                text: modelEntry.count
            }
        }
    }
}