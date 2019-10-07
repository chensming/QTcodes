#include "circle.h"

Circle::Circle(QObject *parent) : QObject(parent)
{

}


Circle::Circle(double Radius)
{
    circleRadius = Radius;
}

double Circle::CircleArea()
{
    circleArea = 3.14159 * circleRadius * circleRadius;
    return circleArea;
}
