import QtQuick 2.15
import QtQuick.Window 2.15
import com.example 1.0 // Assurez-vous que c'est bien le nom correct pour StarRenderer

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Étoile 3D")
    color: "black"

    // Utilisation de StarRenderer correctement
    StarRenderer {
        id: star
        width: parent.width
        height: parent.height
    }
}
