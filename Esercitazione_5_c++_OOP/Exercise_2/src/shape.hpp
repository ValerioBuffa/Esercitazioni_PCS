#ifndef __SHAPE_H
#define __SHAPE_H

#include <iostream>
#include "Eigen/Eigen"

using namespace std;

namespace ShapeLibrary {

  class Polygon {
    Eigen::MatrixXd vertices;

    public:
        Polygon() = default;
        Polygon(Eigen::MatrixXd& points) : vertices(points) {}

        string Show();
        double Area();
  };


  class Triangle : public Polygon
  {
    bool flag = false;
    double base, height;

    public:
        Triangle() = default;
        Triangle(double& base, double& height) : base(base), height(height) {
            flag = true;
        }
        Triangle(Eigen::MatrixXd& points) : Polygon(points) {}

        string Show();
        double Area();
  };


  class TriangleEquilateral final : public Triangle
  {
    bool flag = false;
    double edgeLength;

    public:
        TriangleEquilateral() = default;
        TriangleEquilateral(double& edgeLength) : edgeLength(edgeLength) {
            flag = true;
        }
        TriangleEquilateral(double& base, double& height) : Triangle(base, height) {}

        string Show();
        double Area();
  };

  class Quadrilateral : public Polygon
  {
    bool flag = false;
    Polygon t1, t2;

    public:
        Quadrilateral() = default;
        Quadrilateral(Triangle& t1, Triangle& t2) : t1(t1), t2(t2) {
            flag = true;
        }
        Quadrilateral(Eigen::MatrixXd& points) : Polygon(points) {}

        string Show();
        double Area();
  };

  class Rectangle : public Quadrilateral
  {
    unsigned int flag = 0;
    double base, height;

    public:
        Rectangle() = default;
        Rectangle(Eigen::MatrixXd& points) : Quadrilateral(points) {}
        Rectangle(Triangle& t1, Triangle& t2) : Quadrilateral(t1, t2) {
            flag = 1;
        }
        Rectangle(double& base, double& height) : base(base), height(height) {
            flag = 2;
        }

        string Show();
        double Area();
  };

  class Square final: public Rectangle
  {
    unsigned int flag = 0;
    double edgeLength;

    public:
        Square() = default;
        Square(Eigen::MatrixXd& points) : Rectangle(points) {}
        Square(Triangle& t1, Triangle& t2) : Rectangle(t1, t2) {
            flag = 1;
        }
        Square(double& base, double& height) : Rectangle(base, height){
            flag = 2;
        }
        Square(double& edgeLength) : edgeLength(edgeLength) {
            flag = 3;
        }

        string Show();
        double Area();
  };
}

#endif // __SHAPE_H
