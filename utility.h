#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <cmath>

using namespace std;


typedef struct resultado 
{
	
	double intersecao;
	bool interceptou;

} resultado;

class Vetor
{
private:
	float x;
	float y;
	float z;
	float w;
public:
	
	Vetor(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	Vetor(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 0.0;	

	}
	Vetor()
	{
		this->x = 0.0;
		this->y = 0.0;
		this->z = 0.0;
		this->w = 0.0;
	}



	friend ostream& operator << (ostream& out, const Vetor& v)
	{
		out << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]" << endl;
		return out;
	}

	float operator [] (short unsigned int index) const
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

	const Vetor& operator = (const Vetor& v)
	{
		this->x = v[0];
		this->y = v[1];
		this->z = v[2];
		this->w = v[3];

		return *this;
	}

	const Vetor operator / (float s)
	{

		Vetor v = Vetor(this->x/s, this->y/s, this->z/s);
		
		return v;
	}

	Vetor operator * (Vetor& v)
	{
		Vetor m = Vetor(this->x * v[0], this->y * v[1], this->z * v[2]);

		return m;	
	}

	Vetor operator * (float s)
	{
		Vetor v = Vetor(this->x*s, this->y*s, this->z*s);

		return v;
	}

	Vetor operator - (Vetor& v)
	{
		Vetor m = Vetor(this->x - v[0], this->y - v[1], this->z - v[2]);

		return m;
	}

	Vetor operator + (Vetor& v)
	{
		Vetor m = Vetor(this->x + v[0], this->y + v[1], this->z + v[2]);

		return m;	
	}

	float dot(const Vetor& v) const
	{
		return (this->x * v[0] + this->y * v[1] + this->z * v[2] + this->w * v[3]);
	}

	void normalizar(void)
	{
		*this = *this/sqrt(this->dot(*this));
	}

	const Vetor cross(const Vetor& v) const
	{
		Vetor novoVetor(this->y * v[2] - this->z * v[1], this->z * v[0] - this->x * v[2], this->x * v[1] - this->y * v[0]);
		return novoVetor;
	}
};

class Ponto
{
private:
	float x;
	float y;
	float z;
	float w;
public:

	Ponto(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 1.0f;

	}

	Ponto()
	{
		this->x = 0.0;
		this->y = 0.0;
		this->z = 0.0;
		this->w = 1.0f;
	}

	
	friend ostream& operator << (ostream& out, const Ponto& p)
	{
		out << "(" << "x: " << p[0] << " y: " << p[1] << " z: " << p[2] << " w: " << p[3] << ")" << endl;
		return out;
	}


	float operator [] (short unsigned int index) const
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

	const Ponto& operator = (const Ponto& p)
	{
		x = p[0];
		y = p[1];
		z = p[2];
		w = p[3];

		return *this;
	}

	const Vetor operator - (const Ponto& p) const
	{
		Vetor v;
		float x = this->x - p[0];
		float y = this->y - p[1];
		float z = this->z - p[2];
		v = Vetor(x, y, z, 0.0);
		return v;
	}

};


class Luz
{
private:
	Ponto origem;
	Vetor cor;
public:
	Luz(Ponto o, Vetor c)
	{
		origem = o;
		cor = c;
	}

	Vetor& getCor()
	{
		return this->cor;
	}

	Ponto& getOrigem()
	{
		return this->origem;
	}

	void setOrigem(Ponto& p)
	{
		this->origem = p;
	}
};

class Material
{
private:
	Vetor rAmbiente;
	Vetor rDifusa;
	Vetor rEspecular;
public:
	Material(Vetor a, Vetor d, Vetor e)
	{
		rAmbiente = a;
		rDifusa = d;
		rEspecular = e;
	}

	Material()
	{
		rAmbiente = Vetor(0.0f, 0.0f, 0.0f);
		rDifusa = Vetor(0.0f, 0.0f, 0.0f);
		rEspecular = Vetor(0.0f, 0.0f, 0.0f);
	}

	const Material& operator = (const Material& m)
	{
		this->rAmbiente = m.rAmbiente;
		this->rDifusa = m.rDifusa;
		this->rEspecular = m.rEspecular;

		return *this;
	}

	Vetor& getAmbiente()
	{
		return this->rAmbiente;
	}

	Vetor& getDifusa()
	{
		return this->rDifusa;
	}

	Vetor& getEspecular()
	{
		return this->rEspecular;
	}

	Vetor corAmbiente(Luz l)
	{
		return this->rAmbiente * l.getCor();
	}

	Vetor corDifusa(Luz l, Vetor normal, Vetor fonte)
	{
		normal.normalizar();
		fonte.normalizar();

		float cosineNormalFonte = normal.dot(fonte);


		if(cosineNormalFonte < 0)
			return Vetor(0.0f, 0.0f, 0.0f);
		else
			return (this->rDifusa * l.getCor()) * cosineNormalFonte;
	}

	Vetor corEspecular(Luz l, Vetor normal, Vetor observador, Vetor fonte)
	{
		normal.normalizar();
		observador.normalizar();
		fonte.normalizar();

		Vetor refletido = normal * (2 * (fonte.dot(normal)))  - fonte;

		if(refletido.dot(observador) < 0)
			return Vetor(0.0f, 0.0f, 0.0f);
		else
			return (this->rEspecular * l.getCor()) *  pow((refletido.dot(observador)), 0.6 * 128); // Com índice de espelhamento igual a 1.

	}
};


class Esfera
{

private:
	Ponto centro;
	float raio;
	Material material;

public:
	Esfera(Ponto& c, float r, Material& m)
	{
		this->centro = c;
		this->raio = r;
		this->material = m;

	}

	friend ostream& operator << (ostream& out, const Esfera& e)
	{
		out << "centro: " << e.centro << " raio: " << e.raio << endl;
		return out;
	}

	Ponto getCentro()
	{
		return this->centro;
	}

	float getRaio()
	{
		return this->raio;
	}

	void setCentro(Ponto& c)
	{
		this->centro = c;
	}

	Material& getMaterial()
	{
		return this->material;
	}
	//~Esfera();
	
};


class Face 
{
private:
	Ponto vertice1;
	Ponto vertice2;
	Ponto vertice3;
	Material material;

public:
	Face(Ponto v1, Ponto v2, Ponto v3, Material m)
	{
		vertice1 = v1;
		vertice2 = v2;
		vertice3 = v3;
		material = m;
	}

	Ponto getVertice(unsigned short int t)
	{
		if(t == 1)
		{
			return this->vertice1;
		}

		if(t == 2)
		{
			return this->vertice2;
		}

		if (t==3)
		{
			return this->vertice3;
		}
	}

	void setVertice(unsigned short int t, Ponto& value)
	{
		if(t == 1)
		{
			this->vertice1 =  value;
		}

		if(t == 2)
		{
			this->vertice2 =  value;
		}

		if (t==3)
		{
			this->vertice3 =  value;
		}
	}

	Vetor encontrarNormal(void)
	{
		Vetor aresta1 = this->vertice2 - this->vertice1;
		Vetor aresta2 = this->vertice3 - this->vertice1;

		return aresta1.cross(aresta2);
	}

	resultado intersecaoTriangulo(Vetor v) //V é o vetor que parte do observador para centro do pixel. 
	{
		resultado r = {false, 0};

		Vetor normalTriangulo = this->encontrarNormal();
		normalTriangulo.normalizar();

		double produtoNormalRaio = v.dot(normalTriangulo); //Produto escalar do vetor normal com o vetor v

		//Checar se raio intercepta o plano que contém o triângulo

		if(produtoNormalRaio == 0) // Raio perpendicular à normal do plano 
		{
			r.interceptou = false;
			r.intersecao = 0;
			return r;
		
		} else {

			Vetor origemVertice = this->vertice1 - Ponto(0, 0, 0); //Vetor da origem da câmera para um dos vértices do triângulo (neste caso, o primeiro)
			double tIntersecao = origemVertice.dot(normalTriangulo) / produtoNormalRaio; 

			if (tIntersecao < 0) //O objeto está atrás do observador
			{
				r.interceptou = false;
				r.intersecao = 0;
				return r;
			} 

			//Checar se ponto encontrado está dentro do triângulo.

			Vetor origemAoPonto = v * tIntersecao;
			Ponto pontoIntersecao(origemAoPonto[0], origemAoPonto[1], origemAoPonto[2]); //Esta linha foi necessária para transformar o vetor posição do ponto de interseção em um ponto.

			Vetor aresta1 = this->vertice2 - this->vertice1; //Vetor do vertice1 para o vertice2
			Vetor aresta2 = this->vertice3 - this->vertice2; //Vetor do vertice 2 para o vertice 3
			Vetor aresta3 = this->vertice1 - this->vertice3; //Vetor do vertice 3 para o vertice 1

			Vetor vertice1Ponto = pontoIntersecao - this->vertice1; //Vetor do vértice 1 para o ponto de interseção
			Vetor vertice2Ponto = pontoIntersecao - this->vertice2; //Vetor do vértice 2 para o ponto de interseção
			Vetor vertice3Ponto = pontoIntersecao - this->vertice3; //Vetor do vértice 3 para o ponto de interseção

			if (   (aresta1.cross(vertice1Ponto)).dot(normalTriangulo) > 0 
					
					&& (aresta2.cross(vertice2Ponto)).dot(normalTriangulo) > 0 
					
					&& (aresta3.cross(vertice3Ponto)).dot(normalTriangulo) > 0 ) // Então ponto interceptado está dentro do triângulo e está na face frontal.

			{
				r.interceptou = true;
				r.intersecao = tIntersecao;
			}   else {
				r.interceptou = false;
				r.intersecao = 0;
			}




		}
	
		return r;

	}


};


class Camera
{
private:
	Ponto origem;
	Ponto lookAt;
	Ponto aViewUp;
public:
	Camera(Ponto o, Ponto l, Ponto a)
	{
		origem = o;
		lookAt = l;
		aViewUp = a;

	}

	void  transformarCoordenadas(Esfera& e, Luz& l)
	{
		Vetor lookAt = this->origem - this->lookAt; //Precisa ser normalizado
		Vetor aViewUp = this->aViewUp - this->origem;
		Vetor direita = aViewUp.cross(lookAt); //Precisa ser normalizado
		Vetor paraCima = lookAt.cross(direita); //Precisa ser normalizado;

		lookAt.normalizar(); //Primeiro vetor coluna
		direita.normalizar(); //Segundo vetor coluna
		paraCima.normalizar(); //Terceiro vetor coluna

		cout << lookAt << endl;
		cout << direita << endl;
		cout << paraCima << endl;

		Vetor eye(origem[0], origem[1], origem[2]);

		Vetor escalares(-1 * direita.dot(eye), -1 * paraCima.dot(eye), -1 * lookAt.dot(eye), 1.0f);
		// "Matriz" de transformação das coordenadas dos pontos do objeto, de mundo para câmera.
		Vetor linhaUm(direita[0], direita[1], direita[2], escalares[0]);
		Vetor linhaDois(paraCima[0], paraCima[1], paraCima[2], escalares[1]);
		Vetor linhaTres(lookAt[0], lookAt[1], lookAt[2], escalares[2]);
		//Vetor linhaQuatro(lookat[3], direita[3], paraCima[3], escalares[3]);

		//Representação na classe Vetor do ponto Centro. Necessário nesta implementação para fazer o produto escalar. 
		Vetor centroAntigo(e.getCentro()[0], e.getCentro()[1], e.getCentro()[2], 1.0f);

		// "Multiplicação" da matriz acima com o Ponto Centro da esfera.
		Ponto novoCentro(linhaUm.dot(centroAntigo), linhaDois.dot(centroAntigo), linhaTres.dot(centroAntigo));

		e.setCentro(novoCentro);


		//Representação na classe Vetor do ponto de origem da fonte luminosa. 

		Vetor fonteAntiga(l.getOrigem()[0], l.getOrigem()[1], l.getOrigem()[2], 1.0f);

		// "Multiplicação" da "matriz" acima com o ponto da origem
		
		Ponto novaFonte(linhaUm.dot(fonteAntiga), linhaDois.dot(fonteAntiga), linhaTres.dot(fonteAntiga));

		l.setOrigem(novaFonte);		

	}


	void  transformarCoordenadas(Face& f, Luz& l)
	{
		Vetor lookAt = this->origem - this->lookAt; //Precisa ser normalizado
		Vetor aViewUp = this->aViewUp - this->origem;
		Vetor direita = aViewUp.cross(lookAt); //Precisa ser normalizado
		Vetor paraCima = lookAt.cross(direita); //Precisa ser normalizado;

		lookAt.normalizar(); //Primeiro vetor coluna
		direita.normalizar(); //Segundo vetor coluna
		paraCima.normalizar(); //Terceiro vetor coluna

		cout << lookAt << endl;
		cout << direita << endl;
		cout << paraCima << endl;

		Vetor eye(origem[0], origem[1], origem[2]);

		Vetor escalares(-1 * direita.dot(eye), -1 * paraCima.dot(eye), -1 * lookAt.dot(eye), 1.0f);
		// "Matriz" de transformação das coordenadas dos pontos do objeto, de mundo para câmera.
		Vetor linhaUm(direita[0], direita[1], direita[2], escalares[0]);
		Vetor linhaDois(paraCima[0], paraCima[1], paraCima[2], escalares[1]);
		Vetor linhaTres(lookAt[0], lookAt[1], lookAt[2], escalares[2]);
		//Vetor linhaQuatro(lookat[3], direita[3], paraCima[3], escalares[3]);

		//Representação na classe Vetor do ponto Centro. Necessário nesta implementação para fazer o produto escalar. 
		//Vetor centroAntigo(e.getCentro()[0], e.getCentro()[1], e.getCentro()[2], 1.0f);

		Vetor vertice1Antigo(f.getVertice(1)[0], f.getVertice(1)[1], f.getVertice(1)[2], 1.0f);
		Vetor vertice2Antigo(f.getVertice(2)[0], f.getVertice(2)[1], f.getVertice(2)[2], 1.0f);
		Vetor vertice3Antigo(f.getVertice(3)[0], f.getVertice(3)[1], f.getVertice(3)[2], 1.0f);

		// "Multiplicação" da matriz acima com o Ponto Centro da esfera.
		Ponto novoVerticeUm(linhaUm.dot(vertice1Antigo), linhaDois.dot(vertice1Antigo), linhaTres.dot(vertice1Antigo));
		Ponto novoVerticeDois(linhaUm.dot(vertice2Antigo), linhaDois.dot(vertice2Antigo), linhaTres.dot(vertice2Antigo));
		Ponto novoVerticeTres(linhaUm.dot(vertice3Antigo), linhaDois.dot(vertice3Antigo), linhaTres.dot(vertice3Antigo));
		
		f.setVertice(1, novoVerticeUm);
		f.setVertice(2, novoVerticeDois);
		f.setVertice(3, novoVerticeTres);


		//Representação na classe Vetor do ponto de origem da fonte luminosa. 

		Vetor fonteAntiga(l.getOrigem()[0], l.getOrigem()[1], l.getOrigem()[2], 1.0f);

		// "Multiplicação" da "matriz" acima com o ponto da origem
		
		Ponto novaFonte(linhaUm.dot(fonteAntiga), linhaDois.dot(fonteAntiga), linhaTres.dot(fonteAntiga));

		l.setOrigem(novaFonte);		

	}


};



#endif