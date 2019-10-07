#ifndef RECTANGLE_H
#define RECTANGLE_H


class rectangle
{
public:
    rectangle();
    rectangle(double l,double w);
    double RectangleArea();

private:
    double length;
    double width;
    double rectangleArea;
};

#endif // RECTANGLE_H
