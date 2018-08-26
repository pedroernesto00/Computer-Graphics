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
};

#endif