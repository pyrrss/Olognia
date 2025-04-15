#include <iostream>
#include <deque>

#include "../ADTS/queue/QueueArray.hpp"
#include "../ADTS/queue/QueueLinkedList.hpp"

struct Mechon
{
    int health;
    int damage = 2;
};

struct Enemy
{
    int health;
    int damage;
    bool is_special;
};

// por ahora lo hare con adts de la std lib
// luego de que funcione lo hare con mis adts
// ya que me falta definir adt iterador para definir forma estándar de iterar

int main()
{
    bool debug = true;

    Mechon mechon;

    // std::cout << "Vida del héroe mechón: ";
    std::cin >> mechon.health; 

    int num_enemies;
    // std::cout << "Número total de esbirros: ";
    std::cin >> num_enemies;
  
    std::deque<Enemy> *enemies = new std::deque<Enemy>();

    // std::cout << "Vida de los esbirros (separada por espacios): ";
    for(size_t current_enemy_index = 0; current_enemy_index < num_enemies; current_enemy_index++)
    {
        Enemy enemy;
        std::cin >> enemy.health;
        enemies->push_back(enemy);
    }

    // std::cout << "Daño de los esbirros (separada por espacios): ";
    for(size_t current_enemy_index = 0; current_enemy_index < num_enemies; current_enemy_index++)
    {
        std::cin >> enemies->at(current_enemy_index).damage;
    }

    // std::cout << "Esbirros especiales (separada por espacios): ";
    for(size_t current_enemy_index = 0; current_enemy_index < num_enemies; current_enemy_index++)
    {
        std::cin >> enemies->at(current_enemy_index).is_special;
    }

    // -> estado de la deque
    if(debug)
    {
        for(Enemy& enemy : *enemies)
        {
            // std::cout << "Vida: " << enemy.health << " Daño: " << enemy.damage << " Especial: " << enemy.is_special << std::endl;
        }
    }


    int total_damage_to_enemies = 0;
    int enemies_defeated = 0;
    int current_enemy_index = 0;

    // -> "game-loop"
    // error que tomó más tiempo fue iterar sobre la deque mientras se modificaba (al dividir enemigo especial)
    // solución fue no iterar sobre deque, sino tomar siempre al enemigo de al frente y listo
    while(!enemies->empty())
    {
        Enemy& enemy = enemies->front();
        if(debug) { std::cout << "Duelo " << current_enemy_index + 1 << std::endl; }
 
        int current_round = 0;
        while(enemy.health > 0 && mechon.health > 0)
        {
            current_round++;
            if(debug){ std::cout << "Ronda " << current_round << std::endl; }


            // -> ataque enemigo a mechon
            int damage_to_mechon = std::min(enemy.damage, mechon.health);
            mechon.health -= damage_to_mechon;

            // -> ataque mechon a enemigo
            int damage_to_enemy = std::min(mechon.damage, enemy.health);
            enemy.health -= damage_to_enemy;
            total_damage_to_enemies += damage_to_enemy;
            
            if(debug)
            {
                std::cout << "Mechon ataca con " << mechon.damage << 
                    " y causa " << damage_to_enemy << 
                    " a enemigo, " << " y recibe " <<
                    damage_to_mechon << " de daño" << std::endl;
            }

            // lo siguiente es manejar caso enemigo especial

            // si el enemigo es especial, luego de recibir 2 ataques, se dividirá en 2 enemigos con 1 menos de vida y ataque
            if(current_round == 2 && enemy.is_special && enemy.health > 0)
            {
                if(debug) { std::cout << "Enemigo especial se divide en 2" << std::endl; }
                Enemy new_enemy_a;

                new_enemy_a.health = enemy.health - 1;
                new_enemy_a.damage = enemy.damage - 1;
                new_enemy_a.is_special = false;

                Enemy new_enemy_b = new_enemy_a;

                enemies->pop_front();
                enemies->push_front(new_enemy_a);
                enemies->push_front(new_enemy_b);
                
                if(debug)
                {
                    std::cout << "Nuevo estado de la deque: " << std::endl;
                    for(Enemy& enemy : *enemies)
                    {
                        std::cout << "Vida: " << enemy.health << " Daño: " << enemy.damage << " Especial: " << enemy.is_special << std::endl;
                    }
                }
                
                break;
            }


            if(debug) { std::cout << "(Daño acumulado : " << total_damage_to_enemies << ")" << std::endl; }
        }

        if(enemy.health <= 0)
        {
            if(debug) { std::cout << "Enemigo derrotado" << std::endl; }
            enemies_defeated++;
            enemies->pop_front();
            current_enemy_index++;    

            // TODO: Hacer que aumente cada 5
            if(enemies_defeated == 6)
            {
                mechon.damage++;
            }

        }

        if(mechon.health <= 0)
        {
            if(debug) { std::cout << "Mechón derrotado" << std::endl; }
            break;
        }


    }
    
    // -> resultados
    std::cout << total_damage_to_enemies << std::endl;

    if(mechon.health <= 0)
    {
        std::cout << "RIP mechon" << std::endl;
        // std::cout << "Enemigos derrotados: " << enemies_defeated << std::endl;
    }
    else
    {
        std::cout << "EZ pizi" << std::endl;
        // std::cout << "Vida restante: " << mechon.health << std::endl;
    }


    delete enemies;
    return 0;
}
