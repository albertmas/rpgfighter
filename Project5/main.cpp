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

	printf_s("So you are %s? Alright, now enter your stats in the following order: hp, attack min, attack max, armor.", hero_name);
	scanf_s("%d %d %d %d", hp, attack_min, attack_max, armor);

	struct hero_data hero;
	hero.name = hero_name;
	hero.coins = 0;
	hero.xp = 0;
	hero.combat.hp = hp;
	hero.combat.armor = armor;
	hero.combat.attack_min = attack_min;
	hero.combat.attack_max = attack_max;


	printf("Let's start!\n");
	int i = 1;
	int goblin_amount;
	struct monster_data* goblins;
	int hero_target;

	srand(time(NULL));
	while (hero.combat.hp > 0)
	{
		printf("Wave %d starts:\n", i);

		goblin_amount = rand() % 5;
		goblins = (monster_data*)malloc(goblin_amount * sizeof(monster_data));

		while (wave_is_on())
		{
			srand(time(NULL));
			hero_target = rand() % goblin_amount;
		}

		while (i < 6)
		{
			goblins[i].combat.hp = 0;
			++i;
		}
		++i;

		free(goblins);
		getchar();
	}

	free(hero_name);
	getchar();
	getchar();
	return 0;
}