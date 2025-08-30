#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>

class Img{
   public:
      int h,w,c;
      size_t s;
      uint8_t *p = NULL;
      
      Img(int w1, int h1, int c1): h{h1}, w{w1}, c{c1}, s{(size_t)w1*h1*c1}{p = new uint8_t[s];} 
      //void make_pimg(const char* fname);
};

class Color{
   public:
      uint8_t c[3];

      Color(uint8_t c1,uint8_t c2,uint8_t c3): c{c1, c2, c3}{}      
      Color(const Color& c1): c{c1.c[0], c1.c[1], c1.c[2]}{}
      uint8_t& operator[](int i){return c[i%3];}
};

class Ray{
   public:
      double vec[3];
      double mag;

      Ray(): vec{0, 0, 0}, mag{0}{}
      Ray(double d1, double d2, double d3): vec{d1, d2, d3}{mag = sqrt(d1*d1+d2*d2+d3*d3);}
      Ray(const Ray& r): vec{r.vec[0], r.vec[1], r.vec[2]}, mag{r.mag}{}
      Ray operator+(const Ray r)const;      
      Ray operator-(const Ray r)const;
      Ray operator*(const Ray r)const;
      Ray operator*(const double d)const;
      double& operator[](const int);
      double operator/(const Ray r)const;
      void unit();
      void print();
      void Mag();
};

class Plane{
   public:
      Ray v[4];
      Ray n, e1, e2;
      Color col;

      Plane(Ray v1, Ray v2, Ray v3, Color c1):v{v1, v2, v3, v3+v2-v1}, e1{v2-v1}, e2{v3-v1}, col{c1}{n = (e1*e2); n.unit();} 
      bool checkMeet(const Ray r);
      void print();
};

void test_plane_img(Img& i1, Plane& p);
void test_write_img(Img& i1);

