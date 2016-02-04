// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>

#include "myglwidget.h"



#define X_MAX_FIRST 0.2
#define X_MIN_FIRST -0.2

#define Y_MAX_FIRST 1.8
#define Y_MIN_FIRST 1.0

#define Z_MAX_FIRST 0.25
#define Z_MIN_FIRST -0.25



#define X_MAX_SECOND 0.2
#define X_MIN_SECOND -0.2

#define Y_MAX_SECOND 0.8
#define Y_MIN_SECOND 0.0

#define Z_MAX_SECOND 0.25
#define Z_MIN_SECOND -0.25

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    //    xRot1 = 0;
    //    yRot1 = 0;
    //    zRot1 = 0;

    //    xRot2 = 0;
    //    yRot2 = 0;
    //    zRot2 = 0;
}

MyGLWidget::~MyGLWidget()
{
}


void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    /*
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
*/
    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
/////////////////////////////////////////////////////////change this fragment
//    draw();
//    glLoadIdentity();
//    glTranslatef(0.0, 0.0, -10.0);

}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}


void MyGLWidget::inputData(Acc* data)
{
    if(data->id == 0)
    {
        rotation[0].x_ = data->x;
        rotation[0].y_ = data->y;
        rotation[0].z_ = data->z;
    }

    else
    {
        rotation[1].x_ = data->x;
        rotation[1].y_ = data->y;
        rotation[1].z_ = data->z;
    }

    updateGL();
}



void MyGLWidget::draw(char id, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max)
{
    if(id == 0)
    {
        glRotatef(rotation[0].x_ / 16.0, 1.0, 0.0, 0.0);
        glRotatef(rotation[0].y_ / 16.0, 0.0, 1.0, 0.0);
        glRotatef(rotation[0].z_ / 16.0, 0.0, 0.0, 1.0);

    }

    else
    {
        glRotatef(rotation[1].x_ / 16.0, 1.0, 0.0, 0.0);
        glRotatef(rotation[1].y_ / 16.0, 0.0, 1.0, 0.0);
        glRotatef(rotation[1].z_ / 16.0, 0.0, 0.0, 1.0);

    }

    glPolygonMode( GL_BACK, GL_LINE);
    glBegin(GL_QUADS);
        glNormal3f(0,0,1);
        glVertex3f( x_min,     y_min,    z_max);
        glVertex3f( x_min,     y_max,    z_max);
        glVertex3f( x_max,     y_max,    z_max );
        glVertex3f( x_max,     y_min,    z_max );
    glEnd();


    //BACK
    //  glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f( x_min,     y_min,     z_min);
        glVertex3f( x_min,     y_max,     z_min);
        glVertex3f( x_max,     y_max,     z_min);
        glVertex3f( x_max,     y_min,     z_min);
    glEnd();

    //TOP
    glBegin(GL_QUADS);
        glNormal3f(0,0,1);
        glVertex3f( x_min,     y_max,    z_min );
        glVertex3f( x_min,     y_max,    z_max );
        glVertex3f( x_max,     y_max,    z_max );
        glVertex3f( x_max,     y_max,    z_min );
    glEnd();

    //BELOW
    glBegin(GL_QUADS);
        glNormal3f(0,0,1);
        glVertex3f( x_min,     y_min,    z_min );
        glVertex3f( x_min,     y_min,    z_max );
        glVertex3f( x_max,     y_min,    z_max );
    glVertex3f( x_max,     y_min,    z_min );

    glEnd();

    //LEFT

    glBegin(GL_QUADS);
        glNormal3f(0,0,1);
        glVertex3f( x_min,     y_min,    z_min );
        glVertex3f( x_min,     y_min,    z_max );
        glVertex3f( x_min,     y_max,    z_max );
    glVertex3f( x_min,     y_max,    z_min );

    glEnd();

    //RIGHT

    glBegin(GL_QUADS);
        glNormal3f(0,0,1);
        glVertex3f( x_max,     y_min,    z_min );
        glVertex3f( x_max,     y_min,    z_max );
        glVertex3f( x_max,     y_max,    z_max );
        glVertex3f( x_max,     y_max,    z_min );
    glEnd();

}



