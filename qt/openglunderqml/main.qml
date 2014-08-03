import QtQuick 2.0
import OpenGLUnderQML 1.0

Item {

    width: 800
    height: 600

    Squircle {
        id: glwindow
        anchors.fill: parent
        anchors.margins: 100
    }

    Rectangle {
        color: Qt.rgba(0, 0, 0, 0)
        radius: 10
        border.width: 1
        border.color: "white"
        anchors.fill: glwindow
        anchors.margins: 0
    }

    Rectangle {
        color: Qt.rgba(0, 0, 1, 0.5)
        radius: 10
        border.width: 1
        border.color: "white"
        anchors.fill: label
        anchors.margins: -10
    }

    Text {
        id: label
        color: "black"
        wrapMode: Text.WordWrap
        text: "The background here is a squircle rendered with raw OpenGL using the 'beforeRender()' signal in QQuickWindow. This text label and its border is rendered using QML"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }
}
