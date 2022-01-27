#include <stdio.h>
#include <string.h>

int main() {

	struct snack {
		char name[100];
		float cost;
		int quantity;
	};

	struct snack cocoPuffs, manchegoCheese, magicBeans, potatoChips, granola;
	struct snack arr[100];
	int snacks = 5;

	strcpy(cocoPuffs.name, "Coco Puffs");
	cocoPuffs.cost = 1.50;
	cocoPuffs.quantity = 4;

	strcpy(manchegoCheese.name, "Manchego Cheese");
	manchegoCheese.cost = 15.50;
	manchegoCheese.quantity = 6;

	strcpy(magicBeans.name, "Magic Beans");
	magicBeans.cost = 0.50;
	magicBeans.quantity = 0;

	strcpy(potatoChips.name, "Potato Chips");
	potatoChips.cost = 2.00;
	potatoChips.quantity = 2;

	strcpy(granola.name, "Granola");
	granola.cost = 1.50;
	granola.quantity = 10;

	arr[0] = cocoPuffs;
	arr[1] = manchegoCheese;
	arr[2] = magicBeans;
	arr[3] = potatoChips;
	arr[4] = granola;

	int money;
	int item;

	printf("Welcome to Steven Struct's Snack Bar.\n");
	printf("How much money do you have? ");
	scanf("%d\n",money);

	for(int i = 0; i < snacks; i++) {
		printf("%d) %s  cost: %f  quantity: %d\n", i, arr[i].name, arr[i].cost, arr[i].quantity);
	}

	printf("What would you like to buy? [");
	for(int i = 0; i < snacks; i++) {
		printf("%d,",i);
	}
	printf("] ");
	scanf("%d\n", *item);

	if(arr[item] >= snacks) {
		printf("Sorry, we do not have this item\n");
	} else if(arr[item].quantity <= 0) {
		printf("Sorry, we are out of %\ns", arr[item].name);
	} else if(arr[item].cost > money) {
		printf("Sorry, you cannot afford %s\n", arr[item].name);
	} else {
		printf("You bought %s\n", arr[item].name);
		printf("You have $%f left\n");
	}


	
	
}

