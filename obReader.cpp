#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>



using namespace std;


/*
	ATENÇÃO: Compilar usando -std=c++11
	Ao exportar OBJ, marque apenas as alternativas: write normals e triangulate faces
*/

/* TO-DO 


	OBS.: Escrever cada uma das informações acima num .h


	DONE
	
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



*/


// Declarar os containers que serão utilizados para o processamento do arquivo. 


vector<string> pontos;
vector<string> normais;
vector<string> faces;

void lerObj(string path, string objName)
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
			objFace << "Triangle( " << objName << "_vertices" << "[" << coord[0] << "]" << ", " << objName << "_vertices" << "[" << coord[2] << "]" << ", " << objName << "_vertices" << "[" << coord[4] << "]" << ")";

			faces.push_back(objFace.str());

			delete[] l;
			delete[] coord;

			objFace.str("");
		}

		



	}
}


void writeObject(string path, string objName)
{
	ofstream outObj;

	outObj.open(path, ios::app);

	
	if(!outObj.good())
	{
		cout << "Erro ao criar o header!" << endl;
		exit(1); 
	}

	outObj << "//Setting " << objName << "'s " << "material" << endl; 
	outObj << "Vec3 " << objName << "_env_material" << "(0.9, 0.9, 0.9); // Material's enviroment component factors" << endl;
	outObj << "Vec3 " << objName << "_dif_material" << "(0.9, 0.9, 0.9);   // Material's difuse component factors" << endl;
	outObj << "Vec3 " << objName << "_spe_material" <<  "(0.9, 0.9, 0.9);   // Material's specular component factors " << endl;
	outObj << "Material " << objName << "_material" << "(" << objName << "_env_material" << ", " << objName << "_dif_material" << ", " << objName << "_spe_material"<< ");" << endl;

	outObj << "const int " << objName << "_num_faces = " << faces.size() << ";" << endl;
	outObj << "const int " << objName << "_num_vertices = " << pontos.size() << ";" << endl;
	
	outObj << "Point " << objName << "_vertices[]" << " = { " << endl;
	for (auto p : pontos)
	{
		outObj << "\t" <<  p << ", " << endl;
		
	}

	outObj << "}; " << endl;

	/*
	for (auto n : normais)
	{
		outObj << n << endl;
	}

	*/

	
	

	outObj << "Triangle " << objName << "_faces[]" << " = { " << endl;;
	
	for (auto f : faces)
	{
		outObj << "\t" << f <<  ", " << endl;
	}

	outObj << "}; " << endl;


	outObj << "Model " << objName << "(" << objName << "_num_faces, " << objName << "_num_vertices, " << objName << "_vertices, " << objName << "_faces, " << objName << "_material);" << endl; 


	outObj.close();


}




int main(int argc, char const *argv[])
{
	
	if(argc > 1)
	{
		string objName = argv[1];
		string pathRead = "source/" + objName + ".obj";
		string pathWrite = "product/models.h";  
		lerObj(pathRead, objName);
		writeObject(pathWrite, objName);

	}

	return 0;
}