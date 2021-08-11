import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1

ApplicationWindow {
    visible: true
    minimumWidth: 640
    minimumHeight: 480
    title: "Тестовое задание 2GIS"

    Material.theme: Material.Dark
    Material.accent: Material.Teal

    Component {
        id: firstScreen
        FirstScreen {}
    }

    Loader {
        anchors.fill: parent
        sourceComponent: firstScreen
    }
}
