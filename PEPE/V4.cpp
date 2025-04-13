#include <iostream>
#include <sstream>
#include <string>
#include <deque>

using namespace std;

struct Mob{
	int health = 0;
	int damage = 2;
	int CANO = 0;
	int enemiesDefeated = 0;
	int acomulatedDamage = 0;
	int hits = 0;	
};

int main(){
	int n;
	string auxString;

	deque<Mob> minions;
	Mob heroe;

	cout << "Ingrese la vida del mechon = ";
	cin >> heroe.health;

	cout << "Ingrese la cantidad de esbirros = ";
	cin >> n;

	for(int i = 0; i < n; i++) minions.push_front(Mob{0,0,0,0,0,0});
	
	cout << "Indique la vida de los esbirros = ";
	for (int i = 0; i < n; i++) cin >> minions[i].health;

	cout << "Indique el daño de los esbirros = ";
	for (int i = 0; i < n; i++) cin >> minions[i].damage;

	cout << "Indique si son CANO = ";
	for (int i = 0; i < n; i++) cin >> minions[i].CANO;

	while(!minions.empty()){
		heroe.acomulatedDamage += min(heroe.damage, minions.front().health);
		minions.front().health -= min(heroe.damage, minions.front().health);
		heroe.health -= minions.front().damage;
		minions.front().hits += 1;
		if(minions.front().hits == 2 && minions.front().CANO == 1){
			minions.front() = {minions.front().health - 1, minions.front().damage - 1, 0, 0 ,0};
			minions.push_front(minions.front());
		}
		if(minions.front().health <= 0){
			minions.pop_front();
			heroe.enemiesDefeated += 1;
			if (heroe.enemiesDefeated % 5 == 0){
				heroe.damage += 1;
			}
		}
		if(heroe.health <= 0){
			cout << "RIP mechon" << endl;
			return 0;
		}
	}
	cout << heroe.acomulatedDamage << endl << "EZ pizi" << endl;	
};