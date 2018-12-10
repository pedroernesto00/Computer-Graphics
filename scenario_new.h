#include <cmath>
#include <iostream>
#include "Mat3.h"
#include "Mat4.h"

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
    float w;

    Point(const Point&);
    Point(float, float, float);
    Point(float, float, float, float);
    void plus(const Vec3&);

    Point() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        w = 1.0;
    }

    const Point& operator = (const Point& p) {
        x = p[0];
        y = p[1];
        z = p[2];
        w = 1.0;

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

    const Point operator + (const Vec4& v) const {
        Point p;
        float x = this->x + v[0];
        float y = this->y + v[1];
        float z = this->z + v[2];
        p = Point(x, y, z, 1);

        return p;
    }

    const Point operator * (const Mat4& mat) {
        float j = 0;
        float k = 0;
        float l = 0;
        float m = 0;

        j += this->x * mat(0,0) + this->y * mat(0,1) + this->z * mat(0,2) + this->w * mat(0,3);
        k += this->x * mat(1,0) + this->y * mat(1,1) + this->z * mat(1,2) + this->w * mat(1,3);
        l += this->x * mat(2,0) + this->y * mat(2,1) + this->z * mat(2,2) + this->w * mat(2,3);
        m += this->x * mat(3,0) + this->y * mat(3,1) + this->z * mat(3,2) + this->w * mat(3,3);

        Point newPoint(j, k, l, m);
        return newPoint;
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

    static const Point pointScale(const Point& oldPoint, const Point& centerPoint, const Mat4& scala) {
        Vec3 v(oldPoint-centerPoint);

        Vec4 newV( scala * Vec4(v[0], v[1], v[2], 0) );
        
        return Point(centerPoint + newV);
    }
};

Point::Point (const Point& p) {
    x = p.x;
    y = p.y;
    z = p.z;
    w = p.w;
};

Point::Point (float cx, float cy, float cz) {
    x = cx;
    y = cy;
    z = cz;
    w = 1;
};

Point::Point (float cx, float cy, float cz, float cw) {
    x = cx;
    y = cy;
    z = cz;
    w = cw;
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
    Point *vertex1;
    Point *vertex2;
    Point *vertex3;
    bool visible;
    Material material;

    Triangle() {}

    Triangle(Point& v1, Point& v2, Point& v3) {
        vertex1 = &v1;
        vertex2 = &v2;
        vertex3 = &v3;
        visible = true;
        material = Material();
    }

    Triangle(Point& v1, Point& v2, Point& v3, Material m) {
        vertex1 = &v1;
        vertex2 = &v2;
        vertex3 = &v3;
        material = m;
        visible = true;
    }

    Point operator [] (short unsigned int index) const {
       if (index == 1) return (*this->vertex1);
       if (index == 2) return (*this->vertex2);
       if (index == 3) return (*this->vertex3);
    }

    const Triangle operator * (const Mat4& mat) const {
        Point pontoMedio = Point((this->vertex1->x + this->vertex2->x + this->vertex3->x)/3,
                                (this->vertex1->y + this->vertex2->y + this->vertex3->y)/3,
                                (this->vertex1->z + this->vertex2->z + this->vertex3->z)/3);

        Vec3 v1((*this->vertex1)-pontoMedio);
        Vec3 v2((*this->vertex2)-pontoMedio);
        Vec3 v3((*this->vertex3)-pontoMedio);

        Vec4 newV1( mat * Vec4(v1[0], v1[1], v1[2], 0) );
        Vec4 newV2( mat * Vec4(v2[0], v2[1], v2[2], 0) );
        Vec4 newV3( mat * Vec4(v3[0], v3[1], v3[2], 0) );
        
        Point newP1(pontoMedio + newV1);
        Point newP2(pontoMedio + newV2);
        Point newP3(pontoMedio + newV3);

       return Triangle(newP1, newP2, newP3);
    }

    void setVertex(unsigned short int t, Point& p) {
        if(t == 1) {
            this->vertex1 = &p;
        }

        if(t == 2) {
            this->vertex2 = &p;
        }

        if (t==3) {
            this->vertex3 = &p;
        }
    }

    Vec3 findNormal(void) {
        Vec3 edge1 = ((*this->vertex2) - (*this->vertex1));
        Vec3 edge2 = ((*this->vertex3) - (*this->vertex1));

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
            Vec3 sourceVertex = (*this->vertex1) - O; //Vetor da origem da câmera para um dos vértices do triângulo (neste caso, o primeiro)
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

            Vec3 edge1 = (*this->vertex2) - (*this->vertex1); //Vetor do vertex1 para o vertex2
            Vec3 edge2 = (*this->vertex3) - (*this->vertex2); //Vetor do vertice 2 para o vertice 3
            Vec3 edge3 = (*this->vertex1) - (*this->vertex3); //Vetor do vertice 3 para o vertice 1

            Vec3 vertex1Point = pointIntersection - (*this->vertex1); //Vetor do vértice 1 para o ponto de interseção
            Vec3 vertex2Point = pointIntersection - (*this->vertex2); //Vetor do vértice 2 para o ponto de interseção
            Vec3 vertex3Point = pointIntersection - (*this->vertex3); //Vetor do vértice 3 para o ponto de interseção

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

class BoundingBox {
  public:
    Point *vertices;
    Triangle *faces;

    BoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
        Point _vertices[] = {
            Point(minX, minY, maxZ), // p1
            Point(maxX, minY, maxZ), // p2
            Point(minX, maxY, maxZ), // p3
            Point(maxX, maxY, maxZ), // p4

            Point(minX, minY, minZ), // p5
            Point(maxX, minY, minZ), // p6
            Point(minX, maxY, minZ), // p7
            Point(maxX, maxY, minZ) // p8
        };

        Triangle _faces[] = {
            Triangle(vertices[0], vertices[1], vertices[2]), // f1
            Triangle(vertices[1], vertices[3], vertices[2]), // f2
            Triangle(vertices[1], vertices[5], vertices[3]), // f3
            Triangle(vertices[5], vertices[4], vertices[3]), // f4

            Triangle(vertices[5], vertices[6], vertices[4]), // f5
            Triangle(vertices[5], vertices[4], vertices[6]), // f6
            Triangle(vertices[4], vertices[2], vertices[6]), // f7
            Triangle(vertices[2], vertices[4], vertices[0]), // f8

            Triangle(vertices[3], vertices[4], vertices[6]), // f9
            Triangle(vertices[3], vertices[6], vertices[2]), // f10
            Triangle(vertices[1], vertices[5], vertices[5]), // f11
            Triangle(vertices[0], vertices[4], vertices[1]), // f12
        };

        vertices = _vertices;
        faces = _faces;
    }

    bool intercept(Vec3 V, Point O) {
        for (int k = 0; k < 12; k++) {
            if (faces[k].visible == true) {
                // Draw Triangle
                resultado result = faces[k].intersectionTriangle(V, O);
                if (result.interceptou) {
                    return true;
                }
            }   
        }

        return false;
    }
};

class Model {
  private:
    void setCluster() {
        Point middle_point(0, 0, 0);

        float minX = 1e10;
        float minY = 1e10;
        float minZ = 1e10;
        float maxX = -1e10;
        float maxY = -1e10;
        float maxZ = -1e10;
    
        for (int i = 0; i < num_vertices; ++i) {
            middle_point.x += vertices[i].x;
            middle_point.y += vertices[i].y;
            middle_point.z += vertices[i].z;

            if (vertices[i].z < minZ) minZ = vertices[i].z;
            if (vertices[i].y < minY) minY = vertices[i].y;
            if (vertices[i].x < minX) minX = vertices[i].x;
            if (vertices[i].z > maxZ) maxZ = vertices[i].z;
            if (vertices[i].y > maxY) maxY = vertices[i].y;
            if (vertices[i].x > maxX) maxX = vertices[i].x;
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
        box = new BoundingBox(minX, minY, minZ, maxX, maxY, maxZ);
    };

  public:
    int num_faces;
    int num_vertices;
    Sphere *cluster;
    BoundingBox *box;
    Point *vertices;
    Triangle *faces;
    Material material;

    void move(const Mat4&);
    void rotate(const Mat4&);
    void scale(const Mat4&);
    
    Model(const int n_faces, const int n_vertices, Point *vertices_list, Triangle *faces_list, Material mat) {
        num_faces = n_faces;
        num_vertices = n_vertices;
        faces = faces_list;
        vertices = vertices_list;
        material = mat;

        setCluster();
    }

};

void Model::move(const Mat4& trans) {
        for (int vertex = 0; vertex < this->num_vertices; vertex++) {
            this->vertices[vertex] = this->vertices[vertex] * trans;
        }
    }

void Model::rotate(const Mat4& rot) {
    for (int vertex = 0; vertex < this->num_vertices; vertex++) {
        this->vertices[vertex] = this->vertices[vertex] * rot;
    }
}

void Model::scale(const Mat4& scl) {
    for (int vertex = 0; vertex < this->num_vertices; vertex++) {
        this->vertices[vertex] = Point::pointScale(this->vertices[vertex], this->cluster->center, scl);
    }
}
