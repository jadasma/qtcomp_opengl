#include "miwidget.h"

miWidget::miWidget(QWidget *parent):QOpenGLWidget(parent)
{

}

void miWidget::initializeGL()
{
 initializeOpenGLFunctions();

 //glClearColor(0.0, 0.0, 0.0, 0.0);
         glEnable(GL_DEPTH_TEST);

}

void miWidget::resizeGL(int w, int h)
{

glViewport(0, 0, w, h);
/*glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   */
   //glOrtho(30.0, 30.0, 30.0, 30.0, 30.0, 30.0);

}

void miWidget::paintGL()
{
/*
glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1,0,0);

glBegin(GL_TRIANGLES);
      glColor3f(1.0f, 0.0f, 0.0f);  // activamos el color rojo
      glVertex3f(-1.0f, 0.0f, 0.0f);
      glColor3f(0.0f,1.0f, 0.0f);  // activamos el color verde
      glVertex3f(1.0f,0.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);  // activamos el color azul
      glVertex3f(0.0f, 1.0f, 0.0f);
glEnd();
 glFlush();*/

    //  Borrar pantalla y Z-buffer
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      glDepthFunc(GL_LESS);
      glEnable(GL_DEPTH_TEST);
      glShadeModel(GL_SMOOTH);
      // Resetear transformaciones
      glLoadIdentity();

      // Otras transformaciones
      // glTranslatef( 0.1, 0.0, 0.0 );      // No incluido
      // glRotatef( 180, 0.0, 1.0, 0.0 );    // No incluido

      // Rotar cuando el usuario cambie “rotate_x” y “rotate_y”
      glRotatef( rotate_x, 1.0, 0.0, 0.0 );
      glRotatef( rotate_y, 0.0, 1.0, 0.0 );
      glRotatef( rotate_z, 0.0, 0.0, 1.0 );


      // Otras transformaciones
      // glScalef( 2.0, 2.0, 0.0 );          // No incluido

      //LADO FRONTAL: lado multicolor
      glBegin(GL_POLYGON);

      glColor3f( 1.0, 0.0, 0.0 );
      glVertex3f(  0.5, -0.5, -0.5 );      // P1 es rojo
      glColor3f( 0.0, 1.0, 0.0 );
      glVertex3f(  0.5,  0.5, -0.5 );      // P2 es verde
      glColor3f( 0.0, 0.0, 1.0 );
      glVertex3f( -0.5,  0.5, -0.5 );      // P3 es azul
      glColor3f( 1.0, 0.0, 1.0 );
      glVertex3f( -0.5, -0.5, -0.5 );      // P4 es morado

      glEnd();

      // LADO TRASERO: lado blanco
      glBegin(GL_POLYGON);
      glColor3f(   1.0,  1.0, 1.0 );
      glVertex3f(  0.5, -0.5, 0.5 );
      glVertex3f(  0.5,  0.5, 0.5 );
      glVertex3f( -0.5,  0.5, 0.5 );
      glVertex3f( -0.5, -0.5, 0.5 );
      glEnd();

      // LADO DERECHO: lado morado
      glBegin(GL_POLYGON);
      glColor3f(  1.0,  0.0,  1.0 );
      glVertex3f( 0.5, -0.5, -0.5 );
      glVertex3f( 0.5,  0.5, -0.5 );
      glVertex3f( 0.5,  0.5,  0.5 );
      glVertex3f( 0.5, -0.5,  0.5 );
      glEnd();

      // LADO IZQUIERDO: lado verde
      glBegin(GL_POLYGON);
      glColor3f(   0.0,  1.0,  0.0 );
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
      glEnd();

      // LADO SUPERIOR: lado azul
      glBegin(GL_POLYGON);
      glColor3f(   0.0,  0.0,  1.0 );
      glVertex3f(  0.5,  0.5,  0.5 );
      glVertex3f(  0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
      glEnd();

      // LADO INFERIOR: lado rojo
      glBegin(GL_POLYGON);
      glColor3f(   1.0,  0.0,  0.0 );
      glVertex3f(  0.5, -0.5, -0.5 );
      glVertex3f(  0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
      glEnd();


      graficarLineas();
      glFlush();
        this->makeCurrent();

}

void miWidget::graficarLineas()
{

        glBegin(GL_LINES);
            glColor3f(1,0,0);
            glVertex3f(0,0,0);
            glVertex3f(20,0,0);

            glColor3f(1,1,0);
            glVertex3f(0,0,0);
            glVertex3f(0,20,0);

            glColor3f(0,1,1);
            glVertex3f(0,0,0);
            glVertex3f(0,0,20);
        glEnd();

}
