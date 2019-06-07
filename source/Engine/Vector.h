#ifndef VECTOR_H
#define VECTOR_H

struct Vector{
    Vector();
    Vector(float a, float b);

    Vector operator+(const Vector& a);
    Vector operator-(const Vector& a);
    Vector operator*(const int& a);
    Vector operator/(const int& a);
    bool operator==(const Vector& a);

    float x;
    float y;
};

#endif //!VECTOR_H