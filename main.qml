import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import CustomComponents 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: "OpenGL Star"

    Rectangle {
        anchors.fill: parent
        color: "black"

        StarItem {
            anchors.centerIn: parent
            width: 400
            height: 400
        }
        Rectangle {
            color: "white"
            x: 0
            y: 0
            width: 20
            height: 20
        }
    }
}
