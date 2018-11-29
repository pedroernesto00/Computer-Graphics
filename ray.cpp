#include <cmath>
#include <iostream>
#include "scenario_new.h"
#include "Mat4.h"

#ifdef __APPLE__
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif

#define PI 3.14159265

using namespace std;

int canvasH = 500;
int canvasW = 500;

float camera_rot = 0;

float d = -700;                     // Position of window
int windowW = 500;                  // Width of window
int windowH = 500;                  // Height of window
int dy = windowH/canvasH;           // Size of y delta
int dx = windowW/canvasW;           // Size of x delta

// Initialization routine.
void setup(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Origin's point of camera
Point O(250, 250, 700); // Front

Point LookAt(250, 250, 1500);
Point ViewUp(LookAt.x, LookAt.y + 100, LookAt.z);
Vec3 K_camera(O.x - LookAt.x, O.y - LookAt.y, O.z - LookAt.z);
Vec3 k_camera = Vec3::normalize(K_camera);
Vec3 O_UP(ViewUp.x - LookAt.x, ViewUp.y - LookAt.y, ViewUp.z - LookAt.z);
Vec3 I_camera = Vec3::cross(O_UP, k_camera);
Vec3 i_camera = Vec3::normalize(I_camera);
Vec3 J_camera = Vec3::cross(k_camera, i_camera);
Vec3 j_camera = Vec3::normalize(J_camera);

Point light_center(-1000, 1500, 0);
Vec3 light_color(1, 1, 1);
Light light(light_center, light_color);

// Setting snow material
Vec3 snow_env_material(0.8, 0.8, 0.8);   // Material's enviroment component factors
Vec3 snow_dif_material(0.7, 0.7, 0.8);   // Material's difuse component factors
Vec3 snow_spe_material(0.1, 0.1, 0.1);   // Material's specular component factors
Material snow_material(snow_env_material, snow_dif_material, snow_spe_material);

// Setting triangle material
Vec3 triangle_env_material(0.9, 0.9, 0.9);   // Material's enviroment component factors
Vec3 triangle_dif_material(0.9, 0.9, 0.9);   // Material's difuse component factors
Vec3 triangle_spe_material(0.9, 0.9, 0.9);   // Material's specular component factors
Material triangle_material(triangle_env_material, triangle_dif_material, triangle_spe_material);

// Triangle definition
const int num_faces = 92;
const int num_vertices = 48;
Triangle* faces[num_faces] = {};

int faces_vertices[num_faces][3] = {
    3, 16, 4,
    12, 18, 9,
    6, 25, 8,
    20, 10, 19,
    18, 10, 9,
    12, 20, 17,
    3, 10, 1,
    1, 11, 2,
    2, 12, 4,
    4, 9, 3,
    15, 13, 14,
    2, 14, 1,
    4, 15, 2,
    1, 13, 3,
    7, 17, 8,
    5, 18, 7,
    8, 20, 6,
    6, 19, 5,
    24, 29, 21,
    8, 26, 7,
    5, 28, 6,
    7, 27, 5,
    22, 25, 21,
    23, 26, 22,
    21, 28, 24,
    24, 27, 23,
    29, 31, 30,
    21, 30, 22,
    23, 32, 24,
    31, 33, 35,
    38, 45, 46,
    30, 35, 36,
    30, 34, 22,
    22, 33, 23,
    38, 39, 37,
    40, 46, 48,
    36, 43, 44,
    35, 41, 43,
    43, 45, 47,
    44, 47, 48,
    44, 46, 42,
    41, 46, 45,
    36, 42, 34,
    39, 45, 37,
    34, 41, 33,
    40, 47, 39,
    3, 13, 16,
    12, 17, 18,
    6, 28, 25,
    20, 11, 10,
    18, 19, 10,
    12, 11, 20,
    3, 9, 10,
    1, 10, 11,
    2, 11, 12,
    4, 12, 9,
    15, 16, 13,
    2, 15, 14,
    4, 16, 15,
    1, 14, 13,
    7, 18, 17,
    5, 19, 18,
    8, 17, 20,
    6, 20, 19,
    24, 32, 29,
    8, 25, 26,
    5, 27, 28,
    7, 26, 27,
    22, 26, 25,
    23, 27, 26,
    21, 25, 28,
    24, 28, 27,
    29, 32, 31,
    21, 29, 30,
    23, 31, 32,
    31, 23, 33,
    38, 37, 45,
    30, 31, 35,
    30, 36, 34,
    22, 34, 33,
    38, 40, 39,
    40, 38, 46,
    36, 35, 43,
    35, 33, 41,
    43, 41, 45,
    44, 43, 47,
    44, 48, 46,
    41, 42, 46,
    36, 44, 42,
    39, 47, 45,
    34, 42, 41,
    40, 48, 47
};

float coords[num_vertices][3] = {
    1.619769 * 60 + 125, 100 + 2.043673 * 60, 600 + 4.789231 * 60,
    1.716691 * 60 + 125, 100 + 2.772106 * 60, 600 + 4.850597 * 60,
    2.256417 * 60 + 125, 100 + 2.043673 * 60, 600 + 3.783701 * 60,
    2.353339 * 60 + 125, 100 + 2.772106 * 60, 600 + 3.845067 * 60,
    1.867751 * 60 + 125, 100 + 2.227356 * 60, 600 + 4.571919 * 60,
    1.913161 * 60 + 125, 100 + 2.568648 * 60, 600 + 4.600671 * 60,
    2.166039 * 60 + 125, 100 + 2.227356 * 60, 600 + 4.100800 * 60,
    2.211450 * 60 + 125, 100 + 2.568648 * 60, 600 + 4.129551 * 60,
    2.297218 * 60 + 125, 100 + 1.988607 * 60, 600 + 3.703049 * 60,
    1.564314 * 60 + 125, 100 + 1.988607 * 60, 600 + 4.860606 * 60,
    1.675890 * 60 + 125, 100 + 2.827172 * 60, 600 + 4.931250 * 60,
    2.408793 * 60 + 125, 100 + 2.827172 * 60, 600 + 3.773693 * 60,
    2.262100 * 60 + 125, 100 + 2.042614 * 60, 600 + 3.787300 * 60,
    1.625452 * 60 + 125, 100 + 2.042614 * 60, 600 + 4.792830 * 60,
    1.722374 * 60 + 125, 100 + 2.771046 * 60, 600 + 4.854196 * 60,
    2.359022 * 60 + 125, 100 + 2.771046 * 60, 600 + 3.848666 * 60,
    2.461840 * 60 + 125, 100 + 2.817284 * 60, 600 + 3.807279 * 60,
    2.350264 * 60 + 125, 100 + 1.978719 * 60, 600 + 3.736635 * 60,
    1.617361 * 60 + 125, 100 + 1.978719 * 60, 600 + 4.894192 * 60,
    1.728936 * 60 + 125, 100 + 2.817284 * 60, 600 + 4.964836 * 60,
    2.204301 * 60 + 125, 100 + 2.493329 * 60, 600 + 4.249826 * 60,
    2.176064 * 60 + 125, 100 + 2.281111 * 60, 600 + 4.231948 * 60,
    1.990587 * 60 + 125, 100 + 2.281111 * 60, 600 + 4.524893 * 60,
    2.018824 * 60 + 125, 100 + 2.493329 * 60, 600 + 4.542771 * 60,
    2.269294 * 60 + 125, 100 + 2.557866 * 60, 600 + 4.166175 * 60,
    2.223883 * 60 + 125, 100 + 2.216574 * 60, 600 + 4.137424 * 60,
    1.925595 * 60 + 125, 100 + 2.216574 * 60, 600 + 4.608543 * 60,
    1.971006 * 60 + 125, 100 + 2.557866 * 60, 600 + 4.637295 * 60,
    2.276824 * 60 + 125, 100 + 2.479811 * 60, 600 + 4.295743 * 60,
    2.248587 * 60 + 125, 100 + 2.267594 * 60, 600 + 4.277865 * 60,
    2.063110 * 60 + 125, 100 + 2.267594 * 60, 600 + 4.570810 * 60,
    2.091346 * 60 + 125, 100 + 2.479811 * 60, 600 + 4.588688 * 60,
    1.998333 * 60 + 125, 100 + 1.771431 * 60, 600 + 4.529797 * 60,
    2.183810 * 60 + 125, 100 + 1.771431 * 60, 600 + 4.236852 * 60,
    2.070855 * 60 + 125, 100 + 1.771431 * 60, 600 + 4.575714 * 60,
    2.256332 * 60 + 125, 100 + 1.769326 * 60, 600 + 4.282769 * 60,
    1.997958 * 60 + 125, 100 + 1.740192 * 60, 600 + 4.529672 * 60,
    2.183436 * 60 + 125, 100 + 1.740192 * 60, 600 + 4.236727 * 60,
    2.070481 * 60 + 125, 100 + 1.740192 * 60, 600 + 4.575589 * 60,
    2.255958 * 60 + 125, 100 + 1.738087 * 60, 600 + 4.282644 * 60,
    1.767334 * 60 + 125, 100 + 1.767158 * 60, 600 + 4.654865 * 60,
    2.214229 * 60 + 125, 100 + 1.767158 * 60, 600 + 3.949034 * 60,
    2.061558 * 60 + 125, 100 + 1.767158 * 60, 600 + 4.841152 * 60,
    2.508453 * 60 + 125, 100 + 1.765588 * 60, 600 + 4.135321 * 60,
    1.765899 * 60 + 125, 100 + 1.743854 * 60, 600 + 4.654227 * 60,
    2.212794 * 60 + 125, 100 + 1.743854 * 60, 600 + 3.948396 * 60,
    2.060123 * 60 + 125, 100 + 1.743854 * 60, 600 + 4.840513 * 60,
    2.507018 * 60 + 125, 100 + 1.742284 * 60, 600 + 4.134683 * 60
};

Point worldToCamera(Point Po) {
    Vec3 OO(O.x, O.y, O.z);
    Vec4 OP(Po.x, Po.y, Po.z, 1);

    Vec4 c1(i_camera[0], j_camera[0], k_camera[0], 0);
    Vec4 c2(i_camera[1], j_camera[1], k_camera[1], 0);
    Vec4 c3(i_camera[2], j_camera[2], k_camera[2], 0);
    Vec4 c4(-(Vec3::dot(i_camera, OO)), -(Vec3::dot(j_camera, OO)), -(Vec3::dot(k_camera, OO)), 1);

    return Point(
        c1[0] * OP[0] + c2[0] * OP[1] + c3[0] * OP[2] + c4[0] * OP[3],
        c1[1] * OP[0] + c2[1] * OP[1] + c3[1] * OP[2] + c4[1] * OP[3],
        c1[2] * OP[0] + c2[2] * OP[1] + c3[2] * OP[2] + c4[2] * OP[3]
    );
}

// Drawing routine.
void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glPointSize(1);
    glBegin(GL_POINTS);
        // Setting the enviroment light;
        Vec3 Ienv(0.5764705, 0.6470588, 0.756862);

        for (int i = 0; i < canvasH; i += 1) {
            for (int j = 0; j < canvasW; j += 1) {
                Point Pix(j * dx + dx / 2 - windowW / 2, i * dy + dy / 2 - windowH / 2, d); // Pixel point in window

                // Vector from camera to Pixel
                Vec3 V(Pix.x - O.x, Pix.y - O.y, Pix.z - O.z); 
                
                float t_norm = 1e10;

                glColor3f(Ienv[0], Ienv[1], Ienv[2]);

                int selectedTriangle = -1;
                float intersection = -1;
                for (int k = 0; k < num_faces; k++) {
                    if (faces[k] != NULL) {
                        // Draw Triangle
                        resultado result = faces[k]->intersectionTriangle(V, O);
                        if (result.interceptou && result.intersecao < t_norm) {
                            selectedTriangle = k;
                            t_norm = result.intersecao;
                        }
                    }
                }

                if (selectedTriangle >= 0) {
                    int k = selectedTriangle;
                    V *= intersection;

                    // Find the intercepted point
                    Point P(V[0], V[1], V[2]);

                    Vec3 N = faces[k]->findNormal();
                    Vec3 n = Vec3::normalize(N);

                    Vec3 L(light.center.x - P.x, light.center.y - P.y, light.center.z - P.z);
                    Vec3 l = Vec3::normalize(L); // Nomalized vector from point to light

                    // Components factors to enviroment light
                    Vec3 Kenv(faces[k]->material.env_material[0],
                              faces[k]->material.env_material[1],
                              faces[k]->material.env_material[2]);

                    // Generating the final color for current pixel
                    Vec3 Color(Ienv[0], Ienv[1], Ienv[2]);
                    Color = Vec3::at(Color, Kenv);

                    Vec3 Kdif(faces[k]->material.dif_material[0],
                              faces[k]->material.dif_material[1],
                              faces[k]->material.dif_material[2]); // Components factors to difuse light

                    Vec3 Kspe(faces[k]->material.spe_material[0],
                              faces[k]->material.spe_material[1],
                              faces[k]->material.spe_material[2]); // Components factors to specular light

                    Vec3 If(light.color[0],
                            light.color[1],
                            light.color[2]); // Light rate

                    // Calculating the difusing rate
                    Vec3 Idif(If[0] * Kdif[0], If[1] * Kdif[1], If[2] * Kdif[2]);
                    Idif *= Vec3::dot(l, n);

                    // Calculating the specular rate
                    Vec3 Ispe(If[0] * Kspe[0], If[1] * Kspe[1], If[2] * Kspe[2]);
                    Vec3 r = (n * (2 * Vec3::dot(l, n))) - l;
                    Vec3 PO(O.x - P.x, O.y - P.y, O.z - P.z);
                    Vec3 v = Vec3::normalize(PO);
                    Ispe *= pow(Vec3::dot(r, v), 3);

                    Color = Vec3::at(Color, Kenv);
                    Color += Idif;
                    Color += Ispe;

                    glColor3f(Color[0], Color[1], Color[2]);
                }

                glVertex2i(j, i);
            }
        }
    glEnd();
    glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, canvasW, 0.0, canvasH, 10.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main routine.
int main(int argc, char **argv){
    glutInit(&argc, argv);

    for (int i = 0; i < num_faces; i++) {
        Point p1(coords[faces_vertices[i][0] - 1][0], coords[faces_vertices[i][0] - 1][1], coords[faces_vertices[i][0] - 1][2]);
        Point p2(coords[faces_vertices[i][1] - 1][0], coords[faces_vertices[i][1] - 1][1], coords[faces_vertices[i][1] - 1][2]);
        Point p3(coords[faces_vertices[i][2] - 1][0], coords[faces_vertices[i][2] - 1][1], coords[faces_vertices[i][2] - 1][2]);
        faces[i] = new Triangle(p1, p2, p3, triangle_material);
    }

    for (int k = 0; k < num_faces; k++) {
        if (faces[k] != NULL) {
            faces[k]->vertex1 = worldToCamera(faces[k]->vertex1);
            faces[k]->vertex2 = worldToCamera(faces[k]->vertex2);
            faces[k]->vertex3 = worldToCamera(faces[k]->vertex3);
        } 
    }


    //light.center = worldToCamera(light.center);
    O = worldToCamera(O);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(canvasW, canvasH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ray Casting");
    
    glutDisplayFunc(drawScene);

    glutReshapeFunc(resize);
    
    setup();

    glutMainLoop();
}
