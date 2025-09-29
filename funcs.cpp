#include "funcs.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#define FP 5000

void test_write_img(Img& i1){
    int y=0;
    float a, b;
    for(int i = 0; i < i1.height(); i++){
       for(int j = 0; j < i1.width(); j++){
            a = i;
            a /= i1.height();
            a *= 255;
            b = j;
            b /= i1.width();
            b *= 255;
            i1.start()[y]=a;
            i1.start()[y+1]=b;
            i1.start()[y+2]=255-a;
            if(i1.chan()==4) {
                i1.start()[y+3]=0;
                y++;
            }
            y +=3;
       } 
    }
    stbi_write_png("1.png", i1.width(), i1.height(), i1.chan(), i1.start(), i1.width()*i1.chan());
    return;
}

void test_plane_img(Img& i1, Plane& p){
   int t=0;
   for(int i = 0; i < i1.height(); i++){
      for(int j = 0; j < i1.width(); j++){
         if(p.checkMeet(Ray((double)j - (double)i1.width()/2, (double)i1.height()/2-(double)i, FP))){
            i1.start()[t++] = p.red();
            i1.start()[t++] = p.green();
            i1.start()[t++] = p.blue();
            if(i1.chan()==4)i1.start()[t++] = p.alpha();
            std::cout << "i, j: " << i << ", " << j << std::endl;
         }
         else{
            i1.start()[t++] = 0;  
            i1.start()[t++] = 0;
            i1.start()[t++] = 0;
            if(i1.chan()==4)i1.start()[t++] = 255;
         }
      }
   }

   stbi_write_png("1.png", i1.width(), i1.height(), i1.chan(), i1.start(), i1.width()*i1.chan());
   return;
}

void test_sphere_img(Img& i1, Sphere& s){
   int t=0;
   for(int i = 0; i < i1.height(); i++){
      for(int j = 0; j < i1.width(); j++){
         if(s.checkMeet(Ray((double)j - (double)i1.width()/2, (double)i1.height()/2-(double)i, FP))){
            i1.start()[t++] = s.red();
            i1.start()[t++] = s.green();
            i1.start()[t++] = s.blue();
            if(i1.chan()==4)i1.start()[t++] = s.alpha();
            std::cout << "i, j: " << i << ", " << j << std::endl;
         }
         else{
            i1.start()[t++] = 0;  
            i1.start()[t++] = 0;
            i1.start()[t++] = 0;
            if(i1.chan()==4)i1.start()[t++] = 255;
         }
      }
   }

   stbi_write_png("1.png", i1.width(), i1.height(), i1.chan(), i1.start(), i1.width()*i1.chan());
   return;
}

void test_scenery_img(Img& i1, Scenery& v){
   int t=0;
   Ray temp;
   Color c;
   bool f;
   for(int i = 0; i < i1.height(); i++){
      for(int j = 0; j < i1.width(); j++){
         temp = Ray((double)j - (double)i1.width()/2, (double)i1.height()/2-(double)i, FP);
         f = v.checkMeet(temp, c);
         if(f){   
            i1.start()[t++] = c.red();
            i1.start()[t++] = c.green();
            i1.start()[t++] = c.blue();
            if(i1.chan()==4)i1.start()[t++] = c.alpha();
            std::cout << "i, j: " << i << ", " << j << std::endl;
         }
         else{
            i1.start()[t++] = 0;  
            i1.start()[t++] = 0;
            i1.start()[t++] = 0;
            if(i1.chan()==4)i1.start()[t++] = 255;
         }
      }
   }

   stbi_write_png("1.png", i1.width(), i1.height(), i1.chan(), i1.start(), i1.width()*i1.chan());
   return;
}

Ray Ray::operator+(const Ray r)const {
         Ray out(vec[0]+r.vec[0], vec[1]+r.vec[1], vec[2]+r.vec[2]);
         return out;
}

Ray Ray::operator-(const Ray r)const {
         Ray out(vec[0]-r.vec[0], vec[1]-r.vec[1], vec[2]-r.vec[2]);
         return out;
}

Ray Ray::operator*(const Ray r)const {
        return Ray(vec[1]*r.vec[2] - vec[2]*r.vec[1], vec[0]*r.vec[2] - vec[2]*r.vec[0], vec[1]*r.vec[0] - vec[0]*r.vec[/*  */1]);
}

Ray Ray::operator*(const double d)const {
         Ray out(vec[0]*d, vec[1]*d, vec[2]*d);
         return out;
}

double Ray::operator/(const Ray r)const {
         return vec[0]*r.vec[0] + vec[1]*r.vec[1] + vec[2]*r.vec[2];  
}

double& Ray::operator[](const int i){
   if(i<0) return vec[(-i)%3];
   return vec[i%3];
}

void Ray::unit(){
   Ray::Mag();       
   vec[0] /= mag;   
   vec[1] /= mag;   
   vec[2] /= mag;
   mag = 1;
   return;
}

void Ray::print() const{
   //std::cout << "(" << vec[0] <<", " << vec[1] << ", " << vec[2] << ")" << std::endl;
   std::cout << vec[0] << " " << vec[1] << " "  << vec[2] << std::endl;
}

double Ray::Mag(){
   mag = vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2];
   mag = sqrt(mag);
   return mag;
}

Plane::Plane(Ray v1, Ray v2, Ray v3, double k){
   v[0] = Ray(v1[0]*k, v1[1]*k, v1[2]);
   v[1] = Ray(v2[0]*k, v2[1]*k, v2[2]);
   v[2] = Ray(v3[0]*k, v3[1]*k, v3[2]);
   v[3] = v[1]+v[2]-v[0];
   e1 = v[1] - v[0];
   e2 = v[2] - v[0];
   n = e1*e2;
   n.unit();
   assert (n/e1<3e-6);
} 

bool Plane::checkMeet(const Ray r){
   if(r/n == 0) return false;
   double k =(v[0]/n)/(r/n);
   if(k<1 || k > 10000) return false;
   Ray pointOnPlane = r*k;
   assert ((pointOnPlane - v[0])/n < 1e-6);
   Ray pOP_v1 = pointOnPlane-v[0], pOP_v3=pointOnPlane-v[3];
   if (pOP_v1/e1 >= 0 && pOP_v1/e2 >= 0 && pOP_v3/e1 <= 0 && pOP_v3/e2 <= 0) return true;
   return false;
}

void Plane::print()const{
   std::cout << "Plane: " << std::endl;
   v[0].print();
   v[1].print();
   v[2].print();
   v[3].print();
   n.print();
   e1.print();
   e2.print();
   std::cout << std::endl;
}

bool Sphere::checkMeet(const Ray r){
   Ray v = r;
   v.unit();
   double dot = v/center;
   if(dot >= 0 && dot*dot >= center/center - radius*radius){
      return true;
   }
   return false;
}

bool Sphere::checkMeet(const Ray r, double& mul){
   mul = 0;
   Ray v = r;
   v.unit();
   double dot = v/center, del;
   del = dot*dot - center/center + radius*radius; 
   if(del >= 0){
      del = sqrt(del);
      mul = dot - del;
      if(mul <= 0) mul += del + del;
      return true;
   }
   return false;
}

bool Scenery::checkMeet(const Ray r, Color& c){
   c = Color(0, 0, 0);
   double min = 1e15, m;
   bool f=false;
   for(int i = 0; i < spheres.size(); i++){
      if(spheres[i].checkMeet(r, m)) {
         f=true; 
         if(m < min){
            c = spheres[i].color();
            min = m;
         }
      }
   }
   return f;
}

