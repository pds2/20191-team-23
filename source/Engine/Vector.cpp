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
Vector Vector::operator*(const float& a){
    return Vector(x*a, y*a);
}
Vector Vector::operator/(const float& a){
    return Vector(x/a, y/a);
}


bool Vector::operator==(const Vector& a){
    return x==a.x && y==a.y;
}


// Assignment operators
void Vector::operator+=(const Vector& a){
    x += a.x; y += a.y;
}
void Vector::operator-=(const Vector& a){
    x -= a.x; y -= a.y;
}
void Vector::operator*=(const float& a){
    x *= a; y *= a;
}
void Vector::operator/=(const float& a){
    x /= a; y /= a;
}