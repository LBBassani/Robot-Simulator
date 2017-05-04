#ifndef ROBOT_H
#define ROBOT_H

class Robot
{
private:

    double L;

    double u1, u2;
    double v, omega;

    double x, y, theta;
public:

    Robot(double L, double x, double y, double theta);
    void draw(double rgb1[], double rgb2[]);
    void evolve(double dt);
    void inputControls(double u1Value, double u2Value);

};


#endif /* ROBOT_H */