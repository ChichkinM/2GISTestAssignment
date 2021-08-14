import QtQuick 2.8
import QtQuick.Controls 2.1

import QtCharts 2.2
import QtQuick.Controls.Material 2.1

ApplicationWindow {
    id: applicationWindow
    visible: true
    minimumWidth: 640
    minimumHeight: 480
    title: "Тестовое задание 2GIS"

    Material.theme: Material.Dark
    Material.accent: Material.Teal

    Header {
        id: header
        width: parent.width
    }

    Chart {
        width: parent.width
        anchors {
            top: header.bottom
            bottom: footer.top
        }
    }

    Footer {
        id: footer
        width: parent.width
        anchors.bottom: parent.bottom
    }
}
