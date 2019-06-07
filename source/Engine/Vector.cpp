#include "Vector.h"

Vector::Vector(){
    x = 0.0f;
    y = 0.0f;
}

Vector::Vector(float a, float b){
    x = a;
    y = b;
}

Vector Vector::operator+(const Vector& a){
    return Vector(x+a.x, y+a.y);
}
Vector Vector::operator-(const Vector& a){
    return Vector(x-a.x, y-a.y);
}
Vector Vector::operator*(const int& a){
    return Vector(x*a, y*a);
}
Vector Vector::operator/(const int& a){
    return Vector(x/a, y/a);
}

bool Vector::operator==(const Vector& a){
    return x==a.x && y==a.y;
}