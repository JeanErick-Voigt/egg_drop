#include "egg.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	int num_of_floors, egg_group;
	int current_floor;
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
	egg *e = NULL;
	e = lay_egg();
	egg_group -= 1;
	//printf("%lu", sizeof(e));
	printf("num of floors is %d\n", num_of_floors);
	//printf("num of eggs is %d", egg_group);
	e = lay_egg();	
	//printf("%d", sizeof(e));
	puts("\n");
	// brute force way
	for(current_floor = 1; current_floor <=  num_of_floors; current_floor++){
		egg_drop_from_floor(e, current_floor);
		printf("current floor %d\n", current_floor);
		if(egg_is_broken(e) == 1){
			printf("Maximum safe floor to drop from is %d floor", current_floor - 1);
			break;
		}else{
			printf("Next floor");
		}
	}
	return(0);
}
