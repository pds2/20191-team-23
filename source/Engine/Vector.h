#ifndef VECTOR_H
#define VECTOR_H

struct Vector{
    Vector();
    Vector(float a, float b);

    Vector operator+(const Vector& a);
    Vector operator-(const Vector& a);
    Vector operator*(const float& a);
    Vector operator/(const float& a);

    bool operator==(const Vector& a);

    // Assignment operators
    void operator+=(const Vector& a);
    void operator-=(const Vector& a);
    void operator*=(const float& a);
    void operator/=(const float& a);

    float x;
    float y;
};

#endif //!VECTOR_H