#include <rpc/client.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

char tab1[6][6];
char tab2[6][6];

using namespace std;

int main(int argc, const char **argv){
	bzero(tab2, 36);
	rpc::client cli("127.0.0.1", 8000);

	int id = cli.call("logar").as<int>();

	int vx = 2;
	int vy = 3;
	cli.call("positionar", id, vx, vy).as<int>();

	string gg;
	int ataque_p[2];
	while((gg = cli.call("ganhador").as<string>()) == "-"){
		for(int x=0; x<6; x++){
			for(int y=0; y<6; y++){
				cout << "[" << (tab2[x][y] == 0 ? " " : (tab2[x][y] == 2 ? "x" : "o")) << "]";
			}
			cout << endl;
		}
		
		cin >> ataque_p[0];
		cin >> ataque_p[1];
		int atk = cli.call("atacar", id, ataque_p[0], ataque_p[1]).as<int>();
		if(atk == 0){
			cout << "espere sua vez" << endl;
			continue;
		}
		if(atk == 1){
			tab2[ataque_p[0]][ataque_p[1]] = 1;
		}else{
			cout << "errou!" << endl;
			tab2[ataque_p[0]][ataque_p[1]] = 2;
		}
	}

	cout << gg << endl;

	return 0;
}
