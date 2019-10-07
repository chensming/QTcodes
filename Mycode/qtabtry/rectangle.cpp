#include "rectangle.h"

rectangle::rectangle()
{

}

rectangle::rectangle(double l,double w)
{
    length = l;
    width = w;
}

 double rectangle::RectangleArea()
 {
     rectangleArea = length * width;
     return rectangleArea;
 }


