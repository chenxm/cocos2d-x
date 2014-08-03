import QtQuick 2.0

import SceneGraphRendering 1.0

Item {
    width: 800
    height: 600

    Renderer {
        id: renderer
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 100

        // The transform is just to show something interesting..
        transform: [
            Rotation { id: rotation; axis.x: 1; axis.z: 0; axis.y: 0;angle: 180; origin.x: renderer.width / 2; origin.y: renderer.height / 2;}
        ]
    }

    Rectangle {
        id: labelFrame
        anchors.margins: -10
        radius: 5
        color: "white"
        border.color: "black"
        opacity: 0.8
        anchors.fill: label
    }

    Text {
        id: label
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        wrapMode: Text.WordWrap
        text: "The blue rectangle with the vintage 'Q' is an FBO, rendered by the application on the scene graph rendering thread. The FBO is managed and displayed using the QQuickFramebufferObject convenience class."
    }


}
