#version 330 core

layout(location = 0) in vec3 vertexPosition;      // Position des sommets
in vec4 qt_MultiTexCoord0;                         // Coordonnées de texture
uniform mat4 mvpMatrix;                            // Matrice de projection et modèle
out vec4 qt_TexCoord0;                             // Coordonnées de texture à envoyer au fragment shader

void main(void)
{
    // Passer les coordonnées de texture au fragment shader
    qt_TexCoord0 = qt_MultiTexCoord0;

    // Calcul de la position finale du sommet
    gl_Position = mvpMatrix * vec4(vertexPosition, 1.0);
}
