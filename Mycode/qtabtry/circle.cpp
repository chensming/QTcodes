#include "circle.h"

Circle::Circle()
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
