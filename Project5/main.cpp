#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "creatures.h"

int main()
{
	// Use this file to add the main flow of code. 
	// Keep it clean using creatures.cpp to create utility functions
	// Remember to free all allocated memory with malloc

	int hp;
	int attack_min;
	int attack_max;
	int armor;

	char* hero_name = (char*)malloc(11 * sizeof(char));

	printf("Hello hero! Welcome to the goblin fighter, please introduce your name: (max 11 characters)\n");
	scanf_s("%s", hero_name, 11);

	printf_s("So you are %s? Alright, now enter your stats in the following order: hp, attack min, attack max, armor.\n", hero_name);
	scanf_s("%d %d %d %d", &hp, &attack_min, &attack_max, &armor);

	struct hero_data hero;
	hero.name = hero_name;
	hero.coins = 0;
	hero.xp = 0;
	hero.combat.hp = hp;
	hero.combat.armor = armor;
	hero.combat.attack_min = attack_min;
	hero.combat.attack_max = attack_max;

	printf("Let's start!\n");
	int i = 0;
	int w = 1;
	int goblin_amount;
	int hero_target;
	int hero_attack;
	int hero_damage;
	int goblin_attack;
	int goblin_damage;
	int remaining_goblins;


	while (hero.combat.hp > 0) // Whole combat loop. When the hero dies, the loop brakes.
	{
		srand(time(NULL));

		goblin_amount = rand() % 6 + 1;

		printf_s("Wave %d. You fight against %d goblins:\n", w, goblin_amount);
		remaining_goblins = goblin_amount;

		struct monster_data* goblins = (struct monster_data*)malloc(goblin_amount * sizeof(struct monster_data));
		for (i = 0; i < goblin_amount; i++)
		{
			goblins[i].combat.hp = 50; //40 + rand() % 21;
			goblins[i].combat.attack_min = 10;
			goblins[i].combat.attack_max = 20;
			goblins[i].combat.armor = 5;
			goblins[i].coins = 1 + rand() % 5;
			goblins[i].xp = 15 + rand() % 36;
		}

		while (remaining_goblins > 0) //Wave loop
		{
			hero_target = rand() % goblin_amount;

			if (goblins[hero_target].combat.hp > 0) //If the goblin is alive, the hero attacks him. Then the goblin attacks the hero.
			{
				getchar(); // The code stops at every attack.

				hero_attack = hero.combat.attack_min + rand() % (hero.combat.attack_max - hero.combat.attack_min);
				hero_damage = hero_attack - goblins[hero_target].combat.armor;

				if (hero_damage > goblins[hero_target].combat.hp) //It ensures that the hero cannot deal more damage than the goblin's remaining HP. Thus, no goblin will have negative HP.
				{
					hero_damage = goblins[hero_target].combat.hp;
				}

				goblins[hero_target].combat.hp -= hero_damage;

				printf_s("You have %d HP left. You hit the goblin #%d for %d!\n", hero.combat.hp, hero_target + 1, hero_damage);

				if (goblins[hero_target].combat.hp <= 0)
				{
					remaining_goblins -= 1;
					hero.coins += goblins[hero_target].coins;
					hero.xp += goblins[hero_target].xp;
					printf_s("%d Remaining goblins\n", remaining_goblins);
				}
				if (goblins[hero_target].combat.hp > 0)
				{
					goblin_attack = goblins[hero_target].combat.attack_min + rand() % (goblins[hero_target].combat.attack_max - goblins[hero_target].combat.attack_min);
					goblin_damage = goblin_attack - hero.combat.armor;
					if (goblin_damage < 0) //It ensures that (when the damage dealt by the goblin is smaller than the armor) the hero doesn't heal.
					{
						goblin_damage = 0;
					}
					if (goblin_damage > hero.combat.hp) //Maximum goblin damage = heroe's reamining HP
					{
						goblin_damage = hero.combat.hp;
					}
					hero.combat.hp -= goblin_damage;
					printf_s("Goblin #%d hits you for %d!\n", hero_target + 1, goblin_damage);
				}
			}				
				
			if (hero.combat.hp == 0)
			{
				break;
			}
		}




			/*for (int j = 0; j < goblin_amount; j++)
			{
				if (goblins[j].combat.hp > 0)
				{
					goblin_attack = goblins[j].combat.attack_min + rand() % (goblins[j].combat.attack_max - goblins[j].combat.attack_min);
					goblin_damage = goblin_attack - hero.combat.armor;
					if (goblin_damage < 0) //It ensures that (when the damage dealt by the goblin is smaller than the armor) the hero doesn't heal.
					{
						goblin_damage = 0;
					}
					if (goblin_damage > hero.combat.hp) //Maximum goblin damage = heroe's reamining HP
					{
						goblin_damage = hero.combat.hp;
					}

					hero.combat.hp -= goblin_damage;

					printf_s("Goblin #%d hits you for %d!\n", j + 1, goblin_damage);
				}

				if (hero.combat.hp <= 0)
				{
					break;
				}
			}
			if (hero.combat.hp == 0)
			{
				break;
			}*/
		
		free(goblins);

		++w;
		getchar();
	}

	printf_s("YOU DIED!\n");
	printf_s("You collected %d coins and gained %d XP!\n", hero.coins, hero.xp);
	printf_s("GAME OVER");

	free(hero_name);
	getchar();
	return 0;
}
