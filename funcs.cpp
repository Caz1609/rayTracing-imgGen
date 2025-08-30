#include "funcs.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#define FP 10

void test_write_img(Img& i1){
    int y=0;
    float a, b;
    for(int i = 0; i < i1.h; i++){
       for(int j = 0; j < i1.w; j++){
            a = i;
            a /= i1.h;
            a *= 255;
            b = j;
            b /= i1.w;
            b *= 255;
            i1.p[y]=a;
            i1.p[y+1]=b;
            i1.p[y+2]=255-a;
            if(i1.c==4) {
                i1.p[y+3]=0;
                y++;
            }
            y +=3;
       } 
    }
    stbi_write_png("1.png", i1.w, i1.h, i1.c, i1.p, i1.w*i1.c);
    return;
}

void test_plane_img(Img& i1, Plane& p){
   int t=0;
   bool f;
   for(int i = 0; i < i1.h; i++){
      for(int j = 0; j < i1.w; j++){
         if(f=p.checkMeet(Ray((double)j - (double)i1.w/2, (double)i1.h/2-(double)i, FP))){
            i1.p[t] = p.col[0];
            i1.p[t+1] = p.col[1];
            i1.p[t+2] = p.col[2];
         }
         t+=3;
         if(i1.c==4)i1.p[t++] = 0;
         if(f == 1){
            std::cout << "i, j: " << i << ", " << j << std::endl;
         }
      }
   }

   stbi_write_png("1.png", i1.w, i1.h, i1.c, i1.p, i1.w*i1.c);
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
        return Ray(vec[1]*r.vec[2] - vec[2]*r.vec[1], vec[2]*r.vec[0] - vec[0]*r.vec[2], vec[0]*r.vec[1] - vec[1]*r.vec[0]);
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

void Ray::Mag(){
   mag = vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2];
   mag = sqrt(mag);
   return;
}

Plane::Plane(Ray v1, Ray v2, Ray v3, Color c1, double k): col{c1}{
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
