#include "egg.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int  brute_force(int lowest_number, int num_of_floors, egg *e);
int educated_split(int maximum_floor, int minimum_floor, int egg_group);


int main(int argc, char **argv)
{

	int num_of_floors, egg_group;
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
	egg *e  = lay_egg();
	egg *max = lay_egg();
	puts("\n");
	int guessing = 1;
		
	int maximum_floor = num_of_floors;
	int minimum_floor = 1;
	int lowest_number = 1;
	int guess_number = 0;
	int egg_count = 1;
	int current_floor = 0;
	int max_safe_floor;
	while(guessing){
		// fringe cases
		//printf("This is current_floor %d, max floor %d, minimum_floor %d\n", current_floor, maximum_floor, minimum_floor);
		if(maximum_floor - minimum_floor < 3){
			guess_number += 1;
			egg_drop_from_floor(e, (minimum_floor));
			if(egg_is_broken(e) == 1){
		//		printf("egg broke\n");
				minimum_floor -= 1;
			}
			else if(egg_is_broken(e) != 1 && maximum_floor == num_of_floors){
				minimum_floor = maximum_floor;
			}else if(maximum_floor != num_of_floors && egg_is_broken(e) != 1){
				e = lay_egg();
				guess_number += 1;
				egg_drop_from_floor(e, minimum_floor + 1);
				if(egg_is_broken(e) == 1){
					;
				}else{
					minimum_floor += 1;
				}
			}else{
				minimum_floor += 1;
			}
			printf("%d is the maximum safe floor, found after %d drops\n", minimum_floor, guess_number);
			break;
		}
		if(minimum_floor == maximum_floor){
			printf("%d is the maximum safe floor, found after %d drops\n", minimum_floor - 1, guess_number);
			break;
		}
		if(maximum_floor - minimum_floor == minimum_floor + 1){
			printf("%d is the maximum safe floor, found after %d drops\n", minimum_floor + 1, guess_number);
			break;
		}

//		printf("The minimum floor %d and max floor %d\n", minimum_floor, maximum_floor);
		printf("Dropping egg %d from floor: \n", egg_count); 
		guess_number += 1;
		if(egg_group > 1){
			current_floor = educated_split(maximum_floor, minimum_floor, egg_group);
			printf("#%d", current_floor);
			egg_drop_from_floor(e, current_floor);
			if(egg_is_broken(e) == 1){
				egg_group -= 1;
				egg_count += 1;
				printf(" CRACK\n");
				maximum_floor = current_floor;
				minimum_floor = lowest_number + 1;  //test
				e = lay_egg();
			}else{
				minimum_floor = lowest_number = current_floor;
				printf(" safe\n");
			}
		}else{
			max_safe_floor = brute_force(minimum_floor, maximum_floor, e);
			if(max_safe_floor != num_of_floors)
					max_safe_floor -= 1;
			else
				max_safe_floor = num_of_floors;
			printf("%d is the maximum safe floor, found after %d drops \n", (max_safe_floor), 
				guess_number + (max_safe_floor - minimum_floor));

			guessing = 0;
		}
		
	}
	destroy_egg(e);
	destroy_egg(max);
	return(0);
}


int brute_force(int  lowest_number, int num_of_floors, egg *e){
	int current_floor;
	for(current_floor = lowest_number; current_floor <=  num_of_floors; current_floor++){
		egg_drop_from_floor(e, current_floor + 1);
		printf(" #%d", current_floor + 1);
		if(egg_is_broken(e) == 1){
			printf(" CRACK\n");
			return(current_floor);
		}else{
			printf(" safe\n");
			current_floor += 1;
		}
	}


	return(num_of_floors);

}

int educated_split(int maximum_floor, int minimum_floor, int egg_group)
{
	int range, guess;
	range = maximum_floor -minimum_floor;
	if(range > 75)
		egg_group = 2;
	if(range < 50 && range > 30)
		egg_group = 3;
	while(range < egg_group && egg_group > 1){
		egg_group -= 1;
		range = maximum_floor - minimum_floor;
	}

	guess = (minimum_floor) + floor(range/egg_group);
	return guess;
}
