#include <cmath>
#include <iostream>
#include "Vec3.h"

using namespace std;

typedef struct resultado {
    float intersecao;
    bool interceptou;
} resultado;

class Point {
  public:
    float x;
    float y;
    float z;

    Point(const Point&);
    Point(float, float, float);
    void plus(const Vec3&);

    Point() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    const Point& operator = (const Point& p) {
        x = p[0];
        y = p[1];
        z = p[2];

        return *this;
    }

    const Vec3 operator - (const Point& p) const {
        Vec3 v;
        float x = this->x - p[0];
        float y = this->y - p[1];
        float z = this->z - p[2];
        v = Vec3(x, y, z);

        return v;
    }

    float operator [] (short unsigned int index) const {
        switch(index % 3) {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            case 2:
                return z;
                break;
            default:
                break;
        }
    }
};

Point::Point (const Point& p) {
    x = p.x;
    y = p.y;
    z = p.z;
};

Point::Point (float cx, float cy, float cz) {
    x = cx;
    y = cy;
    z = cz;
};

void Point::plus (const Vec3& v) {
    x += v[0];
    y += v[1];
    z += v[2];
};


class Light {
public:
    Point center;
    Vec3 color;
    Light(Point, Vec3);
};

Light::Light(Point lcenter, Vec3 lcolor) : center(lcenter), color(lcolor) {}

class Material {
public:
    Vec3 env_material;
    Vec3 dif_material;
    Vec3 spe_material;
    Material(Vec3, Vec3, Vec3);

    Material(){
        env_material = Vec3();
        dif_material = Vec3();
        spe_material = Vec3();
    }

    const Material& operator = (const Material& m) {
        this->env_material = m.env_material;
        this->dif_material = m.dif_material;
        this->spe_material = m.spe_material;

        return *this;
    }

    Vec3 colorEnviroment(Light l) {
        return this->env_material * l.color;
    }

    Vec3 colorDiffuse(Light l, Vec3 normal, Vec3 source) {
        Vec3 normalUni = Vec3::normalize(normal);
        Vec3 sourceUni = Vec3::normalize(source);

        float cosineNormalFonte =Vec3::dot(normalUni, sourceUni);

        if(cosineNormalFonte < 0)
            return Vec3();
        else
            (this->dif_material * l.color) * cosineNormalFonte;
    }

    Vec3 corSpecular(Light l, Vec3 normal, Vec3 observer, Vec3 source) {

        Vec3 normalUni = Vec3::normalize(normal);
        Vec3 sourceUni = Vec3::normalize(source);
        Vec3 observerUni = Vec3::normalize(observer);

        Vec3 reflected = normalUni * (2 * (Vec3::dot(sourceUni, normalUni)))  - sourceUni;

        if(Vec3::dot(reflected, observerUni) < 0)
            return Vec3();
        else
            return (this->spe_material * l.color) *  pow((Vec3::dot(reflected, observerUni)), 0.6 * 128); // Com índice de espelhamento igual a 1.
    }
};

Material::Material(Vec3 envMaterial, Vec3 difMaterial, Vec3 speMaterial)
    : env_material(envMaterial), dif_material(difMaterial), spe_material(speMaterial) {}

//Material::Material()
//    : env_material(Vec3(0.0f, 0.0f, 0.0f)), dif_material(Vec3(0.0f, 0.0f, 0.0f)), spe_material(Vec3(0.0f, 0.0f, 0.0f)) {}


class Sphere {
public:
    Point center;
    float radius;
    Material material;
    Sphere(Point, float);
    Sphere(Point, float, const Material&);
    float checkInterception(bool&, Vec3, Point, const bool&);
};

Sphere::Sphere(Point pcenter, float sradius, const Material& smaterial) 
: center(pcenter), material(smaterial.env_material, smaterial.dif_material, smaterial.spe_material) {
    radius = sradius;
};

Sphere::Sphere(Point pcenter, float sradius) 
: center(pcenter), material() {
    radius = sradius;
};

float Sphere::checkInterception(bool& intercept, Vec3 V, Point O, const bool& isShadow = false) {
    // Checking if the ball is intercepted by ray
    // This check uses the square equation delta
    float alpha = Vec3::dot(V, V);

    Vec3 Wshadow(center.x - O.x, center.y - O.y, center.z - O.z);
    Vec3 WNonShadow(-center.x, -center.y, -center.z);
    Vec3 W = isShadow ? Wshadow : WNonShadow;

    float beta = 2 * Vec3::dot(V, W);

    float gamma = Vec3::dot(W, W) - radius * radius;

    // Calculating the delta from 'alpha', 'beta' and 'gamma';
    float delta = beta * beta - 4 * alpha * gamma;

    // Scalar that stretch the 'V' vector from camera to intercepted point
    float t_int = 0;
    if (isShadow) {
        t_int = max((-beta + sqrt(delta)) / (2 * alpha), (-beta - sqrt(delta)) / (2 * alpha));
    } else {
        t_int = min((-beta + sqrt(delta)) / (2 * alpha), (-beta - sqrt(delta)) / (2 * alpha));
    }

    intercept = delta >= 0;

    return t_int;
}

class Triangle {
  public:
    Point vertex1;
    Point vertex2;
    Point vertex3;
    bool visible;
    Material material;

    Triangle() {}

    Triangle(Point& v1, Point& v2, Point& v3) {
        vertex1 = v1;
        vertex2 = v2;
        vertex3 = v3;
        visible = true;
        material = Material();
    }

    Triangle(Point& v1, Point& v2, Point& v3, Material m) {
        vertex1 = v1;
        vertex2 = v2;
        vertex3 = v3;
        material = m;
        visible = true;
    }

    Point operator [] (short unsigned int index) const {
       if (index == 1) return this->vertex1;
       if (index == 2) return this->vertex2;
       if (index == 3) return this->vertex3;
    }

    void setVertex(unsigned short int t, Point& p) {
        if(t == 1) {
            this->vertex1 = p;
        }

        if(t == 2) {
            this->vertex2 = p;
        }

        if (t==3) {
            this->vertex3 = p;
        }
    }

    Vec3 findNormal(void) {
        Vec3 edge1 = (this->vertex2 - this->vertex1);
        Vec3 edge2 = (this->vertex3 - this->vertex1);

        return Vec3::cross(edge1, edge2);
    }

    //V é o vetor que parte do observador para centro do pixel. 
    resultado intersectionTriangle(Vec3 v, Point O) {
        resultado r = {false, 0};

        Vec3 normalTriangle = this->findNormal();
        Vec3 normalTriangleUni = Vec3::normalize(normalTriangle);

        double productNormalRadius = Vec3::dot(v, normalTriangleUni); //Produto escalar do vetor normal com o vetor v

        //Checar se raio intercepta o plano que contém o triângulo
        if(productNormalRadius == 0) { // Raio perpendicular à normal do plano 
            r.interceptou = false;
            r.intersecao = 0;
            return r;
        } else {
            Vec3 sourceVertex = this->vertex1 - O; //Vetor da origem da câmera para um dos vértices do triângulo (neste caso, o primeiro)
            float tIntersection = Vec3::dot(sourceVertex, normalTriangleUni) / productNormalRadius; 

            if (tIntersection < 0) { //O objeto está atrás do observador
                r.interceptou = false;
                r.intersecao = 0;
                return r;
            } 

            //Checar se ponto encontrado está dentro do triângulo.

            Vec3 v_aux = v * tIntersection;
            Vec3 sourceToPoint(O.x + v_aux[0], O.y + v_aux[1], O.z + v_aux[2]);
            Point pointIntersection(sourceToPoint[0], sourceToPoint[1], sourceToPoint[2]); //Esta linha foi necessária para transformar o vetor posição do ponto de interseção em um ponto.

            Vec3 edge1 = this->vertex2 - this->vertex1; //Vetor do vertex1 para o vertex2
            Vec3 edge2 = this->vertex3 - this->vertex2; //Vetor do vertice 2 para o vertice 3
            Vec3 edge3 = this->vertex1 - this->vertex3; //Vetor do vertice 3 para o vertice 1

            Vec3 vertex1Point = pointIntersection - this->vertex1; //Vetor do vértice 1 para o ponto de interseção
            Vec3 vertex2Point = pointIntersection - this->vertex2; //Vetor do vértice 2 para o ponto de interseção
            Vec3 vertex3Point = pointIntersection - this->vertex3; //Vetor do vértice 3 para o ponto de interseção

            Vec3 edgeVertex1 = Vec3::cross(edge1, vertex1Point);
            Vec3 edgeVertex2 = Vec3::cross(edge2, vertex2Point);
            Vec3 edgeVertex3 = Vec3::cross(edge3, vertex3Point);

            float dot1 = Vec3::dot(edgeVertex1, normalTriangleUni);
            float dot2 = Vec3::dot(edgeVertex2, normalTriangleUni);
            float dot3 = Vec3::dot(edgeVertex3, normalTriangleUni);

            // Então ponto interceptado está dentro do triângulo e está na face frontal.
            if (dot1 > 0  && dot2 > 0 && dot3 > 0) {
                r.interceptou = true;
                r.intersecao = tIntersection;
            } else {
                r.interceptou = false;
                r.intersecao = 0;
            }
        }
    
        return r;
    }
};


class Model {
  private:

    void setCluster() {
        Point middle_point(0, 0, 0);

        for (int i = 0; i < num_vertices; ++i) {
            middle_point.x += vertices[i].x;
            middle_point.y += vertices[i].y;
            middle_point.z += vertices[i].z;
        }

        middle_point.x /= num_vertices;
        middle_point.y /= num_vertices;
        middle_point.z /= num_vertices;

        float max_distance = 0;
        for (int i = 0; i < num_vertices; ++i) {
            Vec3 radius(
                middle_point.x - vertices[i].x,
                middle_point.y - vertices[i].y,
                middle_point.z - vertices[i].z
            );
            float length = Vec3::length(radius);
            if (length > max_distance) {
                max_distance = length;
            }
        }

        cluster = new Sphere(middle_point, max_distance);
    };

  public:
    int num_faces;
    int num_vertices;
    Sphere *cluster;
    Point *vertices;
    Triangle *faces;
    Material material;

    Model(const int n_faces, const int n_vertices, Point *vertices_list, Triangle *faces_list, Material mat) {
        num_faces = n_faces;
        num_vertices = n_vertices;
        faces = faces_list;
        vertices = vertices_list;
        material = mat;

        setCluster();
    };
};
