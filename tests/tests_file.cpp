#include <bits/stdc++.h>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../extern/doctest.h"
#include "../source/engine/Vector.h"

TEST_CASE("0.0 - Vector Construction"){
    Vector v(2.0, 3.0);

    CHECK(v.x == 2.0);
    CHECK(v.y == 3.0);
}

TEST_CASE("0.1 - Vector Operations"){
    Vector v(3.0, 4.0);
    CHECK(v.Length() == 5.0);

    float l = v.Length();
    v.Normalize();
    CHECK(v.x == 0.6f);
    CHECK(v.y == 0.8f);
}

TEST_CASE("0.2.0 - Vector Maths - Assignment Operators"){
    Vector v(3.0, 4.0);

    Vector add_me(1.0, 2.0);
    v += add_me;
    CHECK(v.x == 4.0);
    CHECK(v.y == 6.0);

    Vector subtract_me(2.0, 3.0);
    v -= subtract_me;
    CHECK(v.x == 2.0);
    CHECK(v.y == 3.0);

    v *= 4.0;
    CHECK(v.x == 8.0);
    CHECK(v.y == 12.0);

    v/=2.0;
    CHECK(v.x == 4.0);
    CHECK(v.y == 6.0);
}

TEST_CASE("0.2.1 - Vector Maths - Vector Operators"){
    Vector v(2.0, 2.0);
    Vector u(3.0, 3.0);

    Vector added = v+u;
    CHECK(added.x == 5.0);
    CHECK(added.y == 5.0);

    Vector subtracted = u-v;
    CHECK(subtracted.x == 1.0);
    CHECK(subtracted.y == 1.0);

    Vector multiplied = v*2.0;
    CHECK(multiplied.x == 4.0);
    CHECK(multiplied.y == 4.0);

    Vector divided = u/3.0;
    CHECK(divided.x == 1.0);
    CHECK(divided.y == 1.0);
}


// TEST_CASE("1.0 - AABB Collision"){
//     Entity
// }