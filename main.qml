import QtQuick.Controls 2.15 // Pour accéder à `ApplicationWindow`
import CustomShapes 1.0  // Assurez-vous que CustomShapes est bien importé

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "Etoile_3D"

    Star3DItem {
        width: 300
        height: 300
    }
}

