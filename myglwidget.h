

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation1(int angle);
    void setYRotation1(int angle);
    void setZRotation1(int angle);

    void setXRotation2(int angle);
    void setYRotation2(int angle);
    void setZRotation2(int angle);

    void accel1(int x, int y, int z);
    void accel2(int x, int y, int z);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void draw_first();
    void draw_second();


    int xRot1;
    int yRot1;
    int zRot1;

    int xRot2;
    int yRot2;
    int zRot2;

    QPoint lastPos;
};

#endif // MYGLWIDGET_H

