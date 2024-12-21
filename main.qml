import QtQuick 2.15
import QtQuick.Controls 2.15 // Pour accéder à `ApplicationWindow`
import CustomShapes 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480


    Star3DItem {
        width: 300
        height: 300
    }
}
