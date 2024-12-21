#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QMatrix4x4>
#include <QQmlContext>
#include <QVariant>

#include "star.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    // Enregistrez le type StarRenderer (assurez-vous que cela correspond à votre classe dans star.h)
    qmlRegisterType<StarRenderer>("com.example", 1, 0, "star");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);
    // Initialiser le rendu OpenGL
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    return app.exec();
}
