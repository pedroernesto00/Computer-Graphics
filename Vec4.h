#ifndef VEC4_H
#define VEC4_H

#include <iostream>
#include <cmath>

using namespace std;

class Vec4
{
	
private:
	float x,
		  y,
		  z,
		  w;

public:

	Vec4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}


	Vec4(int a)
	{
		x = a;
		y = a;
		z = a;
		w = a;
	}

	Vec4(float a, float b, float c, float d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}

	Vec4(const Vec4& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}

	


	/* -----------------------------------------------------------------------------------------------------
                                                     Operadores
         	                  
	--------------------------------------------------------------------------------------------------------*/


	friend ostream& operator << (ostream& out, const Vec4& vetor)
	{
		return out << "[" << vetor.x << ", " << vetor.y << ", " << vetor.z << ", " << vetor.w << "]" << endl;
	}


	float operator [] (int index) const
	{
		switch(index % 4) 
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
			case 3:
				return w;
				break;	
			default:
				break;

		}
	}

	float& operator [] (int index)
	{
		switch(index % 4)
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
			case 3:
				return w;
				break;
			default:
				break;

		}
	}


	const Vec4 operator +(const Vec4& a) const 
	{
		Vec4 novoVetor(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w);
		return novoVetor;
	}

	
	const Vec4 operator - (const Vec4& a) const 
	{
		Vec4 novoVetor(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w);
		return novoVetor;
	}

	const Vec4 operator * (float a) const 
	{
		Vec4 novoVetor(this->x * a, this->y * a, this->z * a, this->w * a);
		return novoVetor;
	}

	const Vec4 operator / (float a) const 
	{
		Vec4 novoVetor(this->x / a, this->y / a, this->z / a, this->w / a);
		return novoVetor;
	}

	const Vec4& operator=(const Vec4& a) 
	{
		
		this->x = a[0];
		this->y = a[1];
		this->z = a[2];
		this->w = a[3];
		
		return *this;
	}

	const Vec4& operator+=(const Vec4& a)
	{
		*this = *this + a;

		return *this;
	}

	const Vec4& operator-=(const Vec4& a)
	{
		*this = *this - a;

		return *this;
	}

	const Vec4& operator*=(float a) 
	{
		*this = *this * a;

		return *this;
	}

	const Vec4& operator/=(float a)
	{
		*this = *this / a;

		return *this;
	}



/*  ---------------------------------------------------------------------------------------------------------------------------------------

  															Outras operações

  ------------------------------------------------------------------------------------------------------------------------------------------*/





	static float dot(const Vec4& vetorA, const Vec4& vetorB)

	{
		return (vetorA[0] * vetorB[0] + vetorA[1] * vetorB[1] + vetorA[2] * vetorB[2] + vetorA[3] * vetorB[3]);
	}

	static float length(const Vec4& vetor)
	{
		return (sqrt(dot(vetor, vetor)));
	}

	static const Vec4 normalize(const Vec4& vetor) 
	{
		return (vetor / length(vetor));
	}

	//const Vec4



};



#endif