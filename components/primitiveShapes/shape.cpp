#include "shape.h"
#include <iostream>
using namespace std;

/********************* Color Struct ********************/

color::color() : red(0.0), green(0.0), blue(0.0), alpha(1.0) {
}

color::color(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a) {
}

color::color(double r, double g, double b) : red(r), green(g), blue(b), alpha(1.0) {
}

ostream& operator << (ostream& outs, const color &c) {
    outs << "(" << c.red << ", " << c.green << ", " << c.blue << ")";
    return outs;
}

/********************* Point Struct ********************/

point2D::point2D() : x(0), y(0) {}

point2D::point2D(double x, double y) : x(x), y(y) {}

ostream& operator << (ostream& outs, const point2D &p) {
    outs << "(" << p.x << ", " << p.y << ")";
    return outs;
}

/********************* Shape Class *********************/

Shape::Shape() : fill({0.0, 0.0, 0.0}), center({0, 0}) {
}

color Shape::getColor() const {
    return fill;
}

double Shape::getOpacity() const {
    return fill.alpha;
}

point2D Shape::getCenter() const {
    return center;
}

double Shape::getCenterX() const {
    return center.x;
}

double Shape::getCenterY() const {
    return center.y;
}

void Shape::setColor(color c) {
    fill = c;
}

void Shape::setColor(double r, double g, double b, double a) {
    fill = {r, g, b, a};
}

void Shape::setOpacity(double a) {
    fill.alpha = a;
}

void Shape::setCenter(point2D center) {
    this->center = center;
}

void Shape::setCenter(double x, double y) {
    center = {x, y};
}

void Shape::setCenterX(double x) {
    center.x = x;
}

void Shape::setCenterY(double y) {
    center.y = y;
}

