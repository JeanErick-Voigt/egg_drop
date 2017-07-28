#include "egg.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int  brute_force(int lowest_number, int num_of_floors, egg *e);
int educated_split(int maximum_floor, int minimum_floor, int egg_group);


int main(int argc, char **argv)
{

	int num_of_floors, egg_group;
	//int current_floor;
	if(argc > 3){
		printf("Provided too many arguments\n");
		exit(1);
	}
	else if(argc < 3){
		printf("provided too few arguments\n");
		exit(1);
	}else{
		num_of_floors = atoi(argv[1]);
		egg_group = atoi(argv[2]);
	}

//	num_of_floors = atoi(argv[1]);
//	egg_group = atoi(argv[2]);

	egg *e = NULL;
	e = lay_egg();	
	puts("\n");
	int guessing = 1;
	int maximum_floor = num_of_floors;
	int minimum_floor = 1;
	int lowest_number = 1;
	int guess_number = 0;
	while(guessing){
		int max_safe_floor;
		guess_number += 1;
		int current_floor = educated_split(maximum_floor, minimum_floor, egg_group);
		if(egg_group > 1){
			//current_floor;
			printf("This is current floor multi guess %d\n", current_floor);
			egg_drop_from_floor(e, current_floor);
			printf("This is after egg drop\n");
			if(egg_is_broken(e) == 1){
				egg_group -= 1;
				printf("This is number of  eggs %d", egg_group);
				maximum_floor = current_floor;
				minimum_floor = lowest_number;
				e = lay_egg();
			}else{
				minimum_floor = lowest_number = current_floor;
			}
		}else{
			//if(brute_force(minimum_floor, maximum_floor)) >= 1){
				//printf("The maximum safe floor is %d", brute_force(minimum_floor, maximum_floor));
			max_safe_floor = brute_force(minimum_floor, maximum_floor, e);
			printf("highest safe floor is %d\n", max_safe_floor - 1);
			printf("num of guesses = %d\n", guess_number + (max_safe_floor - minimum_floor));
			guessing = 0;
		}
		
	}
	printf("exit looop\n");
	destroy_egg(e);
	return(0);
}


	// brute force way
int brute_force(int  lowest_number, int num_of_floors, egg *e){
	int current_floor;
	for(current_floor = lowest_number; current_floor <=  num_of_floors; current_floor++){
		egg_drop_from_floor(e, current_floor);
		printf("current floor %d\n", current_floor);
		if(egg_is_broken(e) == 1){
			//printf("Maximum safe floor to drop from is %d floor", current_floor - 1);
			//break;
			return(current_floor);
		}
	}
	return(0);

}

int educated_split(int maximum_floor, int minimum_floor, int egg_group)
{
	int range = maximum_floor -(minimum_floor - 1);
	int guess;
	guess = (minimum_floor - 1) + floor(range/egg_group);
	return guess;
}
