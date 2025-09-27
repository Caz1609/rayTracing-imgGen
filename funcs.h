#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <cassert>

class Img{
   private:
      int h,w,c;
      size_t s;
      uint8_t *p = NULL;
   public:
      Img(int w1, int h1, int c1): h{h1}, w{w1}, c{c1}, s{(size_t)w1*h1*c1}{p = new uint8_t[s];} 
      uint8_t*& start(){return p;}
      int height(){return h;}
      int width(){return w;}
      int chan(){return c;}
      size_t size(){return s;}
};

class Ray{
   private:
      double vec[3];
      double mag;
   public:
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
      void print() const;
      double Mag();
};

class Plane{
   private:
      Ray v[4];
      Ray n, e1, e2;
   public:
      Plane(Ray v1, Ray v2, Ray v3):v{v1, v2, v3, v3+v2-v1}, e1{v2-v1}, e2{v3-v1}{n = (e1*e2);n.unit();assert(n/e1<3e-6);} 
      Plane(Ray v1, Ray v2, Ray v3, Ray v4):v{v1, v2, v3, v4}, e1{v2-v1}, e2{v3-v1}{n = (e1*e2);n.unit();assert(n/e1<3e-6);} 
      Plane(Ray v1, Ray v2, Ray v3, double k); 
      bool checkMeet(const Ray r);
      void print()const;
};

class Sphere{
   private:
      Ray center;
      double radius;
   public:
      Sphere(Ray v1, double r):center{v1}, radius{r}{}
      bool checkMeet(const Ray r);
};

void test_plane_img(Img& i1, Plane& p);
void test_write_img(Img& i1);
void test_sphere_img(Img& i1, Sphere& s);

