#ifndef CHORDCHART_RECT_H
#define CHORDCHART_RECT_H

#include "shape.h"

struct dimensions {
    double width;
    double height;

    /* Constructors */
    dimensions();
    dimensions(double w, double h);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const dimensions &d);
};

struct point {
    int x;
    int y;
};

class Rect : public Shape {
private:
    dimensions size;
public:
    /* Constructors */
    Rect();

    /* Destructor */
    virtual ~Rect() = default;

    /* Getters */
    dimensions getSize() const;
    double getWidth() const;
    double getHeight() const;
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    /* Setters */
    void setSize(dimensions size);
    void setSize(double width, double height);
    void setWidth(double width);
    void setHeight(double height);
    void changeSize(double deltaWidth, double deltaHeight);
    void changeWidth(double delta);
    void changeHeight(double delta);

    void hover();
    void pressDown();
    void release();
    void setHoverFill(color hoverColor);

    /* Draw */
    void draw() const override;

};
#endif //CHORDCHART_RECT_H
