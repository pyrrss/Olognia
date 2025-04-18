#include <iostream>
#include <sstream>
#include <deque>

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
	std::deque<Mob> minions;
	Mob heroe;

	std::cout << "Ingrese la vida del mechon = ";
	std::cin >> heroe.health;

	std::cout << "Ingrese la cantidad de esbirros = ";
	std::cin >> n;

	for(int i = 0; i < n; i++) minions.push_front(Mob{0,0,0,0,0,0});
	
	std::cout << "Indique la vida de los esbirros = ";
	for (int i = 0; i < n; i++) std::cin >> minions[i].health;

	std::cout << "Indique el daño de los esbirros = ";
	for (int i = 0; i < n; i++) std::cin >> minions[i].damage;

	std::cout << "Indique si son CANO = ";
	for (int i = 0; i < n; i++) std::cin >> minions[i].CANO;

	while(!minions.empty()){
		heroe.acomulatedDamage += std::min(heroe.damage, minions.front().health);
		minions.front().health -= std::min(heroe.damage, minions.front().health);
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
			std::cout << "RIP mechon" << std::endl;
			return 0;
		}
	}
	std::cout << heroe.acomulatedDamage << std::endl << "EZ pizi" << std::endl;	
};