#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>

class img{
   public:
      int h,w,c;
      size_t s;
      uint8_t *p = NULL;
      
      img(int w1, int h1, int c1): h{h1}, w{w1}, c{c1}, s{(size_t)w1*h1*c1}{p = new uint8_t[s];} 
      //void make_pimg(const char* fname);
};

class color{
   public:
      uint8_t c[3];

      color(uint8_t c1,uint8_t c2,uint8_t c3): c{c1, c2, c3}{}      
      color(const color& c1): c{c1.c[0], c1.c[1], c1.c[2]}{}
};

class ray{
   public:
      double vec[3];
      double mag;

      ray(): vec{0, 0, 0}, mag{0}{}
      ray(double d1, double d2, double d3): vec{d1, d2, d3}{mag = sqrt(d1*d1+d2*d2+d3*d3);}
      ray(const ray& r): vec{r.vec[0], r.vec[1], r.vec[2]}, mag{r.mag}{}
      ray operator+(const ray r)const;      
      ray operator-(const ray r)const;
      ray operator*(const ray r)const;
      ray operator*(const double d)const;
      double operator/(const ray r)const;
      void unit();
};

class plane{
   public:
      ray v[4];
      ray n, e1, e2;
      color c;

      plane(ray v1, ray v2, ray v3, color c1):v{v1, v2, v3, v3+v2-v1}, e1{v2-v1}, e2{v3-v1}, c{c1}{n = (e1*e2); n.unit();} 
      bool checkMeet(const ray r);
};

/*void img::make_pimg(const char* fname){
   stbi_write_png(fname, w, h, c, p, w*c);
   return;
}*/

void test_write_img(img& i1);
