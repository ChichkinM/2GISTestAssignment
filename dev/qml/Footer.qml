import QtQuick 2.8
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.1
import Status 1.0

Item {
    implicitHeight: 40

    HorizontalLine {}

    Label {
        id: label
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

    Label {
        id: performerLabel
        anchors.centerIn: parent
        visible: doublegis.model.status != Status.NotRunning

        function update() {
            var now = (new Date()).getTime() / 1000
            var begin = doublegis.model.begin.getTime() / 1000
            var end = doublegis.model.end.getTime() / 1000

            var result = doublegis.model.status == Status.Running ?
                                  now - begin : end - begin
            performerLabel.text = result.toFixed(1) +  " сек."
        }

        Timer {
            interval: 100
            repeat: true
            running: doublegis.model.status == Status.Running
            onTriggered: performerLabel.update()
            onRunningChanged: performerLabel.update()
        }
    }

    Image {
        id: autorenewImage
        visible: false
        anchors {
            right: parent.right
            rightMargin: 8
            verticalCenter: parent.verticalCenter
        }
        sourceSize.width: 24
        sourceSize.height: 24
        source: "qrc:/autorenew.svg"
    }

    ColorOverlay {
        id: overlay
        anchors.fill: autorenewImage
        visible: doublegis.model.status == Status.Running
        source: autorenewImage
        color: Material.color(Material.Teal)

        onVisibleChanged: {
            animator.running = visible
        }
    }

    RotationAnimator {
        id: animator
        target: overlay
        from: 0
        to: 360
        duration: 1000
        running: true
        loops: Animation.Infinite
    }
}