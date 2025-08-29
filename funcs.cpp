#include "funcs.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

void test_write_img(img& i1){
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

ray ray::operator+(const ray r)const {
         ray out(vec[0]+r.vec[0], vec[1]+r.vec[1], vec[2]+r.vec[2]);
         return out;
}
      
ray ray::operator-(const ray r)const {
         ray out(vec[0]+r.vec[0], vec[1]+r.vec[1], vec[2]+r.vec[2]);
         return out;
}

ray ray::operator*(const ray r)const {
        ray out(vec[1]*r.vec[2] - vec[2]*r.vec[1], out.vec[1] = vec[2]*r.vec[0] - vec[0]*r.vec[2], vec[0]*r.vec[1] - vec[1]*r.vec[0]);
        return out;
}

ray ray::operator*(const double d)const {
         ray out(vec[0]*d, vec[1]*d, vec[2]*d);
         return out;
}

double ray::operator/(const ray r)const {
         return vec[0]*r.vec[0] + vec[1]*r.vec[1] + vec[2]*r.vec[0];  
}

void ray::unit(){
         vec[0] /= mag;   
         vec[1] /= mag;   
         vec[2] /= mag;
         mag = 1;
         return;
}

bool plane::checkMeet(const ray r){
         if(r/n == 0) return false;
         ray vec_p1= r*((v[0]/n)/(r/n)), vec_p2;
         vec_p2 = vec_p1-v[3];
         vec_p1 = vec_p1-v[0];
         if(vec_p1/e1 > 0 && vec_p1/e2 >0 && vec_p2/e1 <0 && vec_p2/e2 <0){
            return true;
         }
         return false;
}



