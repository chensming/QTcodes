#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>

class Circle : public QObject
{
    Q_OBJECT
public:
    explicit Circle(QObject *parent = nullptr);
    Circle();
    Circle(double Radius);
    double CircleArea();


signals:

public slots:


private:
    double circleRadius;
    double circleArea;
};

#endif // CIRCLE_H
