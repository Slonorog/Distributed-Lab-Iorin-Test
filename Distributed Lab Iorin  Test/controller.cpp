#include "controller.h"
#include"Time.h"
#include "Path.h"
#include <fstream>
#include <set>
Controller::Controller()
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			Matr[i][j] = 0;
}

Controller::~Controller()
{
}

void Controller::Load(const char * _path)
{
	/*
	FILE* f = fopen(_p, "r");
	char buf[100];
	buf[0] = 0;
	while (strcmp("<TrainLegs>",buf))
	fscanf(f, "%s",buf);

	while (!feof(f)) {
		int _id=0; int _DSid; int _ASid; double _p;  
		unsigned short _hA, _mA, _sA;
		unsigned short _hD, _mD, _sD;
		
		//<TrainLeg TrainId = "1025" DepartureStationId = "1921"  ArrivalStationId = "1902" 
		//Price = "164.65" ArrivalTimeString = "07:08:00" DepartureTimeString = "22:20:00"></TrainLeg> 
		fscanf(f, "<TrainLeg TrainId = \"%d\" DepartureStationId = \"%d\"  ArrivalStationId = \"%d\" Price = \"%f\" ArrivalTimeString = \"%d:%d:%d\" DepartureTimeString = \"%d:%d:%d\"></TrainLeg>",
			&_id, &_DSid, &_ASid,&_p, &_hA, &_mA, &_sA, &_hD, &_mD, &_sD);
		Time _DTS(_hD, _mD, _sD),  _ATS(_hA, _mA, _sA);
		TrainLegs.push_back(std::make_unique<TrainLeg>(_id, _DSid, _ASid, _p, _DTS, _ATS));
	}
		/*fscanf_s( pFile, " %*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; 
		binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];"
		,&verticesData.pos.x, &verticesData.pos.y, &verticesData.pos.z, &verticesData.uv.x, &verticesData.uv.y);*/
	
	std::ifstream fin(_path); 
	char b[50];
	fin.getline(b, 50); 
	fin.getline(b, 50);
	std::set<int> idlist;
	char *buff = "";
	while (1) {
		int _id ; int _DSid; int _ASid; double _p;
		buff = new char[256];
		char * del=buff;
		fin.getline(buff, 256);
		if (!strcmp("</TrainLegs>", buff))
			break;
		int size = strlen(buff);
		buff = strtok(buff, "\"");
		buff = strtok(0, "\"");
		_id = atoi(buff);
		buff = strtok(0, "\"");
		buff = strtok(0, "\"");
		_DSid = atoi(buff);
		idlist.insert(_DSid);
		buff = strtok(0, "\"");
		buff = strtok(0, "\"");
		_ASid = atoi(buff);
		buff = strtok(0, "\"");
		buff = strtok(0, "\"");
		_p = atof(buff);
		buff = strtok(0, "\"");
		buff = strtok(0, "\"");
		Time _ATS(buff);
		buff = strtok(0, "\"");
		buff = strtok(0, "\"");		
		Time _DTS(buff);
		_ATS.Init();
		_DTS.Init();
		delete[] del;
		TrainLegs.push_back(std::unique_ptr<TrainLeg>(new TrainLeg(_id, _DSid, _ASid, _p, _ATS, _DTS)));
		//TrainLegs.push_back(std::make_unique<TrainLeg>(_id,  _DSid, _ASid, _p, _ATS, _DTS));
		
	}
	fin.close(); 
}

void Controller::makeMatrPrice()
{
	
	//1902 1909 1921 1929 1937 1981
	for (auto &it : TrainLegs) {
		int idD; int idA;
		switch (it->DepartureStationId)
		{
		case(1902) :
			idD = 0;
			break;
		case(1909) :
			idD = 1;
			break;
		case(1921) :
			idD = 2;
			break;
		case(1929) :
			idD = 3;
			break;
		case(1937) :
			idD = 4;
			break;
		case(1981) :
			idD = 5;
			break;
		}
		switch (it->ArrivalStationId)
		{
		case(1902) :
			idA = 0;
			break;
		case(1909) :
			idA = 1;			
			break;
		case(1921) :
			idA = 2;
			break;
		case(1929) :
			idA = 3;
			break;
		case(1937) :
			idA = 4;
			break;
		case(1981) :
			idA = 5;
			break;
		}
		if (Matr[idD][idA] > it->Price|| Matr[idD][idA]==0) {
			Matr[idD][idA] = it->Price;
		}
	}
}

void Controller::DeikstraforPriceLess()
{
	for (int index = 0; index < 6; index++) {
		Path distance[6];
		int count, indexC, i, u, m = index + 1;
		bool visited [6];
		for (i = 0; i < 6; i++)
		{
			distance[i].distance = INT_MAX; visited[i] = false;
		}
		distance[index].distance = 0;
		for (count = 0; count < 6 - 1; count++)
		{
			int min = INT_MAX;
			for (i = 0; i < 6; i++)
				if (!visited[i] && distance[i].distance <= min)
				{

					
						char buf[2];
						min = distance[i].distance;
						indexC = i + 1;
						/*if (Matr[m - 1][i] > 0&& distance[i].path.size()){
							distance[i].path = itoa(m, buf, 10);
							distance[i].path += '>';
							distance[i].path += itoa(indexC, buf, 10);
							distance[i].path += ' ';
						}*/
					
				}
			u = indexC - 1;
			visited[u] = true;
			for (i = 0; i < 6; i++)
				if (!visited[i] && distance[u].distance != INT_MAX &&Matr[u][i] &&
					distance[u].distance + Matr[u][i] < distance[i].distance) {
					char buf[2];
					distance[i].distance = distance[u].distance + Matr[u][i];
					bool flag=0;
					for (int j = 0; j < distance[i].path.size(); j+=4) {

						char a = distance[i].path[j];
						char b = distance[u].path[j];
						if ( a == b  ) {
							flag = 1;
							break;
						}

					}
					if (flag) {
						distance[i].path = distance[u].path;
					}
					else
					distance[i].path += distance[u].path;
					distance[i].path += itoa(u+1, buf, 10);
					distance[i].path += '>';
					distance[i].path += itoa(i+1, buf, 10);
					distance[i].path += ' ';

				}
		}
		std::cout << "count:\t\n";
		for (i = 0; i < 6; i++) if (distance[i].distance != INT_MAX&&distance[i].distance != 0) {
			std::cout << m << " > " << i + 1 << " Price: " << distance[i].distance << std::endl;
			std::cout << "Marshrut = " << distance[i].path << std::endl;
		}
		else if(i!= index)
			std::cout << m << " > " << i + 1 << " = " << "marshrut nedostupen" << std::endl;
	}
}
