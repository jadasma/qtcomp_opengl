#ifndef STARRENDERER_H
#define STARRENDERER_H

#include <QtOpenGL>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QMatrix4x4>
#include <QQuickItem>

class StarRenderer : public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions_3_3_Core {
public:
    StarRenderer();
    ~StarRenderer();

    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;
    void synchronize(QQuickFramebufferObject *item) override;
    // const bool shadersverif;

private:
    QOpenGLShaderProgram m_shaderProgram;
    GLuint m_vbo;
    GLuint m_vao;
    void initializeOpenGL();
    void drawStar();
    bool initializeShaders();
};

class StarItem : public QQuickFramebufferObject {
    Q_OBJECT
public:
    StarItem() {}
    Renderer *createRenderer() const override { return new StarRenderer(); }
};

#endif // STARRENDERER_H
