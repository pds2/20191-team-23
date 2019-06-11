#ifndef VECTOR_H
#define VECTOR_H

struct Vector{
    Vector();
    Vector(float a, float b);

    //returns vector size (sqrt(x*x+y*y)) 
    float Length();
    //normalizes the vector (divides x and y by lenght)
    void Normalize(); 
    //returns a normelized copy of the vector
    Vector Normalized();

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