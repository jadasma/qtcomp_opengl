#include "Star3DItem.h"
#include <QSGSimpleTextureNode>
#include <QtMath>
#include <QOpenGLFunctions_3_3_Core>

Star3DItem::Star3DItem()
{
    setFlag(ItemHasContents, true);
    m_program = nullptr;
    m_initialized = false;
}

Star3DItem::~Star3DItem()
{
    releaseResources();
}

void Star3DItem::initializeGL()
{
    initializeOpenGLFunctions();

    // Vérification des erreurs OpenGL au démarrage
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        qCritical() << "OpenGL Error at initialization:" << err;
    }

    // Coordonnées d'une étoile 3D (pointes et sommets intérieurs)
    GLfloat vertices[] = {
        // Positions            // Couleurs
        0.0f,  1.0f,  0.0f,    1.0f, 0.0f, 0.0f,  // Pointe supérieure
        0.5f,  0.2f, -0.5f,    0.0f, 1.0f, 0.0f,  // Pointe droite avant
        0.5f,  0.2f,  0.5f,    0.0f, 0.0f, 1.0f,  // Pointe droite arrière
        -0.5f,  0.2f,  0.5f,    1.0f, 1.0f, 0.0f,  // Pointe gauche arrière
        -0.5f,  0.2f, -0.5f,    1.0f, 0.0f, 1.0f,  // Pointe gauche avant
        0.0f, -0.5f,  0.0f,    0.5f, 0.5f, 0.5f,  // Centre bas
    };

    GLuint indices[] = {
        0, 1, 2,  // Face avant droite
        0, 2, 3,  // Face arrière droite
        0, 3, 4,  // Face arrière gauche
        0, 4, 1,  // Face avant gauche
        1, 5, 2,  // Face bas droite avant
        2, 5, 3,  // Face bas droite arrière
        3, 5, 4,  // Face bas gauche arrière
        4, 5, 1,  // Face bas gauche avant
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Couleurs
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Shaders
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       R"(
                                       #version 330 core
                                       layout (location = 0) in vec3 aPos;
                                       layout (location = 1) in vec3 aColor;

                                       out vec3 ourColor;

                                       uniform mat4 modelViewMatrix;
                                       uniform mat4 projectionMatrix;

                                       void main() {
                                           gl_Position = projectionMatrix * modelViewMatrix * vec4(aPos, 1.0);
                                           ourColor = aColor;
                                       }
                                       )");
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       R"(
                                       #version 330 core
                                       in vec3 ourColor;
                                       out vec4 FragColor;

                                       void main() {
                                           FragColor = vec4(ourColor, 1.0);
                                       }
                                       )");

    if (!m_program->link()) {
        qCritical() << "Shader program failed to link:" << m_program->log();
    } else {
        qDebug() << "Shader program linked successfully.";
    }

    glEnable(GL_DEPTH_TEST);  // Activer le test de profondeur pour la 3D
    err = glGetError();
    if (err != GL_NO_ERROR) {
        qCritical() << "OpenGL Error after enabling depth test:" << err;
    }

    m_initialized = true;
}

void Star3DItem::render()
{
    if (!m_initialized)
        initializeGL();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    // Configurer les matrices
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45.0f, width() / float(height()), 0.1f, 100.0f);

    m_modelViewMatrix.setToIdentity();
    m_modelViewMatrix.translate(0.0f, 0.0f, -5.0f);
    m_modelViewMatrix.rotate(m_angle, 0.0f, 1.0f, 0.0f); // Faire tourner l'étoile
    m_angle += 1.0f; // Incrémenter l'angle pour l'animation

    m_program->setUniformValue("modelViewMatrix", m_modelViewMatrix);
    m_program->setUniformValue("projectionMatrix", m_projectionMatrix);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    m_program->release();
}

void Star3DItem::releaseResources()
{
    if (m_program) {
        m_program->removeAllShaders();
        delete m_program;
        m_program = nullptr;
    }
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
    if (m_vbo) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }
    if (m_ebo) {
        glDeleteBuffers(1, &m_ebo);
        m_ebo = 0;
    }
}

QSGNode *Star3DItem::updatePaintNode(QSGNode *node, UpdatePaintNodeData *data)
{
    Q_UNUSED(data);

    if (!node)
        node = new QSGSimpleTextureNode();

    render();

    return node;
}
