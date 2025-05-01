#include <iostream>
#include <deque>

// -> struct que representa a los mobs/entidades
struct Mob{
	int health = 0;
	int damage = 2;
	int isCano = 0;
	int enemiesDefeated = 0;
	int accumulatedDamage = 0;
	int hits = 0;	
};

int main(){
	int n;
	std::deque<Mob> minions; // -> adt deque para manejar minions
	Mob hero;

	std::cin >> hero.health;

	std::cin >> n;

	for(int i = 0; i < n; i++) minions.push_front(Mob{0 , 0, 0, 0, 0, 0});

	for (int i = 0; i < n; i++) std::cin >> minions[i].health;
	for (int i = 0; i < n; i++) std::cin >> minions[i].damage;
	for (int i = 0; i < n; i++) std::cin >> minions[i].isCano;

	while(!minions.empty()) {
        Mob& currentEnemy = minions.front();

        // -> héroe ataca al enemigo (para cálculo de daño al enemigo se procura evitar vida negativa)
        int damageToEnemy = std::min(hero.damage, currentEnemy.health);
		hero.accumulatedDamage += damageToEnemy;
		minions.front().health -= damageToEnemy;

        // -> enemigo ataca al héroe
		hero.health -= currentEnemy.damage;
		minions.front().hits++;
        
        // -> se maneja el caso en el que el enemigo es un cano y debe dividirse
		if(currentEnemy.hits == 2 && currentEnemy.isCano == 1 && currentEnemy.health > 1) {
			Mob newEnemy = {currentEnemy.health - 1, currentEnemy.damage - 1, 0, 0 ,0};
			minions.front() = newEnemy;
            minions.push_front(newEnemy);
		}

        // -> se comprueba si el enemigo murió
		if(minions.front().health <= 0) {
			minions.pop_front();
			hero.enemiesDefeated++;
            // -> cada 5 enemigos derrotados se aumenta en 1 el daño del héroe
			if (hero.enemiesDefeated % 5 == 0) {
				hero.damage++;
			}
		}

        // -> se comprueba si el héroe muere sin cumplir su cometido
		if(hero.health <= 0 && !minions.empty()) {
			std::cout << hero.accumulatedDamage << std::endl << "RIP mechon" << std::endl;
			return 0;
		}
	}

	std::cout << hero.accumulatedDamage << std::endl << "EZ pizi" << std::endl;	

    return 0;
}
