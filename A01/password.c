#include <stdio.h>
#include <string.h> 

int main() {
	char passwd[999];
	printf("Enter a password: ");
       	scanf("%s", passwd);
	for(int i = 0; i < strlen(passwd); i++) {
		if(passwd[i] == 'e') {
			passwd[i] = '3';
		}
		else if(passwd[i] == 'l') {
			passwd[i] = '1';
		}
		else if(passwd[i] == 'a') {
			passwd[i] = '@';
		}
	}
	printf("Your bad password is: %s\n", passwd);
}
