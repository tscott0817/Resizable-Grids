#ifndef CHORDCHART_SHAPE_H
#define CHORDCHART_SHAPE_H
#include <math.h>
#include <string>

struct color {
    double red;
    double green;
    double blue;
    double alpha;

    /* Constructors */
    color();
    color(double r, double g, double b);
    color(double r, double g, double b, double a);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const color &c);
};

struct point2D {
    double x;
    double y;

    /* Constructors */
    point2D();
    point2D(double x, double y);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const point2D &p);
};

class Shape {
protected:
    color fill;
    point2D center;

public:
    /* Constructors */
    Shape();

    /* Destructor */
    virtual ~Shape() = default;

    /* Getters */
    color getColor() const;
    double getOpacity() const;
    point2D getCenter() const;
    double getCenterX() const;
    double getCenterY() const;
    virtual double getLeftX() const = 0;
    virtual double getRightX() const = 0;
    virtual double getTopY() const = 0;
    virtual double getBottomY() const = 0;

    /* Setters */
    void setColor(color c);
    void setColor(double r, double g, double b, double a);
    void setOpacity(double a);
    void setCenter(point2D center);
    void setCenter(double x, double y);
    void setCenterX(double x);
    void setCenterY(double y);

    virtual void draw() const = 0;
};
#endif //COF_SHAPE_H
