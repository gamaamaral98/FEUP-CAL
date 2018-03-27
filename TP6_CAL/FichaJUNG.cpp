#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
	GraphViewer *gv = new GraphViewer(600,600,true);
	gv->setBackground("background.jpg");
	gv->createWindow(600,600);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);

	gv->addEdge(0,0,1,EdgeType::DIRECTED);

	gv->removeNode(1);

	gv->addNode(2);

	gv->addEdge(1,0,2,EdgeType::DIRECTED);
	gv->setVertexLabel(2,"Isto é um nó");

	gv->setEdgeLabel(1,"Isto é uma aresta");

	gv->setVertexColor(2, "green");

	gv->setEdgeColor(1, "yellow");
	gv->rearrange();
}

void exercicio2()
{
	GraphViewer *gv = new GraphViewer(600,600,false);
	gv->createWindow(600,600);

	gv->addNode(0, 300, 50);
	gv->addNode(1, 318, 58);
	gv->addNode(2, 325, 75);
	gv->addNode(3, 318, 93);
	gv->addNode(4, 300, 100);
	gv->addNode(5, 282, 93);
	gv->addNode(6, 275, 75);
	gv->addNode(7, 282, 58);
	gv->addNode(8, 150, 200);
	gv->addNode(9, 300, 200);
	gv->addNode(10, 450, 200);
	gv->addNode(11, 300, 400);
	gv->addNode(12, 200, 550);
	gv->addNode(13, 400, 550);

	gv->addEdge(0,0,1,EdgeType::DIRECTED);
	gv->addEdge(1,1,2,EdgeType::DIRECTED);
	gv->addEdge(2,2,3,EdgeType::DIRECTED);
	gv->addEdge(3,3,4,EdgeType::DIRECTED);
	gv->addEdge(4,4,5,EdgeType::DIRECTED);
	gv->addEdge(5,5,6,EdgeType::DIRECTED);
	gv->addEdge(6,6,7,EdgeType::DIRECTED);
	gv->addEdge(7,7,0,EdgeType::DIRECTED);
	gv->addEdge(8,4,9,EdgeType::DIRECTED);
	gv->addEdge(9,9,8,EdgeType::DIRECTED);
	gv->addEdge(10,9,10,EdgeType::DIRECTED);
	gv->addEdge(11,9,11,EdgeType::DIRECTED);
	gv->addEdge(12,11,12,EdgeType::DIRECTED);
	gv->addEdge(13,11,13,EdgeType::DIRECTED);

	/*
	 * Para que a alteração seja perceptível é necessário colocar a "dormir" antes
	 * da execução do comando.
	 */

	Sleep(1000);
	gv->removeNode(12);
	gv->rearrange();

	Sleep(1000);
	gv->removeNode(13);
	gv->rearrange();

	Sleep(1000);
	gv->addNode(14, 250, 550);
	gv->rearrange();

	Sleep(1000);
	gv->addNode(15, 350, 550);
	gv->rearrange();


	int j = 14;
	for(int i = 0; i < 2; i++){
		Sleep(1000);
		gv->removeNode(j);
		gv->rearrange();

		j++;

		Sleep(1000);
		gv->removeNode(j);
		gv->rearrange();

		j++;
		Sleep(1000);
		gv->addNode(j, 250, 550);
		gv->rearrange();

		j++;
		Sleep(1000);
		gv->addNode(j, 350, 550);
		gv->rearrange();

		j--;
	}
	Sleep(100);
	gv->addEdge(j,11,j,EdgeType::DIRECTED);
	gv->rearrange();
	j++;

	Sleep(100);
	gv->addEdge(j,11,j,EdgeType::DIRECTED);
	gv->rearrange();

}

void exercicio3()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);
 //Para Nodes: id, coord x, coord y;
 //Para Arestas: id, idNodeOrigem, idNodeDestino;
	std::ifstream nodesFile, edgeFile;
	nodesFile.open("nos.txt");
	edgeFile.open("arestas.txt");

	if(!nodesFile.good())
		std::cout << "Could not open!" << endl;

	int id, x, y;
	std::string line;

	while(std::getline(nodesFile, line)){

		std::stringstream ss(line);
		std::string aux;
		std::stringstream auxSS;
		//id
		std::getline(ss, aux, ';');
		auxSS << aux;
		auxSS >> id;

		aux.clear();
		auxSS.clear();
		auxSS.str(std::string());

		//coord x
		std::getline(ss, aux, ';');
		auxSS << aux;
		auxSS >> x;

		aux.clear();
		auxSS.clear();
		auxSS.str(std::string());

		//coord Y
		std::getline(ss, aux, '\n');
		auxSS << aux;
		auxSS >> y;

		aux.clear();
		auxSS.clear();
		auxSS.str(std::string());

		gv->addNode(id, x, y);
	}
	if(!edgeFile.good())
		std::cout << "Could not open!" << endl;

	int ide, idorigem, iddest;
	std::string line1;

	while(std::getline(edgeFile, line1)){
		std::stringstream ss(line);
		std::string aux;
		std::stringstream auxSS;
		//id
		std::getline(ss, aux, ';');
		auxSS << aux;
		auxSS >> ide;

		aux.clear();
		auxSS.clear();
		auxSS.str(std::string());

		//coord x
		std::getline(ss, aux, ';');
		auxSS << aux;
		auxSS >> idorigem;

		aux.clear();
		auxSS.clear();
		auxSS.str(std::string());

		//coord Y
		std::getline(ss, aux, '\n');
		auxSS << aux;
		auxSS >> iddest;

		aux.clear();
		auxSS.clear();
		auxSS.str(std::string());

		gv->addNode(ide, idorigem, iddest);
	}
}


int main() {
	//exercicio1();
	//exercicio2();
	exercicio3();
	getchar();
	return 0;
}
