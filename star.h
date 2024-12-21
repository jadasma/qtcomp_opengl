#ifndef STAR_H
#define STAR_H

#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <vector>
#include <QMatrix4x4>

class StarRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit StarRenderer(QObject *parent = nullptr);
    ~StarRenderer();

    void initialize();
    void render(const QMatrix4x4 &mvpMatrix);

signals:
         // Define your signals here

public slots:
              // Define your slots here

private:
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
      QOpenGLShaderProgram* shaderProgram;  // Pointeur, pas un objet

    std::vector<float> starVertices;
};

#endif // STAR_H
