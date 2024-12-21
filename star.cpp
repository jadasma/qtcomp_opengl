#include "star.h"
#include <QOpenGLShader>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

StarRenderer::StarRenderer(QObject* parent) : QObject(parent), shaderProgram(nullptr) {}

void StarRenderer::initialize()
{
    initializeOpenGLFunctions();

    // Créer un programme de shader
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertexShader.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fragmentShader.frag");
    shaderProgram->link();

    GLuint texCoordLocation = 1;
    GLuint vertexPositionLocation = 0;

    shaderProgram->enableAttributeArray(vertexPositionLocation);
    shaderProgram->setAttributeBuffer(vertexPositionLocation, GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);

    shaderProgram->enableAttributeArray(texCoordLocation);
    shaderProgram->setAttributeBuffer(texCoordLocation, GL_FLOAT, 0, 4, sizeof(GLfloat) * 4);
}

void StarRenderer::render(const QMatrix4x4 &mvpMatrix)
{
       Q_UNUSED(mvpMatrix);
    shaderProgram->bind();
    // Dessiner la scène ici...
    shaderProgram->release();
}
