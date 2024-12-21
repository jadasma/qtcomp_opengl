#include "StarRenderer.h"

StarRenderer::StarRenderer() {
    initializeOpenGLFunctions();  // Initialize OpenGL functions from QOpenGLFunctions
    initializeOpenGL();
}

StarRenderer::~StarRenderer() {
    // Use QOpenGLFunctions versions of the functions
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);   // Replaced raw OpenGL call with QOpenGLFunctions
}

void StarRenderer::initializeOpenGL() {
    initializeShaders();
    static const GLfloat starVertices[] = {
        0.0f,  1.0f, 0.0f,  // Top point
        -0.5f,  0.3f, 0.0f, // Bottom-left inner point
        -1.0f, -0.5f, 0.0f, // Bottom-left outer point

        0.0f,  1.0f, 0.0f,  // Top point
        -1.0f, -0.5f, 0.0f, // Bottom-left outer point
        0.5f, -0.5f, 0.0f,  // Bottom-right outer point

        // Add additional triangles to form the star shape
    };

    // Use QOpenGLFunctions methods
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(starVertices), starVertices, GL_STATIC_DRAW);

    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/star.vert");
    m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/star.frag");
    m_shaderProgram.link();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void StarRenderer::render() {
    glViewport(0, 0, framebufferObject()->size().width(), framebufferObject()->size().height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    QMatrix4x4 mvp;
    mvp.ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    m_shaderProgram.bind();
    m_shaderProgram.setUniformValue("mvp", mvp);

    glBindVertexArray(m_vao);
    drawStar();
    glBindVertexArray(0);

    m_shaderProgram.release();

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        qDebug() << "OpenGL Error:" << error;
    }
}


QOpenGLFramebufferObject *StarRenderer::createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::Depth);
    return new QOpenGLFramebufferObject(size, format);
}

void StarRenderer::synchronize(QQuickFramebufferObject *item) {
    Q_UNUSED(item);
}
void StarRenderer::drawStar() {
    glDrawArrays(GL_TRIANGLES, 0, 12); // Adjust vertex count based on the star shape
}
bool StarRenderer::initializeShaders() {
    bool success = m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/star.vert");
    if (!success) {
        qDebug() << "Vertex shader compilation failed: " << m_shaderProgram.log();
        return false;
    }

    success = m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/star.frag");
    if (!success) {
        qDebug() << "Fragment shader compilation failed: " << m_shaderProgram.log();
        return false;
    }

    if (!m_shaderProgram.link()) {
        qDebug() << "Shader program linking failed: " << m_shaderProgram.log();
        return false;
    }

    return true;
}

