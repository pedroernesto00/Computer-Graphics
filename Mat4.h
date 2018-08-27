#ifndef Mat4_H
#define Mat4_H

#include <iostream>
#include <cmath>

#include "Vec4.h"

using namespace std;

class Mat4 {
	
private:
	Vec4 c1, c2, c3, c4;

public:

	// Problemas com este construtor (A soma não pode ser efetuada)
	Mat4() {

		c1 = Vec4(1, 0, 0, 0);
		c2 = Vec4(0, 1, 0, 0);
		c3 = Vec4(0, 0, 1, 0);
        c4 = Vec4(0, 0, 0, 1);
	}

	Mat4(float x1, float x2, float x3, float x4,
			float y1, float y2, float y3, float y4,
			float z1, float z2, float z3, float z4,
            float w1, float w2, float w3, float w4) {

		c1 = Vec4(x1, y1, z1, w1);
		c2 = Vec4(x2, y2, z2, w2);
		c3 = Vec4(x3, y3, z3, w3);
        c4 = Vec4(x4, y4, z4, w4);

	}

	Mat4 (const Vec4& v1, const Vec4& v2, const Vec4& v3, const Vec4& v4) {
		
		c1 = v1;
		c2 = v2;
		c3 = v3;
        c4 = v4;
	}

	Mat4(const Mat4& mat) {

		c1 = mat.c1;
		c2 = mat.c2;
		c3 = mat.c3;
        c4 = mat.c4;
	}
	

	// Método de impressão na tela
	friend ostream& operator << (ostream& out, const Mat4& mat) {
		return out << endl << "[" << mat.c1[0] << ", " << mat.c2[0] << ", " << mat.c3[0] <<  ", " << mat.c4[0] << endl
							<< mat.c1[1] << ", " << mat.c2[1] << ", " << mat.c3[1] <<  ", " << mat.c4[1] << endl
							<< mat.c1[2] << ", " << mat.c2[2] << ", " << mat.c3[2] <<  ", " << mat.c4[2] << endl
                            << mat.c1[3] << ", " << mat.c2[3] << ", " << mat.c3[3] <<  ", " << mat.c4[3] << "]" << endl;
	}

	/*
	const Vec4& operador [] (int index) const {
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

	Vec4& operador [] (int index) {
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
		switch (col % 5) {
			case 0:
				return c1[row];
				break;
			case 1:
				return c2[row];
				break;
			case 2:
				return c3[row];
				break;
            case 3:
                return c4[row];
                break;
			default:
				break;
		}
	}

	float& operator () (int row, int col) {
		switch (col % 5) {
			case 0:
				return c1[row];
				break;
			case 1:
				return c2[row];
				break;
			case 2:
				return c3[row];
				break;
            case 3:
                return c4[row];
                break;
			default:
				break;
		}
	}
	

	// Método de soma de matrizes
	const Mat4 operator +(const Mat4& mat) const {
		Mat4 newMatrix(this->c1 + mat.c1, this->c2 + mat.c2, this->c3 + mat.c3, this->c4 + mat.c4);
		return newMatrix;
	}

	
	// Método de subtração de matrizes
	const Mat4 operator -(const Mat4& mat) const {
		Mat4 newMatrix(this->c1 - mat.c1, this->c2 - mat.c2, this->c3 - mat.c3, this->c4 - mat.c4);
		return newMatrix;
	}

	// Multiplicação da matriz por um escalar
	const Mat4 operator * (float k) const {
		Mat4 newMatrix(this->c1 * k, this->c2 * k, this->c3 * k, this->c4 * k);
		return newMatrix;
	}

	// Multiplicação da matriz por um vetor
	const Vec4 operator * (const Vec4& vec) const {
		float j = 0;
		float k = 0;
		float l = 0;
        float m = 0;

		for (int i = 0; i < 4; i++){
			j = j + (this->c1[i] * vec[i]);
		}
		
		for (int i = 0; i < 4; i++){
			k = k + (this->c2[i] * vec[i]);
		}

		for (int i = 0; i < 4; i++){
			l = l + (this->c3[i] * vec[i]);
		}

        for (int i = 0; i < 4; i++){
			m = m + (this->c4[i] * vec[i]);
		}

		Vec4 newVector(j, k, l, m);
		return newVector;
	}

	// Multiplicação da matriz por uma matriz
	const Mat4 operator * (const Mat4& mat) const {

		int col = 4;
		int row = 4;
		float matrix[row][col];
        
		matrix[0][0] = (this->c1[0] * mat(0, 0)) + (this->c2[0] * mat(1, 0)) + (this->c3[0] * mat(2, 0)) + (this->c4[0] * mat(3, 0));
		matrix[0][1] = (this->c1[0] * mat(0, 1)) + (this->c2[0] * mat(1, 1)) + (this->c3[0] * mat(2, 1)) + (this->c4[0] * mat(3, 1));
		matrix[0][2] = (this->c1[0] * mat(0, 2)) + (this->c2[0] * mat(1, 2)) + (this->c3[0] * mat(2, 2)) + (this->c4[0] * mat(3, 2));
        matrix[0][3] = (this->c1[0] * mat(0, 3)) + (this->c2[0] * mat(1, 3)) + (this->c3[0] * mat(2, 3)) + (this->c4[0] * mat(3, 3));

		matrix[1][0] = (this->c1[1] * mat(0, 0)) + (this->c2[1] * mat(1, 0)) + (this->c3[1] * mat(2, 0)) + (this->c4[1] * mat(3, 0));
		matrix[1][1] = (this->c1[1] * mat(0, 1)) + (this->c2[1] * mat(1, 1)) + (this->c3[1] * mat(2, 1)) + (this->c4[1] * mat(3, 1));
		matrix[1][2] = (this->c1[1] * mat(0, 2)) + (this->c2[1] * mat(1, 2)) + (this->c3[1] * mat(2, 2)) + (this->c4[1] * mat(3, 2));
        matrix[1][3] = (this->c1[1] * mat(0, 3)) + (this->c2[1] * mat(1, 3)) + (this->c3[1] * mat(2, 3)) + (this->c4[1] * mat(3, 3));
		
		matrix[2][0] = (this->c1[2] * mat(0, 0)) + (this->c2[2] * mat(1, 0)) + (this->c3[2] * mat(2, 0)) + (this->c4[2] * mat(3, 0));
		matrix[2][1] = (this->c1[2] * mat(0, 1)) + (this->c2[2] * mat(1, 1)) + (this->c3[2] * mat(2, 1)) + (this->c4[2] * mat(3, 1));
		matrix[2][2] = (this->c1[2] * mat(0, 2)) + (this->c2[2] * mat(1, 2)) + (this->c3[2] * mat(2, 2)) + (this->c4[2] * mat(3, 2));
        matrix[2][3] = (this->c1[2] * mat(0, 3)) + (this->c2[2] * mat(1, 3)) + (this->c3[2] * mat(2, 3)) + (this->c4[2] * mat(3, 3));

        matrix[3][0] = (this->c1[3] * mat(0, 0)) + (this->c2[3] * mat(1, 0)) + (this->c3[3] * mat(2, 0)) + (this->c4[3] * mat(3, 0));
		matrix[3][1] = (this->c1[3] * mat(0, 1)) + (this->c2[3] * mat(1, 1)) + (this->c3[3] * mat(2, 1)) + (this->c4[3] * mat(3, 1));
		matrix[3][2] = (this->c1[3] * mat(0, 2)) + (this->c2[3] * mat(1, 2)) + (this->c3[3] * mat(2, 2)) + (this->c4[3] * mat(3, 2));
        matrix[3][3] = (this->c1[3] * mat(0, 3)) + (this->c2[3] * mat(1, 3)) + (this->c3[3] * mat(2, 3)) + (this->c4[3] * mat(3, 3));

		Mat4 newMatrix(matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
						matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
						matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3],
                        matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
		
		return newMatrix;
	}


	// Multiplicação da matriz por um escalar
	const Mat4 operator / (float k) const {
		Mat4 newMatrix(this->c1 / k, this->c2 / k, this->c3 / k, this->c4 / k);
		return newMatrix;
	}

	// Atribuição de matriz
	const Mat4& operator=(const Mat4& mat) {
		
		this->c1 = mat.c1;
		this->c2 = mat.c2;
		this->c3 = mat.c3;
        this->c4 = mat.c4;
		
		return *this;
	}

	// Soma de matriz com atribuição
	const Mat4& operator+=(const Mat4& mat) {
		
		*this = *this + mat;
		
		return *this;
	}

	// Subtração de matriz com atribuição
	const Mat4& operator-=(const Mat4& mat) {
		
		*this = *this - mat;
		
		return *this;
	}

	// Multiplicação de matriz por escalar com atribuição
	const Mat4& operator*=(float k) {
		
		*this = *this * k;
		
		return *this;
	}

	// Multiplicação de matriz com atribuição
	const Mat4& operator*=(const Mat4& mat) {
		
		*this = *this * mat;
		
		return *this;
	}

	// Divisão de matriz por escalar com atribuição
	const Mat4& operator/=(float k) {
		
		*this = *this / k;
		
		return *this;
	}

	// Retorna a matriz inversa
	static const Mat4 inv(const Mat4& mat) {
		int n, i, j, k;
	    float matrizA[4][4], ident[4][4], inversa[4][4], pivo = 0, m = 0;
	    n = 4;

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
	static const Mat4 det(const Mat4& mat){
		int determinant[4][4];
		float det;
		int row, col;
		 
		for(row = 0; row < 4; row++) {
			for(col = 0; col < 4; col++) {
				determinant[row][col] = mat(row, col);
			}
		}
		 
		det = ((determinant[0][0] * determinant[1][1] * determinant[2][2] * determinant[3][3])
			+ (determinant[0][1] * determinant[1][2] * determinant[2][3] * determinant[3][0])
			+ (determinant[0][2] * determinant[1][3] * determinant[2][0] * determinant[3][1])
            + (determinant[0][3] * determinant[1][0] * determinant[2][1] * determinant[3][2]))

			- ((determinant[0][2] * determinant[1][1] * determinant[2][0] * determinant[3][3])
			+ (determinant[1][2] * determinant[1][0] * determinant[2][3] * determinant[3][2])
			+ (determinant[0][0] * determinant[1][3] * determinant[2][2] * determinant[3][1])
            + (determinant[0][3] * determinant[1][2] * determinant[2][1] * determinant[3][0]));

		cout << "Determinante: " << det << endl;
		 		  
		}

	// Retorna a matriz transposta
	static const Mat4 transpose(const Mat4& mat) {
        int n = 4;
		float transp[n][n];

		for (int row = 0; row < n; row++){
			for (int col = 0; col < n; col++){
				transp[col][row] = 0;
			}
		}

		for (int row = 0; row < n; row++){
			for (int col = 0; col < n; col++){
				transp[col][row] = mat(row, col);
			}
		}

		return Mat4 (transp[0][0], transp[0][1], transp[0][2], transp[0][3],
					transp[1][0], transp[1][1], transp[1][2], transp[1][3],
					transp[2][0], transp[2][1], transp[2][2], transp[2][3],
                    transp[3][0], transp[3][1], transp[3][2], transp[3][3]);
	}

	
	// Escalona a matriz ao longo do vetor
	const Mat4 scale(const Vec4& vector) const {
		float vectorLength = Vec4::length(vector);

		Vec4 c1_2(
			c1[0] + (vector[0] * vectorLength),
			c1[1] + (vector[1] * vectorLength),
			c1[2] + (vector[2] * vectorLength),
            c1[3] + (vector[3] * vectorLength)
		);

		Vec4 c2_2(
			c2[0] + (vector[0] * vectorLength),
			c2[1] + (vector[1] * vectorLength),
			c2[2] + (vector[2] * vectorLength),
            c1[3] + (vector[3] * vectorLength)
		);

		Vec4 c3_2(
			c3[0] + (vector[0] * vectorLength),
			c3[1] + (vector[1] * vectorLength),
			c3[2] + (vector[2] * vectorLength),
            c1[3] + (vector[3] * vectorLength)
		);

        Vec4 c4_2(
			c3[0] + (vector[0] * vectorLength),
			c3[1] + (vector[1] * vectorLength),
			c3[2] + (vector[2] * vectorLength),
            c1[3] + (vector[3] * vectorLength)
		);

		Mat4 mat_copy(c1_2, c2_2, c3_2, c4_2);

		return mat_copy;
	}

	// Rotaciona a matriz ao longo do vetor
	const Mat4 rotate(const Vec4& vector, float angle) const {
        // int n = 4;
		// Vec4 v2 = Vec4::cross(vector, vector);

		// float angle_cos = cos(angle);
		// float angle_sin = sin(angle);

		// float R[n][n] = {
		// 	{
		// 		angle_cos + v2[0] * (1 - angle_cos),
		// 		vector[0] * vector[1] * (1 - angle_cos) - vector[2] * angle_sin,
		// 		vector[0] * vector[2] * (1 - angle_cos) + vector[1] * angle_sin
		// 	}, {
		// 		vector[0] * vector[1] * (1 - angle_cos) + vector[2] * angle_sin,
		// 		angle_cos + v2[1] * (1 - angle_cos),
		// 		vector[1] * vector[2] * (1 - angle_cos) - vector[0] * angle_sin
		// 	}, {
		// 		vector[2] * vector[0] * (1 - angle_cos) - vector[1] * angle_sin,
		// 		vector[2] * vector[1] * (1 - angle_cos) + vector[0] * angle_sin,
		// 		angle_cos + v2[2] * (1 - angle_cos)
		// 	}
		// };

		// Mat4 R_Mat(R[0][0], R[0][1], R[0][2],
		// 		   R[1][0], R[1][1], R[1][2],
		// 		   R[2][0], R[2][1], R[2][2],
        //            R[3][0], R[3][1], R[3][2]);

		// Vec4 c1_2, c2_2, c3_2, c4_2;

		// c1_2 = R_Mat * c1;
		// c2_2 = R_Mat * c2;
		// c3_2 = R_Mat * c3;
        // c4_2 = R_Mat * c4;


		// Mat4 mat_copy(c1_2, c2_2, c3_2, c4_2);

		// return mat_copy;
	}

	// Reflete a matriz tomando como eixo de simetria o eixo decrito pelo vetor
	const Mat4 reflect(const Vec4& vector) const {
		// P' = P - n 2 (P n)
		// Vec4 n1 = Vec4::cross(, vector);

		// Mat4 R(
		// 	1 - (2 * n1)
		// );
	}
};

#endif