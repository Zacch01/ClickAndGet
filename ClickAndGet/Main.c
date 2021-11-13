#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct manager
{
	char last_name[25];
	char first_name[25];
	char user_name[25];
	long phone;
	int age;
	char password[20];
};



int main()
{
	FILE* fic = fopen("TestProjet.csv", "r+");
	if (fic == NULL)
		exit(1);

	int name=0, age=0;
	fscanf(fic, "%d;%d", &name, &age);
	printf("%d %d", name, age);
	name = 77;
	age = 66;
	fprintf(fic, ";%d;%d;987\n44; ; ; ;88",name,age);

	fclose(fic);
	return 0;
}