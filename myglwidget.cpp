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
    xRot1 = 0;
    yRot1 = 0;
    zRot1 = 0;

    xRot2 = 0;
    yRot2 = 0;
    zRot2 = 0;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}
//1
void MyGLWidget::setXRotation1(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot1) {
        xRot1 = angle;
       // emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation1(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot1) {
        yRot1 = angle;
       // emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation1(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot1) {
        zRot1 = angle;
        //emit zRotationChanged(angle);
        updateGL();
    }
}
//2
void MyGLWidget::setXRotation2(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot2) {
        xRot2 = angle;
       // emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation2(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot2) {
        yRot2 = angle;
       // emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation2(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot2) {
        zRot2 = angle;
        //emit zRotationChanged(angle);
        updateGL();
    }
}

void  MyGLWidget::accel1(int x, int y, int z)
{
    setXRotation1(x);
    setYRotation1(y);
    setYRotation1(z);
}

void  MyGLWidget::accel2(int x, int y, int z)
{
    setXRotation2(x);
    setYRotation2(y);
    setYRotation2(z);
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

    draw_first();



    glLoadIdentity();

    glTranslatef(0.0, 0.0, -10.0);


   draw_second();

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

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
int dz;
    if (event->buttons() & Qt::LeftButton) {
        setXRotation1(xRot1 + 8 * dy);
        setYRotation1(yRot1 + 8 * dx);
        //setZRotation1(zRot1 + 8 * dz);

    } else if (event->buttons() & Qt::RightButton) {

       setXRotation2(xRot2 + 8 * dy);
        setYRotation2(yRot2 + 8 * dx);

    //    setZRotation2(zRot2 + 8 * dz);
    }

    lastPos = event->pos();
}

void MyGLWidget::draw_first()
{
    glRotatef(xRot1 / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot1 / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot1 / 16.0, 0.0, 0.0, 1.0);
    qglColor(Qt::green);

//FRONT,
glPolygonMode( GL_BACK, GL_LINE);
    glBegin(GL_QUADS);
       glNormal3f(0,0,1);
       glVertex3f( X_MIN_FIRST,     Y_MIN_FIRST,    Z_MAX_FIRST);
       glVertex3f( X_MIN_FIRST,     Y_MAX_FIRST,    Z_MAX_FIRST);
       glVertex3f( X_MAX_FIRST,     Y_MAX_FIRST,    Z_MAX_FIRST );
       glVertex3f( X_MAX_FIRST,     Y_MIN_FIRST,    Z_MAX_FIRST );
     glEnd();


//BACK
   //  glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_QUADS);
       glNormal3f(0,0,-1);
       glVertex3f( X_MIN_FIRST,     Y_MIN_FIRST,     Z_MIN_FIRST);
       glVertex3f( X_MIN_FIRST,     Y_MAX_FIRST,     Z_MIN_FIRST);
       glVertex3f( X_MAX_FIRST,     Y_MAX_FIRST,     Z_MIN_FIRST);
       glVertex3f( X_MAX_FIRST,     Y_MIN_FIRST,     Z_MIN_FIRST);
     glEnd();

//TOP

    glBegin(GL_QUADS);
       glNormal3f(0,0,1);
       glVertex3f( X_MIN_FIRST,     Y_MAX_FIRST,    Z_MIN_FIRST );
       glVertex3f( X_MIN_FIRST,     Y_MAX_FIRST,    Z_MAX_FIRST );
       glVertex3f( X_MAX_FIRST,     Y_MAX_FIRST,    Z_MAX_FIRST );
       glVertex3f( X_MAX_FIRST,     Y_MAX_FIRST,    Z_MIN_FIRST );

    glEnd();

//BELOW

    glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glVertex3f( X_MIN_FIRST,     Y_MIN_FIRST,    Z_MIN_FIRST );
      glVertex3f( X_MIN_FIRST,     Y_MIN_FIRST,    Z_MAX_FIRST );
      glVertex3f( X_MAX_FIRST,     Y_MIN_FIRST,    Z_MAX_FIRST );
      glVertex3f( X_MAX_FIRST,     Y_MIN_FIRST,    Z_MIN_FIRST );

    glEnd();

//LEFT

    glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glVertex3f( X_MIN_FIRST,     Y_MIN_FIRST,    Z_MIN_FIRST );
      glVertex3f( X_MIN_FIRST,     Y_MIN_FIRST,    Z_MAX_FIRST );
      glVertex3f( X_MIN_FIRST,     Y_MAX_FIRST,    Z_MAX_FIRST );
      glVertex3f( X_MIN_FIRST,     Y_MAX_FIRST,    Z_MIN_FIRST );

    glEnd();

//RIGHT

    glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glVertex3f( X_MAX_FIRST,     Y_MIN_FIRST,    Z_MIN_FIRST );
      glVertex3f( X_MAX_FIRST,     Y_MIN_FIRST,    Z_MAX_FIRST );
      glVertex3f( X_MAX_FIRST,     Y_MAX_FIRST,    Z_MAX_FIRST );
      glVertex3f( X_MAX_FIRST,     Y_MAX_FIRST,    Z_MIN_FIRST );
glEnd();

//
}

void MyGLWidget::draw_second()
{
    glRotatef(xRot2 / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot2 / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot2 / 16.0, 0.0, 0.0, 1.0);
    qglColor(Qt::green);

//FRONT,
glPolygonMode( GL_BACK, GL_LINE);
    glBegin(GL_QUADS);
       glNormal3f(0,0,1);
       glVertex3f( X_MIN_SECOND,     Y_MIN_SECOND,    Z_MAX_SECOND);
       glVertex3f( X_MIN_SECOND,     Y_MAX_SECOND,    Z_MAX_SECOND);
       glVertex3f( X_MAX_SECOND,     Y_MAX_SECOND,    Z_MAX_SECOND );
       glVertex3f( X_MAX_SECOND,     Y_MIN_SECOND,    Z_MAX_SECOND );
     glEnd();


//BACK
   //  glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_QUADS);
       glNormal3f(0,0,-1);
       glVertex3f( X_MIN_SECOND,     Y_MIN_SECOND,     Z_MIN_SECOND);
       glVertex3f( X_MIN_SECOND,     Y_MAX_SECOND,     Z_MIN_SECOND);
       glVertex3f( X_MAX_SECOND,     Y_MAX_SECOND,     Z_MIN_SECOND);
       glVertex3f( X_MAX_SECOND,     Y_MIN_SECOND,     Z_MIN_SECOND);
     glEnd();

//TOP
     //glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_QUADS);
       glNormal3f(0,0,1);
       glVertex3f( X_MIN_SECOND,     Y_MAX_SECOND,    Z_MIN_SECOND);
       glVertex3f( X_MIN_SECOND,     Y_MAX_SECOND,    Z_MAX_SECOND );
       glVertex3f( X_MAX_SECOND,     Y_MAX_SECOND,    Z_MAX_SECOND );
       glVertex3f( X_MAX_SECOND,     Y_MAX_SECOND,    Z_MIN_SECOND);

    glEnd();

//BELOW
    //glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glVertex3f( X_MIN_SECOND,     Y_MIN_SECOND,    Z_MIN_SECOND );
      glVertex3f( X_MIN_SECOND,     Y_MIN_SECOND,    Z_MAX_SECOND );
      glVertex3f( X_MAX_SECOND,     Y_MIN_SECOND,    Z_MAX_SECOND );
      glVertex3f( X_MAX_SECOND,     Y_MIN_SECOND,    Z_MIN_SECOND );

    glEnd();

//LEFT
    //glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glVertex3f( X_MIN_SECOND,     Y_MIN_SECOND,    Z_MIN_SECOND );
      glVertex3f( X_MIN_SECOND,     Y_MIN_SECOND,    Z_MAX_SECOND );
      glVertex3f( X_MIN_SECOND,     Y_MAX_SECOND,    Z_MAX_SECOND );
      glVertex3f( X_MIN_SECOND,     Y_MAX_SECOND,    Z_MIN_SECOND );

    glEnd();

//RIGHT
    //glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_QUADS);
      glNormal3f(0,0,1);
      glVertex3f( X_MAX_SECOND,     Y_MIN_SECOND,    Z_MIN_SECOND );
      glVertex3f( X_MAX_SECOND,     Y_MIN_SECOND,    Z_MAX_SECOND );
      glVertex3f( X_MAX_SECOND,     Y_MAX_SECOND,    Z_MAX_SECOND );
      glVertex3f( X_MAX_SECOND,     Y_MAX_SECOND,    Z_MIN_SECOND );
glEnd();

//glRotatef(10.0, 1.0f, 1.0f, 1.0f);
}


