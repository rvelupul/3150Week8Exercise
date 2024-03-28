#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "double_vector.h"

TEST_CASE("Testing dot_product function") {
    double_vector a(1, 2);
    double_vector b(3, 4);

    CHECK(dot_product(a, b) == 11); 
    CHECK_EQ(dot_product(a, a), 5); 
    CHECK_EQ(dot_product(b, b), 25); 
}

TEST_CASE("Testing magnitude function") {
    double_vector a(3.0, 4.0);
    double_vector b(1.0, 1.0);

    REQUIRE(magnitude(a) == 5.0); 
    REQUIRE(magnitude(b) == sqrt(2.0)); 
    WARN(magnitude(a) != 4.0); 
}

TEST_CASE("Testing cosine_distance function") {
    double_vector a(1, 0);
    double_vector b(0, 1);
    double_vector c(1, 1);
    double_vector d(1, 1);

    CHECK_FALSE(cosine_distance(a, b) == 0); 
    CHECK(cosine_distance(a, a) == 0); 

    double_vector e(1, 0);
    double_vector f(1, 1);
    double cos_angle = dot_product(e, f) / (magnitude(e) * magnitude(f));
    REQUIRE(cosine_distance(e, f) == acos(cos_angle));
}

TEST_CASE("Testing cosine_distance function with floating point vectors") {
    double_vector a(1.5, 2.5);
    double_vector b(2.0, 3.0);

    double dot_prod_ab = dot_product(a, b);
    double mag_a = magnitude(a);
    double mag_b = magnitude(b);
    double expected_cosine = dot_prod_ab / (mag_a * mag_b);
    double expected_distance = acos(expected_cosine);

    CHECK(cosine_distance(a, b) == doctest::Approx(expected_distance).epsilon(0.01));
}

TEST_CASE("cosine_distance of a vector with itself") {
    double_vector v(3.5, 4.5);  

    CHECK(cosine_distance(v, v) == doctest::Approx(0.0));
}


TEST_CASE("cosine_distance with large magnitude difference") {
    double_vector small(0.001, 0.001);
    double_vector large(1000.0, 1000.0);

    double expected_cos = dot_product(small, large) / (magnitude(small) * magnitude(large));
    CHECK(cosine_distance(small, large) == doctest::Approx(acos(expected_cos)));
}

