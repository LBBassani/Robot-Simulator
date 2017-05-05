#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

const double DEFAULT_FRONT_COLOR[] = {1.0, 0.07831, 0.576471};
const double DEFAULT_BACK_COLOR[]  = {0.0, 0.0, 1.0};

using namespace std;

class Robot
{
private:

    int id;
    double L;

    double u1, u2;
    double v, omega;

    double x, y, theta;
    double frontColor[3];
    double backColor[3];

public:

    Robot(int id, double L, double x, double y, double theta, double *colors = nullptr,
                                                                         bool customColors = false);
    void draw();
    void evolve(double dt);
    void inputControls(double u1Value, double u2Value);
    int getId();
    vector<double> getState();
};


#endif /* ROBOT_H */