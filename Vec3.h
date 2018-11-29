#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

using namespace std;

class Vec3
{
	
private:
	float x,
		  y,
		  z;

public:

	Vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vec3(int a)
	{
		x = a;
		y = a;
		z = a;
	}


	Vec3(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}

	Vec3(const Vec3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	


	/* -----------------------------------------------------------------------------------------------------
                                                     Operadores
         	                  
	--------------------------------------------------------------------------------------------------------*/


	friend ostream& operator << (ostream& out, const Vec3& vetor)
	{
		return out << "[" << vetor.x << ", " << vetor.y << ", " << vetor.z << "]" << endl;
	}


	float operator [] (int index) const
	{
		switch(index % 3) 
		{
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

	float& operator [] (int index)
	{
		switch(index % 3)
		{
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


	const Vec3 operator +(const Vec3& a) const 
	{
		Vec3 novoVetor(this->x + a.x, this->y + a.y, this->z + a.z);
		return novoVetor;
	}

	
	const Vec3 operator - (const Vec3& a) const 
	{
		Vec3 novoVetor(this->x - a.x, this->y - a.y, this->z - a.z);
		return novoVetor;
	}

	const Vec3 operator * (float a) const 
	{
		Vec3 novoVetor(this->x * a, this->y * a, this->z * a);
		return novoVetor;
	}

	const Vec3 operator * (Vec3& v) const {
		Vec3 novoVetor(this->x * v[0], this->y * v[1], this->z * v[2]);
		return novoVetor;
	}

	const Vec3 operator / (float a) const 
	{
		Vec3 novoVetor(this->x / a, this->y / a, this->z / a);
		return novoVetor;
	}

	const Vec3& operator=(const Vec3& a) 
	{
		
		this->x = a[0];
		this->y = a[1];
		this->z = a[2];
		
		return *this;
	}

	const Vec3& operator+=(const Vec3& a)
	{
		*this = *this + a;

		return *this;
	}

	const Vec3& operator-=(const Vec3& a)
	{
		*this = *this - a;

		return *this;
	}

	const Vec3& operator*=(float a) 
	{
		*this = *this * a;

		return *this;
	}

	const Vec3& operator/=(float a)
	{
		*this = *this / a;

		return *this;
	}



/*  ---------------------------------------------------------------------------------------------------------------------------------------

  															Outras operações

  ------------------------------------------------------------------------------------------------------------------------------------------*/




	static float dot(const Vec3& vetorA, const Vec3& vetorB)
	{
		return (vetorA[0] * vetorB[0] + vetorA[1] * vetorB[1] + vetorA[2] * vetorB[2]);
	}
	
	static Vec3 at(const Vec3 &vetorA, const Vec3 &vetorB)
	{
		return Vec3(vetorA[0] * vetorB[0], vetorA[1] * vetorB[1], vetorA[2] * vetorB[2]);
	}

	static float length(const Vec3& vetor)
	{
		return (sqrt(dot(vetor, vetor)));
	}

	static const Vec3 normalize(const Vec3& vetor) 
	{
		return (vetor / length(vetor));
	}

	static const Vec3 cross(const Vec3& vetorA, const Vec3& vetorB)
	{
		return Vec3(

			vetorA[1] * vetorB[2] - vetorB[1] * vetorA[2], 
			
			vetorA[2] * vetorB[0] - vetorB[2] * vetorA[0], 

			vetorA[0] * vetorB[1] - vetorB[0] * vetorA[1]

			);
	}


	static const Vec3 spherical(const Vec3& vetor) //Conversão de coordenadas cartesianas para coordenadas esféricas 
	{
		float p = sqrt(vetor[0] * vetor[0] + vetor[1] * vetor[1] + vetor[2] * vetor[2]);

		return Vec3(

			p,

			acos(vetor[2] / p),

			atan(vetor[1]/vetor[0])


			);
	}


	static const Vec3 cartesian(const Vec3& vetor) // Conversão de coordenadas esféricas para coordenadass cartesianas
	{
		return Vec3(

			vetor[0] * sin(vetor[1]) * cos(vetor[2]),
			vetor[0] * sin(vetor[1]) * sin(vetor[2]),
			vetor[0] * cos(vetor[1])


			);
	}



};



#endif