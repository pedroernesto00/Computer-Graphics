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
Point p1(250, 300, 1500);
Point p2(150, 150, 1500);
Point p3(350, 150, 1500);
Triangle tri(p1, p2, p3, triangle_material);

// Snowman definition
Point body_center(250, 150, 1500); // Center of body sphere
Sphere body(body_center, 100, snow_material);

int objects_len = 0;                       // Number of objects (spheres) in scenario
Sphere objects[] = {body}; // List of these objects

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
        for (int i = 0; i < canvasH; i += 1) {
            for (int j = 0; j < canvasW; j += 1) {
                Point Pix(j * dx + dx / 2 - windowW / 2, i * dy + dy / 2 - windowH / 2, d); // Pixel point in window

                // Vector from camera to Pixel
                Vec3 V(Pix.x - O.x, Pix.y - O.y, Pix.z - O.z); 
                
                float t_norm = 1000000000;

                // Setting the enviroment light;
                Vec3 Ienv(0.5764705, 0.6470588, 0.756862);

                // Draw Triangle
                resultado result = tri.intersectionTriangle(V, O);
                
                //result.interceptou = false;
                if (result.interceptou && result.intersecao < t_norm) {
                    V *= result.intersecao;

                    // Find the intercepted point
                    Point P(V[0], V[1], V[2]);

                    Vec3 N = tri.findNormal();
                    Vec3 n = Vec3::normalize(N);

                    Vec3 L(light.center.x - P.x, light.center.y - P.y, light.center.z - P.z);
                    Vec3 l = Vec3::normalize(L); // Nomalized vector from point to light
                    
                    // Components factors to enviroment light
                    Vec3 Kenv(tri.material.env_material[0], 
                                tri.material.env_material[1], 
                                tri.material.env_material[2]); 

                    // Generating the final color for current pixel
                    Vec3 Color(Ienv[0], Ienv[1], Ienv[2]);
                    Color = Vec3::at(Color, Kenv);

                    Vec3 Kdif(tri.material.dif_material[0], 
                            tri.material.dif_material[1], 
                            tri.material.dif_material[2]); // Components factors to difuse light
                        
                    Vec3 Kspe(tri.material.spe_material[0], 
                        tri.material.spe_material[1], 
                        tri.material.spe_material[2]); // Components factors to specular light

                    Vec3 If(light.color[0], 
                        light.color[1], 
                        light.color[2]); // Light rate

                    // Calculating the difusing rate
                    Vec3 Idif(If[0] * Kdif[0], If[1] * Kdif[1], If[2] * Kdif[2]);
                    Idif *= Vec3::dot(l, n);

                    // Calculating the specular rate
                    Vec3 Ispe(If[0] * Kspe[0], If[1] * Kspe[1], If[2] * Kspe[2]);
                    Vec3 r = (n * (2 * Vec3::dot(l, n))) - l;
                    Vec3 PO(O.x-P.x, O.y-P.y, O.z-P.z);
                    Vec3 v = Vec3::normalize(PO);
                    Ispe *= pow(Vec3::dot(r, v), 3);

                    Color = Vec3::at(Color, Kenv);
                    Color += Idif;
                    Color += Ispe;

                    Vec3 defaultColor (Color[0], Color[1], Color[2]);

                    /*float t_shadow_min = -10000000000;
                    for (int q = 0; q < objects_len; q++) {
                        if (q != k) {
                            // Checking if the ball is intercepted by light ray
                            bool shadow_intercepted = false;
                            float t_shadow_int = objects[q].checkInterception(shadow_intercepted, l, P, true);
                            if (t_shadow_int && t_shadow_int <= 0 && t_shadow_int > t_shadow_min) {
                                Color = defaultColor;
                                Vec3 shadow_fact(0.3, 0.3, 0.3);
                                Color = Vec3::at(Color, shadow_fact);
                                t_shadow_min = t_shadow_int;
                            }
                        }
                    }*/

                    glColor3f(Color[0], Color[1], Color[2]);
                    t_norm = result.intersecao;

                } else {
                    glColor3f(1, 1, 1);
                }

                // Draw Sphere
                for (int k = 0; k < objects_len; k++) {
                    bool intercepted = false;
                    float t_int = objects[k].checkInterception(intercepted, V, O);

                    if (intercepted && t_int < t_norm) {
                        V *= t_int;

                        // Find the intercepted point
                        Point P(V[0], V[1], V[2]);

                        Vec3 N(P.x - objects[k].center.x, P.y - objects[k].center.y, P.z - objects[k].center.z);
                        Vec3 n = Vec3::normalize(N); // Normal vector to point in sphere surface

                        Vec3 L(light.center.x - P.x, light.center.y - P.y, light.center.z - P.z);
                        Vec3 l = Vec3::normalize(L); // Nomalized vector from point to light
						
						Vec3 Kenv(objects[k].material.env_material[0], 
                                    objects[k].material.env_material[1], 
                                    objects[k].material.env_material[2]); // Components factors to enviroment light

                        // Generating the final color for current pixel
                        Vec3 Color(Ienv[0], Ienv[1], Ienv[2]);
                        Color = Vec3::at(Color, Kenv);

                        Vec3 Kdif(objects[k].material.dif_material[0], 
                            objects[k].material.dif_material[1], 
                            objects[k].material.dif_material[2]); // Components factors to difuse light
                        
                        Vec3 Kspe(objects[k].material.spe_material[0], 
                            objects[k].material.spe_material[1], 
                            objects[k].material.spe_material[2]); // Components factors to specular light

                        Vec3 If(light.color[0], 
                            light.color[1], 
                            light.color[2]); // Light rate

                        // Calculating the difusing rate
                        Vec3 Idif(If[0] * Kdif[0], If[1] * Kdif[1], If[2] * Kdif[2]);
                        Idif *= Vec3::dot(l, n);

                        // Calculating the specular rate
                        Vec3 Ispe(If[0] * Kspe[0], If[1] * Kspe[1], If[2] * Kspe[2]);
                        Vec3 r = (n * (2 * Vec3::dot(l, n))) - l;
                        Vec3 PO(O.x-P.x, O.y-P.y, O.z-P.z);
                        Vec3 v = Vec3::normalize(PO);
                        Ispe *= pow(Vec3::dot(r, v), 3);

                        Color = Vec3::at(Color, Kenv);
                        Color += Idif;
                        Color += Ispe;

                        Vec3 defaultColor (Color[0], Color[1], Color[2]);

                        float t_shadow_min = -10000000000;
                        for (int q = 0; q < objects_len; q++) {
                            if (q != k) {
                                // Checking if the ball is intercepted by light ray
                                bool shadow_intercepted = false;
                                float t_shadow_int = objects[q].checkInterception(shadow_intercepted, l, P, true);
                                if (t_shadow_int && t_shadow_int <= 0 && t_shadow_int > t_shadow_min) {
                                    Color = defaultColor;
                                    Vec3 shadow_fact(0.3, 0.3, 0.3);
                                    Color = Vec3::at(Color, shadow_fact);
                                    t_shadow_min = t_shadow_int;
                                }
                            }
                        }

                        glColor3f(Color[0], Color[1], Color[2]);
		                t_norm = t_int;
                    }
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

    for (int k = 0; k < objects_len; k++) {
        objects[k].center = worldToCamera(objects[k].center);
    }
    tri.vertex1 = worldToCamera(tri.vertex1);
    tri.vertex2 = worldToCamera(tri.vertex2);
    tri.vertex3 = worldToCamera(tri.vertex3);

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
