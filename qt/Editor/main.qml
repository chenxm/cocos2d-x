import QtQuick 2.0

import SceneGraphRendering 1.0

Item {
    width: 800
    height: 600

    Renderer {
        id: renderer
        anchors.fill: parent
        anchors.margins: 0

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
        anchors.bottom: renderer.bottom
        anchors.left: renderer.left
        anchors.right: renderer.right
        anchors.margins: 20
        wrapMode: Text.WordWrap
        text: "The blue rectangle with the vintage 'Q' is an FBO, rendered by the application in a dedicated background thread. The background thread juggles two FBOs, one that is being rendered to and one for displaying. The texture to display is posted to the scene graph and displayed using a QSGSimpleTextureNode."
    }


}
