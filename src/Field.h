#ifndef FIELD_H
#define FIELD_H

class Field{
private:
    double xLen;
    double yLen;
    double xC;
    double yC;

public:
    Field(double xSize = 1.5, double ySize = 1.3, double xCenter = 0.0, double yCenter = 0.0);
    void draw();
};

#endif /* FIELD_H */