#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

#include "data.h"

struct Angle
{
    double x_;
    double y_;
    double z_;
};

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

public slots:

    void inputData(Acc*);

//signals:

private:
    void draw();

    void draw(char , double , double , double , double , double , double );
    //(char id, double x_min, double x_max, double y_min, double y_max, double z_min, double z_max,)
    Angle rotation[2];

  //  QPoint lastPos;
};

#endif // MYGLWIDGET_H

