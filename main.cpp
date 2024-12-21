#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Star3DItem.h"  // Inclure Star3DItem

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Enregistrer Star3DItem pour QML
    qmlRegisterType<Star3DItem>("CustomShapes", 1, 0, "Star3DItem");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
