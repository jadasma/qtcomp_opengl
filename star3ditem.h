#ifndef STAR3DITEM_H
#define STAR3DITEM_H

#include <QQuickItem>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

class Star3DItem : public QQuickItem, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    Star3DItem();
    ~Star3DItem();

protected:
    void releaseResources() override;
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *data) override;

private:
    void initializeGL();
    void render();

    bool m_initialized = false;
    QOpenGLShaderProgram *m_program = nullptr;
    GLuint m_vbo = 0, m_vao = 0, m_ebo = 0;

    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_modelViewMatrix;
    float m_angle = 0.0f;
};

#endif // STAR3DITEM_H
