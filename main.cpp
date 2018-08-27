//#include "Vec3.h"
#include "Mat3.h"
#include "Vec4.h"

# define M_PI 3.14159265358979323846

int main(int argc, char const *argv[]) {

	// Teste intanciação
	Vec3 teste1(3.0, 4.0, 5.0);
	Vec3 teste2(4.0, 10.0, 2.01);
	Vec3 teste3(2.0, 5.0, 6.0);
	Vec3 teste4(2);
	Vec3 teste5(teste3);

	Vec4 test1();
	Vec4 test2(1);
	Vec4 test3(1, 2, 4, 6);
	Vec4 test4(test3);

	Mat3 mat1();
	Mat3 mat2(teste3, teste2, teste1);
	Mat3 mat3(teste1, teste2, teste3);

	Mat3 mat4(1, 2, 3, 4, 5, 6, 7, 8, 9);
	Mat3 mat5(mat2);
	Mat3 mat6(1, -1, 0, 2, 5, -3, 0, 5, 4);

	// Teste output
	cout << "Vector4 1: " << test1 << endl;
	cout << "Vector4 2: " << test2 << endl;
	cout << "Vector4 3: " << test3 << endl;
	cout << "Vector4 4: " << test4 << endl;

	cout << "Vector 4: " << teste4 << endl;
	cout << "Vector 5: " << teste5 << endl;

	cout << "Matriz 4: " << mat4 << endl;
	cout << "Matriz 5: " << mat5 << endl;

	mat4 /= 5;
	cout << "Atribuição " << mat4 << endl;
	//cout << "Soma com atribuição " <<   << endl;
	
	/*
	cout << "Matriz 1: " << mat1 << endl;
	cout << "Matriz 2: " << mat2 << endl;
	cout << "Matriz 3: " << mat3 << endl;
	cout << "Matriz 5: " << mat5 << endl;

	Mat3 sumMatrices = mat4 + mat3;
	Mat3 subMatrices = mat4 - mat3;
	Mat3 multMatrixScalar = mat3 * 2;
	Vec3 multMatrixVector = mat4 * teste1;
	Mat3 multMatrixMatrix = mat4 * mat4;
	Mat3 divMatrixScalar = mat4 / 2;


	cout << "Soma: " << sumMatrices << endl;
	cout << "Subtração: " << subMatrices << endl;
	cout << "Multiplicação por escalar: " << multMatrixScalar << endl;
	cout << "Multiplicação por vetor: " << multMatrixVector << endl;
	cout << "Multiplicação por matriz: " << multMatrixMatrix << endl;
	cout << "Divisão por escalar: " << divMatrixScalar << endl;
	
	cout << Mat3::transpose(mat4) << endl;
	


	cout << "Matriz 1: " << mat2 << endl;
	Vec3 resultado = teste + teste2;
	Vec3 resultadoSub = teste - teste2;
	Vec3 resultadoMul = teste2 * 6;
	Vec3 resultadoDiv = teste / 2.0;
 */

	//teste[2] = 4.0;
	
	/*
	
	cout << teste[3] << endl;
	cout << resultado[2] << endl;
	cout << resultadoSub[2] << endl;
	cout << resultadoMul[2] << endl; 
	cout << resultadoDiv[2] << endl;
	
	*/

	/*
	cout << "Dot: " << Vec3::dot(teste, teste2) << endl;

	cout << "Lenght: " << Vec3::length(teste) << endl;

	cout << "Normalize: " << Vec3::normalize(teste) << endl;

	cout << "Div: " << resultadoDiv << endl;

	teste += teste2;

	cout << "+=: " << teste << endl;

	teste *= 2;

	cout << "*=: " << teste << endl;

	teste /= 4;

	cout << teste << endl;

	teste = teste2;

	cout << teste << endl;


	Vec3 rotateVec(1, 0, 0);
	Mat3 mat_rotated = mat2.rotate(rotateVec, M_PI/2);

	cout << mat_rotated;
	*/

	return 0;
}