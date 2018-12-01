#include <cmath>
#include <iostream>
#include <thread>
#include <initializer_list>
#include <algorithm>
#include "models.h"
#include "writeBMP.h"
#include "Mat4.h"

#ifdef __APPLE__
// #include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#else
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment(lib, "glew32.lib")
#endif

#define PI 3.14159265

using namespace std;

const int canvasH = 720;
const int canvasW = 1360;

float camera_rot = 0;

float d = -700;                     // Position of window
int windowW = 1360;                  // Width of window
int windowH = 720;                  // Height of window
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

Point light1_center(-1000, 1500, 0);
Vec3 light1_color(1, 1, 1);
Light light1(light1_center, light1_color);

Point light2_center(100, 1500, 600);
Vec3 light2_color(0.1, 0.1, 0.1);
Light light2(light2_center, light2_color);

int num_lights = 1;
Light lights[] = {light1};

// Setting snow material
Vec3 snow_env_material(0.8, 0.8, 0.8);   // Material's enviroment component factors
Vec3 snow_dif_material(0.7, 0.7, 0.8);   // Material's difuse component factors
Vec3 snow_spe_material(0.1, 0.4, 0.4);   // Material's specular component factors
Material snow_material(snow_env_material, snow_dif_material, snow_spe_material);

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

float pixels[canvasH * canvasW * 3];

void backfaceElimination() {
    for (int m = 0; m < objects_len; m++) {
        for (int k = 0; k < objects[m].num_faces; k++) {
            Vec3 face_normal = Vec3::normalize(objects[m].faces[k].findNormal());
            float cos_angle = Vec3::dot(face_normal, k_camera);

            if (cos_angle > 0) {
                objects[m].faces[k].visible = false;
            } else {
                objects[m].faces[k].visible = true;
            }
        }
    }
}

void calculatePixelColor(int i, int j) {
    // Setting the enviroment light;
    Vec3 Ienv(0.5764705, 0.6470588, 0.756862);

    float defaultColor[] = {Ienv[0], Ienv[1], Ienv[2]};
    Point Pix(0, 0, 0);
    float t_norm;
    float t_cluster_norm;
    int selectedTriangle;
    float intersection;

    Point P(0, 0, 0);

    // Pixel point in window
    Pix.x = j * dx + dx / 2 - windowW / 2;
    Pix.y = i * dy + dy / 2 - windowH / 2;
    Pix.z = d;

    // Vector from camera to Pixel
    Vec3 V(Pix.x - O.x, Pix.y - O.y, Pix.z - O.z);

    defaultColor[0] = Ienv[0];
    defaultColor[1] = Ienv[1];
    defaultColor[2] = Ienv[2];

    t_cluster_norm = 1e10;

    for (int m = 0; m < objects_len; m++) {
        bool intercepted = false;
        float t_cluster_int = objects[m].cluster->checkInterception(intercepted, V, O);

        t_norm = 1e10;
        if (intercepted && t_cluster_int < t_cluster_norm) {
            selectedTriangle = -1;
            intersection = -1;

            // defaultColor[0] = 0;
            // defaultColor[1] = 0;
            // defaultColor[2] = 0;

            for (int k = 0; k < objects[m].num_faces; k++) {
                if (objects[m].faces[k].visible == true) {
                    // Draw Triangle
                    resultado result = objects[m].faces[k].intersectionTriangle(V, O);
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
                P.x = V[0];
                P.y = V[1];
                P.z = V[2];

                Vec3 N = objects[m].faces[k].findNormal();
                Vec3 n = Vec3::normalize(N);

                // Components factors to enviroment light
                Vec3 Kenv(
                    objects[m].material.env_material[0],
                    objects[m].material.env_material[1],
                    objects[m].material.env_material[2]
                );

                for (int q = 0; q < num_lights; q++) {
                    Vec3 L(lights[q].center.x - P.x, lights[q].center.y - P.y, lights[q].center.z - P.z);
                    Vec3 l = Vec3::normalize(L); // Nomalized vector from point to light

                    // Generating the final color for current pixel
                    Vec3 Color(Ienv[0], Ienv[1], Ienv[2]);
                    Color = Vec3::at(Color, Kenv);

                    Vec3 Kdif(
                        objects[m].material.dif_material[0],
                        objects[m].material.dif_material[1],
                        objects[m].material.dif_material[2]); // Components factors to difuse light

                    Vec3 Kspe(
                        objects[m].material.spe_material[0],
                        objects[m].material.spe_material[1],
                        objects[m].material.spe_material[2]); // Components factors to specular light

                    Vec3 If(
                        lights[q].color[0],
                        lights[q].color[1],
                        lights[q].color[2]); // Light rate

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

                    Ienv[0] = Color[0];
                    Ienv[1] = Color[1];
                    Ienv[2] = Color[2];

                    defaultColor[0] = Color[0];
                    defaultColor[1] = Color[1];
                    defaultColor[2] = Color[2];
                }
            }

            t_cluster_norm = t_cluster_int;
        }
    }

    pixels[i * canvasW * 3 + j * 3] = defaultColor[0];
    pixels[i * canvasW * 3 + j * 3 + 1] = defaultColor[1];
    pixels[i * canvasW * 3 + j * 3 + 2] = defaultColor[2];
}

void loadPixels() {
    backfaceElimination();

    for (int i = 0; i < canvasH; i++) {
        for (int j = 0; j < canvasW; j++) {
            calculatePixelColor(i, j);
        }
    }
}

// Drawing routine.
void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(canvasW, canvasH, GL_RGB, GL_FLOAT, pixels);
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

// OpenGL window reshape routine.
void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << x << ", " << y << endl;
    }
}

// Main routine.
int main(int argc, char **argv){
    glutInit(&argc, argv);

    for (int i = 0; i < objects_len; i++) {
        for (int k = 0; k < objects[i].num_faces; k++) {
            objects[i].faces[k].vertex1 = worldToCamera(objects[i].faces[k].vertex1);
            objects[i].faces[k].vertex2 = worldToCamera(objects[i].faces[k].vertex2);
            objects[i].faces[k].vertex3 = worldToCamera(objects[i].faces[k].vertex3);
        }

        objects[i].cluster->center = worldToCamera(objects[i].cluster->center);
    }

    // for (int i = 0; i < num_vertices2; i++) {
    //     cout << "Point(200 + 20 * " << vertices2[i][0] << ", 200 + 20 * " << vertices2[i][1] << ", 600 + 20 * " << vertices2[i][2] << ")," << endl;
    // }

    // for (int i = 0; i < num_faces2; i++) {
    //     cout << "Trianglue(vertices2[" << faces2[i][0] - 1 << "], " << "vertices2[" << faces2[i][1] - 1 << "], " << "vertices2[" << faces2[i][2]- 1 << "]), " << endl;
    // }

    light2.center = worldToCamera(light2.center);
    O = worldToCamera(O);

    loadPixels();

    writeBMP(pixels, canvasW, canvasH);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(canvasW, canvasH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ray Casting");

    glutDisplayFunc(drawScene);
    glutMouseFunc(mouseCallback);
    glutReshapeFunc(resize);

    setup();

    glutMainLoop();
}
