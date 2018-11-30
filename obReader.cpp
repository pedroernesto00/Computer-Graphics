#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>



using namespace std;


/*
	ATENÇÃO: Compilar usando -std=c++11
*/

/* TO-DO 

	1) Ler a posição de cada vértice
	2) Para cada posição lida, gerar um objeto da classe Ponto
	3) Guardar ponto num vector de Pontos


	4) Ler informação de cada vetor normal
	5) Para cada informação lida, gerar um objeto da classe Vetor
	6) Guarda vetor num vector de Vetor

	7) Ler as informações de cada face
	8) Para cada face ler: índice dos vértices no vector de vértices, índice da normal no vector de Vetor
	9) Gerar um objeto da classe face com as informações acima.


	10) Quando todas as faces forem criadas, gerar o objeto da classe Cubo.


	OBS.: Escrever cada uma das informações acima num .h

*/


// Declarar os containers que serão utilizados para o processamento do arquivo. 


vector<string> pontos;
vector<string> normais;
vector<string> faces;

void lerObj(string path)
{
	ifstream obj;
	obj.open(path);

	if(!obj.good())
	{
		cout << "Não foi possível abrir o arquivo!" << endl;
		exit(1);
	}

	while (!obj.eof())
	{
		string linha;
		getline(obj, linha);
		string tipo = linha.substr(0, 2);

		if(tipo.compare("v ") == 0)
		{
			char* l = new char[linha.size() + 1];
			memcpy(l, linha.c_str(), linha.size() + 1);
			strtok(l, " "); 

			float* vertices = new float[3];
			
			for(int i = 0; i < 3; i++)
			{
				vertices[i] = atof(strtok(NULL, " "));
			}

			stringstream objPonto;
		 	objPonto << "Point( " << vertices[0] << ", " << vertices[1] << ", " << vertices[2] << " )";

		 	//cout << vertices[0] << ", " << vertices[1] << ", " << vertices[2] << endl;
			
			pontos.push_back(objPonto.str());

			//cout << objPonto.str() << endl;

			delete[] l;

			objPonto.str("");


		}

	


		if(tipo.compare("vn") == 0)
		{
			char *l = new char[linha.size() + 1];
			memcpy(l, linha.c_str(), linha.size()+1);
			strtok(l, " ");

			float* coord = new float[3];

			for (int i = 0; i < 3; i++)
			{
				coord[i] = atof(strtok(NULL, " "));
			}

			stringstream objNormal;
			objNormal << "Vetor( " << coord[0] << ", " << coord[1] << ", " << coord[2] << " )";

			normais.push_back(objNormal.str());

			delete[] l;

			objNormal.str("");
		}

		if(tipo.compare("f ") == 0)
		{
			char *l = new char[linha.size() + 1];
			memcpy(l, linha.c_str(), linha.size()+1);
			strtok(l, " ");

			float* coord = new float[9];

			
			for (int i = 0; i < 6; i++)
			{
				
				coord[i] = atof(strtok(NULL ," /"));
			}


			stringstream objFace;


			//objFace << "Face( " << pontos[coord[0] - 1] << ", " << pontos[coord[3] - 1] << ", " << pontos[coord[6] - 1] << ", " << normais[coord[2] - 1] << " )";
			objFace << "Triangle( " << pontos[coord[0] - 1] << ", " << pontos[coord[2] - 1] << ", " << pontos[coord[4] - 1] << ", " << "triangle_material" << " )";

			faces.push_back(objFace.str());

			delete[] l;

			objFace.str("");
		}

		



	}
}


void writeObject(string path)
{
	ofstream outObj;

	outObj.open(path);

	
	if(!outObj.good())
	{
		cout << "Erro ao abrir o arquivo!" << endl;
		exit(1); 
	}

	/*
	for (auto p : pontos)
	{
		outObj << p << endl;
		
	}

	for (auto n : normais)
	{
		outObj << n << endl;
	}

	*/

	outObj << "Vec3 triangle_env_material(0.9, 0.9, 0.9); // Material's enviroment component factors\nVec3 triangle_dif_material(0.9, 0.9, 0.9);   // Material's difuse component factors\nVec3 triangle_spe_material(0.9, 0.9, 0.9);   // Material's specular component factors\nMaterial triangle_material(triangle_env_material, triangle_dif_material, triangle_spe_material);\n";

	outObj << "vector<Triangle> faces= { ";
	
	for (auto f : faces)
	{
		outObj << f <<  ", " << endl;
	}

	outObj << "}; " << endl;


	outObj.close();


}




int main(int argc, char const *argv[])
{
	
	if(argc > 1)
	{
		string objName = argv[1];
		string pathRead = "source/" + objName + ".obj";
		string pathWrite = "product/" + objName + "Model.h";  
		lerObj(pathRead);
		cout << "saiu" << endl;
		writeObject(pathWrite);

	}

	return 0;
}