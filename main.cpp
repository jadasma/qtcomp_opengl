#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "StarRenderer.h"
#include <QtOpenGL>
#include <QOpenGLWindow>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    // Query OpenGL version and renderer
    qDebug() << "OpenGL Version: " << (const char*)glGetString(GL_VERSION);
    qDebug() << "OpenGL Renderer: " << (const char*)glGetString(GL_RENDERER);
    qDebug() << "123";
    QGuiApplication app(argc, argv);
    qmlRegisterType<StarItem>("CustomComponents", 1, 0, "StarItem");
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

    return app.exec();
}
