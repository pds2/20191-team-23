#ifndef VECTOR_H
#define VECTOR_H

struct Vector{
    Vector();
    Vector(float a, float b);

    float Length(); //retorna o tamanho do vetor, aka sqrt(x*x+y*y
    void Normalize(); //normaliza o vetor, aka divide x e y pelo length
    Vector Normalized(); //retorna uma copia do vetor soq normalizado

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