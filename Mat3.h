/*

DONE:
1) Scale
2) transpose
3) det
4) cof
5) rotate

DOING:
1) inv

TO-DO:
1) shear
2) reflect
3) lookAt
4)

*/

#ifndef MAT3_H
#define MAT3_H

#include <iostream>
#include <cmath>

#include "Vec3.h"

using namespace std;

class Mat3 {
	
private:
	Vec3 c1, c2, c3;

public:

	// Problemas com este construtor (A soma não pode ser efetuada)
	Mat3() {

		c1 = Vec3(1, 0, 0);
		c2 = Vec3(0, 1, 0);
		c3 = Vec3(0, 0, 1);
	}

	Mat3(float x1, float x2, float x3,
			float y1, float y2, float y3,
			float z1, float z2, float z3) {

		c1 = Vec3(x1, y1, z1);
		c2 = Vec3(x2, y2, z2);
		c3 = Vec3(x3, y3, z3);

	}

	Mat3 (const Vec3& v1, const Vec3& v2, const Vec3& v3) {
		
		c1 = v1;
		c2 = v2;
		c3 = v3;
	}

	Mat3(const Mat3& mat) {

		c1 = mat.c1;
		c2 = mat.c2;
		c3 = mat.c3;
	}
	

	// Método de impressão na tela
	friend ostream& operator << (ostream& out, const Mat3& mat) {
		return out << endl << "[" << mat.c1[0] << ", " << mat.c2[0] << ", " << mat.c3[0] << endl
							<< mat.c1[1] << ", " << mat.c2[1] << ", " << mat.c3[1] << endl
							<< mat.c1[2] << ", " << mat.c2[2] << ", " << mat.c3[2] << "]" << endl;
	}

	/*
	const Vec3& operador [] (int index) const {
		switch(index % 3) {
			case 0:
				return c1;
				break;
			case 1:
				return c2;
				break;
			case 2:
				return c3;
				break;
			default:
				break;
		}
	}

	Vec3& operador [] (int index) {
		switch(index % 3) {
			case 0:
				return c1;
				break;
			case 1:
				return c2;
				break;
			case 2:
				return c3;
				break;
			default:
				break;

		}
	}
	*/

	float operator () (int row, int col) const {
		switch (col % 3) {
			case 0:
				return c1[row];
				break;
			case 1:
				return c2[row];
				break;
			case 2:
				return c3[row];
				break;
			default:
				break;
		}
	}

	float& operator () (int row, int col) {
		switch (col % 3) {
			case 0:
				return c1[row];
				break;
			case 1:
				return c2[row];
				break;
			case 2:
				return c3[row];
				break;
			default:
				break;
		}
	}
	

	// Método de soma de matrizes
	const Mat3 operator +(const Mat3& mat) const {
		Mat3 newMatrix(this->c1 + mat.c1, this->c2 + mat.c2, this->c3 + mat.c3);
		return newMatrix;
	}

	
	// Método de subtração de matrizes
	const Mat3 operator -(const Mat3& mat) const {
		Mat3 newMatrix(this->c1 - mat.c1, this->c2 - mat.c2, this->c3 - mat.c3);
		return newMatrix;
	}

	// Multiplicação da matriz por um escalar
	const Mat3 operator * (float k) const {
		Mat3 newMatrix(this->c1 * k, this->c2 * k, this->c3 * k);
		return newMatrix;
	}

	// Multiplicação da matriz por um vetor
	const Vec3 operator * (const Vec3& vec) const {
		float j = 0;
		float k = 0;
		float l = 0;

		for (int i = 0; i < 3; i++){
			j = j + (this->c1[i] * vec[i]);
		}
		
		for (int i = 0; i < 3; i++){
			k = k + (this->c2[i] * vec[i]);
		}

		for (int i = 0; i < 3; i++){
			l = l + (this->c3[i] * vec[i]);
		}

		Vec3 newVector(j, k, l);
		return newVector;
	}

	// Multiplicação da matriz por uma matriz
	const Mat3 operator * (const Mat3& mat) const {

		int col = 3;
		int row = 3;
		float matrix[row][col];
		
		matrix[0][0] = (this->c1[0] * mat(0, 0)) + (this->c2[0] * mat(1, 0)) + (this->c3[0] * mat(2, 0));
		matrix[0][1] = (this->c1[0] * mat(0, 1)) + (this->c2[0] * mat(1, 1)) + (this->c3[0] * mat(2, 1));
		matrix[0][2] = (this->c1[0] * mat(0, 2)) + (this->c2[0] * mat(1, 2)) + (this->c3[0] * mat(2, 2));

		matrix[1][0] = (this->c1[1] * mat(0, 0)) + (this->c2[1] * mat(1, 0)) + (this->c3[1] * mat(2, 0));
		matrix[1][1] = (this->c1[1] * mat(0, 1)) + (this->c2[1] * mat(1, 1)) + (this->c3[1] * mat(2, 1));
		matrix[1][2] = (this->c1[1] * mat(0, 2)) + (this->c2[1] * mat(1, 2)) + (this->c3[1] * mat(2, 2));
		
		matrix[2][0] = (this->c1[2] * mat(0, 0)) + (this->c2[2] * mat(1, 0)) + (this->c3[2] * mat(2, 0));
		matrix[2][1] = (this->c1[2] * mat(0, 1)) + (this->c2[2] * mat(1, 1)) + (this->c3[2] * mat(2, 1));
		matrix[2][2] = (this->c1[2] * mat(0, 2)) + (this->c2[2] * mat(1, 2)) + (this->c3[2] * mat(2, 2)); 

		Mat3 newMatrix(matrix[0][0], matrix[0][1], matrix[0][2],
						matrix[1][0], matrix[1][1], matrix[1][2],
						matrix[2][0], matrix[2][1], matrix[2][2]);
		
		return newMatrix;
	}


	// Multiplicação da matriz por um escalar
	const Mat3 operator / (float k) const {
		Mat3 newMatrix(this->c1 / k, this->c2 / k, this->c3 / k);
		return newMatrix;
	}

	// Atribuição de matriz
	const Mat3& operator=(const Mat3& mat) {
		
		this->c1 = mat.c1;
		this->c2 = mat.c2;
		this->c3 = mat.c3;
		
		return *this;
	}

	// Soma de matriz com atribuição
	const Mat3& operator+=(const Mat3& mat) {
		
		*this = *this + mat;
		
		return *this;
	}

	// Subtração de matriz com atribuição
	const Mat3& operator-=(const Mat3& mat) {
		
		*this = *this - mat;
		
		return *this;
	}

	// Multiplicação de matriz por escalar com atribuição
	const Mat3& operator*=(float k) {
		
		*this = *this * k;
		
		return *this;
	}

	// Multiplicação de matriz com atribuição
	const Mat3& operator*=(const Mat3& mat) {
		
		*this = *this * mat;
		
		return *this;
	}

	// Divisão de matriz por escalar com atribuição
	const Mat3& operator/=(float k) {
		
		*this = *this / k;
		
		return *this;
	}

	// Retorna a matriz de cofatores
	static const Mat3 cof(const Mat3& mat) {
		float cof[9];

		// Vec 1
		cof[0] = det(mat(1, 1), mat(1, 2), mat(2, 1), mat(2, 2));
		cof[3] = det(mat(0, 1), mat(0, 2), mat(2, 1), mat(2, 2)) * (-1);
		cof[6] = det(mat(0, 1), mat(0, 2), mat(1, 1), mat(1, 2));
		
		// Vec 2
		cof[1] = det(mat(1, 0), mat(1, 2), mat(2, 0), mat(2, 2)) * (-1);
		cof[4] = det(mat(0, 0), mat(0, 2), mat(2, 0), mat(2, 2));
		cof[7] = det(mat(0, 0), mat(0, 2), mat(1, 0), mat(1, 2)) * (-1);

		// Vec 3
		cof[2] = det(mat(1, 0), mat(1, 1), mat(2, 0), mat(2, 1));
		cof[5] = det(mat(0, 0), mat(0, 1), mat(2, 0), mat(2, 1)) * (-1);
		cof[8] = det(mat(0, 0), mat(0, 1), mat(1, 0), mat(1, 1));

		return Mat3(cof[0], cof[1], cof[2],
					cof[3], cof[4], cof[5],
					cof[6], cof[7], cof[8]);
	}

	// Retorna a matriz inversa
	static const Mat3 inv(const Mat3& mat) {
		int n, i, j, k;
	    float matrizA[3][3], ident[3][3], inversa[3][3], pivo = 0, m = 0;
	    n = 3;

	    for(i = 0; i < n; i++) {
	        for(j = 0; j < n; j++) {
	            matrizA[i][j] = mat(i, j);
	        }
	    }

	    //Definindo a Matriz Identidade
	    for(i = 0; i < n; i++) {
	        for(j = 0; j < n; j++) {
	            if(i == j){// definindo a diagonal principal com valor = 1  Ex: a11, a22, a33    
	                ident[i][j] = 1;
	            }
	            else {
	                ident[i][j] = 0; //os outros termos recebem 0 Ex: a12, a13, a21, a23, a31, a32
	            }
	        }
	    }

	    //Calculando Inversa    
	    for(j = 0; j < n; j++) {
	        pivo = matrizA[j][j]; //Elementos da diagonal principal
	        for(k = j; k < n; k++) {
	            matrizA[j][k] = (matrizA[j][k])/(pivo); //L1 -> L1/pivo , L2 -> L2/pivo, L3 -> L3/pivo
	            ident[j][k] = (ident[j][k])/(pivo);  //Ex: 1 0 0 / pivo  , 0 1 0 / pivo,   0 0 1/ pivo
	        }


	        for(i = 0; i < n; i++) {
	            if(i != j) {
	                m = matrizA[i][j];//multiplicador   Ex: m = 1

	                for(k = 0; k < n; k++) {
	                    matrizA[i][k] = (matrizA[i][k]) - (m * matrizA[j][k]); //Ex: L2 -> L2 - ( 1"m" - L1)
	                    ident[i][k] = (ident[i][k]) - (m * ident[j][k]);  
	                }       
	            }
	        }
	    }


	    cout << endl << " ----  Matriz Inversa  ---- " << endl;
	    for(i = 0; i < n; i++) {
	        for (j = 0; j < n; j++) {
	            cout << ident[i][j] << " ";
			}
	        cout << endl;
	    }
	}

	// Retorna o determinante da matriz
	static const Mat3 det(const Mat3& mat){
		int determinant[3][3];
		float det;
		int row, col;
		 
		for(row = 0; row < 3; row++) {
			for(col = 0; col < 3; col++) {
				determinant[row][col] = mat(row, col);
			}
		}
		 
		det = ((determinant[0][0] * determinant[1][1] * determinant[2][2])
			+ (determinant[0][1] * determinant[1][2] * determinant[2][0])
			+ (determinant[0][2] * determinant[1][0] * determinant[2][1]))

			- ((determinant[2][0] * determinant[1][1] * determinant[0][2])
			+ (determinant[2][1] * determinant[1][2] * determinant[0][0])
			+ (determinant[2][2] * determinant[1][0] * determinant[0][1]));

		cout << "Determinante: " << det << endl;
		 		  
	}

	static const float det(float a, float b, float c, float d) {
		return (a * d) - (b * c);
	}

	// Retorna a matriz transposta
	static const Mat3 transpose(const Mat3& mat) {
		float transp[3][3];

		for (int row = 0; row < 3; row++){
			for (int col = 0; col < 3; col++){
				transp[col][row] = 0;
			}
		}

		for (int row = 0; row < 3; row++){
			for (int col = 0; col < 3; col++){
				transp[col][row] = mat(row, col);
			}
		}

		return Mat3 (transp[0][0], transp[0][1], transp[0][2], 
					transp[1][0], transp[1][1], transp[1][2], 
					transp[2][0], transp[2][1], transp[2][2]);
	}

	
	// Escalona a matriz ao longo do vetor
	const Mat3 scale(const Vec3& vector) const {
		float vectorLength = Vec3::length(vector);

		Vec3 c1_2(
			c1[0] + (vector[0] * vectorLength),
			c1[1] + (vector[1] * vectorLength),
			c1[2] + (vector[2] * vectorLength)
		);

		Vec3 c2_2(
			c2[0] + (vector[0] * vectorLength),
			c2[1] + (vector[1] * vectorLength),
			c2[2] + (vector[2] * vectorLength)
		);

		Vec3 c3_2(
			c3[0] + (vector[0] * vectorLength),
			c3[1] + (vector[1] * vectorLength),
			c3[2] + (vector[2] * vectorLength)
		);

		Mat3 mat_copy(c1_2, c2_2, c3_2);

		return mat_copy;
	}

	// Rotaciona a matriz ao longo do vetor
	const Mat3 rotate(const Vec3& vector, float angle) const {
		Vec3 v2 = Vec3::cross(vector, vector);

		float angle_cos = cos(angle);
		float angle_sin = sin(angle);

		float R[3][3] = {
			{
				angle_cos + v2[0] * (1 - angle_cos),
				vector[0] * vector[1] * (1 - angle_cos) - vector[2] * angle_sin,
				vector[0] * vector[2] * (1 - angle_cos) + vector[1] * angle_sin
			}, {
				vector[0] * vector[1] * (1 - angle_cos) + vector[2] * angle_sin,
				angle_cos + v2[1] * (1 - angle_cos),
				vector[1] * vector[2] * (1 - angle_cos) - vector[0] * angle_sin
			}, {
				vector[2] * vector[0] * (1 - angle_cos) - vector[1] * angle_sin,
				vector[2] * vector[1] * (1 - angle_cos) + vector[0] * angle_sin,
				angle_cos + v2[2] * (1 - angle_cos)
			}
		};

		Mat3 R_Mat(R[0][0], R[0][1], R[0][2],
				   R[1][0], R[1][1], R[1][2],
				   R[2][0], R[2][1], R[2][2]);

		Vec3 c1_2, c2_2, c3_2;

		c1_2 = R_Mat * c1;
		c2_2 = R_Mat * c2;
		c3_2 = R_Mat * c3;

		Mat3 mat_copy(c1_2, c2_2, c3_2);

		return mat_copy;
	}

};

#endif