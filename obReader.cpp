#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <experimental/filesystem>



using namespace std;
namespace fs = experimental::filesystem;


enum Render
{
	RAYCAST,
	OPENGL
};


/*
	ATENÇÃO: Compilar usando -lstdc++fs -std=c++17
	Ao exportar OBJ, marque apenas as alternativas: write normals e triangulate faces
*/



vector<string> pontos;
vector<string> normais;
vector<string> faces;

void lerObj(string path, string objName, Render typeRender)
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
		 	
		 	if(typeRender == RAYCAST) objPonto << "Point( " << vertices[0] << ", " << vertices[1] << ", " << vertices[2] << " )";
		 	else if(typeRender == OPENGL) objPonto << vertices[0] << ", " << vertices[1] << ", " << vertices[2];
		 	
		 	//cout << vertices[0] << ", " << vertices[1] << ", " << vertices[2] << endl;
			
			pontos.push_back(objPonto.str());

			//cout << objPonto.str() << endl;

			delete[] l;
			delete[] vertices;

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
			delete[] coord;

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
			if(typeRender == RAYCAST)objFace << "Triangle( " << objName << "_vertices" << "[" << coord[0] - 1 << "]" << ", " << objName << "_vertices" << "[" << coord[2] - 1 << "]" << ", " << objName << "_vertices" << "[" << coord[4] - 1 << "]" << ")";
			else if(typeRender == OPENGL) objFace << coord[0] - 1 << ", " << coord[2] - 1 << ", " << coord[4] - 1;
			
			faces.push_back(objFace.str());

			delete[] l;
			delete[] coord;

			objFace.str("");
		}

		



	}
}


void writeObject(string path, string objName, Render typeRender)
{
	ofstream outObj;

	outObj.open(path, ios::app);
	
	//Escrita em caso de raycasting

	if(!outObj.good())
	{
		cout << "Erro ao criar o header!" << endl;
		exit(1); 
	}

	if (typeRender == RAYCAST)
	{
		outObj << "//Setting " << objName << "'s " << "material" << endl; 
		outObj << "Vec3 " << objName << "_env_material" << "(0.9, 0.9, 0.9); // Material's enviroment component factors" << endl;
		outObj << "Vec3 " << objName << "_dif_material" << "(0.9, 0.9, 0.9);   // Material's difuse component factors" << endl;
		outObj << "Vec3 " << objName << "_spe_material" <<  "(0.9, 0.9, 0.9);   // Material's specular component factors " << endl;
		outObj << "Material " << objName << "_material" << "(" << objName << "_env_material" << ", " << objName << "_dif_material" << ", " << objName << "_spe_material"<< ");" << endl;
	}	
	
	outObj << "const int " << objName << "_num_faces = " << faces.size() << ";" << endl;
	outObj << "const int " << objName << "_num_vertices = " << pontos.size() << ";" << endl;
	
	if (typeRender == RAYCAST) outObj << "Point " << objName << "_vertices[]" << " = { " << endl;
	else if (typeRender == OPENGL) outObj << "float " << objName << "_vertices[]" << " = {" << endl;
	
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


	if (typeRender == RAYCAST) outObj << "Triangle " << objName << "_faces[]" << " = { " << endl;
	else if(typeRender == OPENGL) outObj << "int " << objName << "_faces[]" << " = {" << endl;
	
	for (auto f : faces)
	{
		outObj << "\t" << f <<  ", " << endl;
	}

	outObj << "}; " << endl;

	if (typeRender == RAYCAST) outObj << "Model " << objName << "(" << objName << "_num_faces, " << objName << "_num_vertices, " << objName << "_vertices, " << objName << "_faces, " << objName << "_material);" << endl; 


	//Escrita em caso de OpenGL

	


	outObj.close();


}


void prepararArquivo(Render typeRender)
{
	/*
		#include <cmath>
		#include <iostream>
		#include "scenario_new.h"



	 */

	ofstream arq;
	string pathOpen = (typeRender == OPENGL ? "product/modelsGL.h" : "product/models.h"); 
	arq.open(pathOpen);

	if (!arq.good())
	{
		cout << "Não foi possivel criar arquivo models.h!" << endl;
		exit(1);
	}

	if(typeRender == RAYCAST) arq << "#include <cmath>" << endl << "#include <iostream>" << endl << "#include \"..\\scenario_new.h\"" << endl;

	arq.close();


}




int main(int argc, char const *argv[])
{
	
	Render typeRender = RAYCAST;
	
	if(argc > 1)
	{
		string tipoEntrada = argv[1];
		if(tipoEntrada == "-o") typeRender = OPENGL;
	}
	

	
	prepararArquivo(typeRender);

	string pathRead = "./source";

	string pathWrite = (typeRender == OPENGL ? "product/modelsGL.h" : "product/models.h");

	for (auto p : fs::directory_iterator(pathRead))
	{
		if(p.path().extension() == ".obj") 
		{
			lerObj(p.path(), p.path().stem(), typeRender);
			writeObject(pathWrite, p.path().stem(), typeRender);
			pontos.clear();
			normais.clear();
			faces.clear();
		} 
	}

	

	/*
	if(argc > 1)
	{
		string objName = argv[1];
		string pathRead = "source/" + objName + ".obj";
		string pathWrite = "product/models.h";  
		lerObj(pathRead, objName);
		writeObject(pathWrite, objName);

	} */

	return 0;
}