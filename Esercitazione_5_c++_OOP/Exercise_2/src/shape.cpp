#include "shape.hpp"
#include <math.h>

namespace ShapeLibrary {

    string Polygon::Show(){
        return "Polygon: " + to_string(Area());
    }

    double Polygon::Area(){
        double sum = 0;

        for(unsigned int i = 0; i < vertices.cols() - 1; i++)
            sum += vertices(0,i)*vertices(1,i+1) - vertices(0,i+1)*vertices(1,i);

        sum += vertices(0, vertices.cols() - 1)*vertices(1,0) - vertices(0,0)*vertices(1, vertices.cols() - 1);

        return abs(sum)/2;
    }

    string Triangle::Show(){
        if(flag)
            return "Triangle: " + to_string(Area());
        else
            return "Triangle As Polygon: " + to_string(Polygon::Area());
    }

    double Triangle::Area(){
        return base*height/2;
    }

    string TriangleEquilateral::Show(){
        if(flag)
            return "TriangleEquilateral: " + to_string(Area());
        else
            return "TriangleEquilateral As Triangle: " + to_string(Triangle::Area());
    }

    double TriangleEquilateral::Area(){
        return pow(edgeLength, 2)*sqrt(3)/4;
    }

    string Quadrilateral::Show(){
        if(flag)
            return "Quadrilateral: " + to_string(Area());
        else
            return "Quadrilateral As Polygon: " + to_string(Polygon::Area());
    }

    double Quadrilateral::Area(){
        return t1.Area() + t2.Area();
    }

    string Rectangle::Show(){
        if(flag == 0)
            return "Rectangle As Polygon: " + to_string(Polygon::Area());
        else if(flag == 1)
            return "Rectangle As Quadrilateral: " + to_string(Quadrilateral::Area());
        else
            return "Rectangle: " + to_string(Area());
    }

    double Rectangle::Area(){
        return base*height;
    }

    string Square::Show(){
        if(flag == 0)
            return "Square As Polygon: " + to_string(Polygon::Area());
        else if(flag == 1)
            return "Square As Quadrilateral: " + to_string(Quadrilateral::Area());
        else if(flag == 2)
            return "Square As Rectangle: " + to_string(Rectangle::Area());
        else
            return "Square: " + to_string(Area());
    }

    double Square::Area(){
        return pow(edgeLength, 2);
    }
}
