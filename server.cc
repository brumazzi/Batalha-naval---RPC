#include <rpc/server.h>
#include <iostream>
#include <cstring>

using namespace std;

typedef struct {
	int id;
	string login;
	string senha;
	int ponto=0;
} Users;

Users users[2];
int atacante = 2;
int ganhador = 0;

int login(){
	static bool primeiro = true;
	if(primeiro){
	/*	users[0].id = 1;
		users[0].login = user;
		users[0].senha = pass;*/
		primeiro = false;
		return 1;
	}else{
/*		users[1].id = 2;
		users[1].login = user;
		users[1].senha = pass;*/
		return 2;
	}
}

/*      Barcos      */
char tab1[6][6];
char tab2[6][6];

int positionar(int id, int px, int py){
	/*if(atacante == id)
		return 0;*/

	if(id == 1){
		tab1[px][py] = 1;
	//	tab1[px][py] = 1;
		atacante = 1;
	}else{
		tab2[px][py] = 1;
	//	tab2[px][py] = 1;
		atacante = 2;
	}

	return 1;
}

/*  atacar  */

int atacar(int id, int px, int py){
	if(atacante == id)
		return 0;

	if(id == 1){
		atacante = 1;
		if(tab2[px][py] != 0){
			users[0].ponto++;
			if(users[0].ponto == 1)
				ganhador = 1;
			return 1;
		}
	}else{
		atacante = 2;
		if(tab1[px][py] != 0){
			users[1].ponto++;
			if(users[1].ponto == 1)
				ganhador = 2;
			return 1;
		}
	}
	return 2;
}

string _ganhador(){
	if(ganhador == 1){
		return "Jogador 1 ganhou";
	}else if(ganhador == 2)
		return "jogador 2 ganhou";

	return "-";
}

int main(int argc, const char **argv){
	bzero(tab1,36);
	bzero(tab2,36);
	rpc::server server(8000);

	server.bind("logar", &login);
	server.bind("positionar", &positionar);
	server.bind("atacar", &atacar);
	server.bind("ganhador", &_ganhador);

	server.run();
	return 0;
}
