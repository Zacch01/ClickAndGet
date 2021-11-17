#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//ILAN

	/*FILE* fic = fopen("TestProjet.csv", "r+");
		if (fic == NULL)
			exit(1);*/
	/*int name=0, age=0;
	fscanf(fic, "%d;%d", &name, &age);
	printf("%d %d", name, age);
	name = 77;
	age = 66;
	fprintf(fic, ";%d;%d;987\n44; ; ; ;88",name,age);

	fclose(fic);
	return 0;*/

	typedef struct manager
	{
		char last_name[25];
		char first_name[25];
		char user_name[25];
		char phone[11];
		int age;
		char password[25];
	}manager;

	typedef struct customer
	{
		char last_name[25];
		char first_name[25];
		char user_name[25];
		char phone[11];
		int age;
		char city[20];
		char adress[50];
		char password[25];
	}customer;

	void menu();
	int register_manager();
	int register_customer();
	int checkm(char last[25], char first[25], char user[25], char phone[11], int age, char password1[25], char password2[25]);
	int checkc(char last[25], char first[25], char user[25], char phone[11], int age,char city[20],char adress[50], char password1[25], char password2[25]);
	int termofuse();
	int login_manager();
	int login_customer();



	int main()
	{
		menu();
		return 0;
	}

	void menu()
	{
		int account, connection;
		printf("\t\t\t1-Manager\n\t\t\t2-Customer\n");
		scanf_s("%d", &account);
		while (account != 1 && account != 2)
		{
			printf("Bad choice. Try again\n");
			scanf_s("%d", &account);
		}
		printf("\t\t\t1-Log In\n\t\t\t2-Register\n");
		scanf_s("%d", &connection);
		while (connection != 1 && connection != 2)
		{
			printf("Bad choice. Try again\n");
			scanf_s("%d", &connection);
		}

		if (account == 1)
		{
			if (connection == 1)
			{
				while (login_manager() == 0)
					printf("\nYour user name or your password is not correct. Please try again.\n");
				/*menu_manger();*/
			}
			else
			{
				if (register_manager() == 0)
					printf("Please note, you hasn't been registered.\n");
				return menu();

			}
		}
		else
		{
			if (connection == 2)
			{
				while (login_customer() == 0)
					printf("\nYour user name or your password is not correct. Please try again.\n");
			}
			else
			{
				if (register_customer() == 0)
					printf("Please note, you hasn't been registered.\n");
				return menu();
			}
		}
	}

	int register_manager()
	{
		FILE* fic = fopen("ManagersInformation.csv", "r+");
		if (fic == NULL)
			exit(1);
		char cpassword[25];
		manager data;

		do
		{
			printf("Last name (without characters): ");
			scanf("%s", data.last_name);
			printf("First name (without characters): ");
			scanf("%s", data.first_name);
			printf("User name: ");
			scanf("%s", data.user_name);
			printf("Phone number (must start with 05): ");
			scanf("%s", data.phone);
			printf("Age (must be under 120): ");
			scanf_s("%d", &data.age);
			printf("Password (must include one capital letter and minimum 6 characters): ");
			scanf("%s", data.password);
			printf("Write again your password: ");
			scanf("%s", cpassword);
		} while (checkm(data.last_name, data.first_name, data.user_name, data.phone, data.age, data.password, cpassword) == 0);

		if (termofuse() == 0)
			return 0;

		fseek(fic, 0, SEEK_END);
		fprintf(fic, "\n%s,%s,%s,%s,%d,%s", data.last_name, data.first_name, data.user_name, data.phone, data.age, data.password);
		fclose(fic);
		return 1;
	}

	int register_customer()
	{
		FILE* fic = fopen("CustomersInformation.csv", "r+");
		if (fic == NULL)
			exit(1);
		char cpassword[25];
		customer data;

		do
		{
			printf("Last name (without characters): ");
			scanf("%s", data.last_name);
			printf("First name (without characters): ");
			scanf("%s", data.first_name);
			printf("User name: ");
			scanf("%s", data.user_name);
			printf("Phone number (must start with 05): ");
			scanf("%s", data.phone);
			printf("Age (must be under 120): ");
			scanf_s("%d", &data.age);
			printf("City (without characters): ");
			scanf(" %[^\n]", data.city);
			printf("Adress (without characters and one number): ");
			scanf(" %[^\n]", data.adress);
			printf("Password (must include one capital letter and minimum 6 characters): ");
			scanf("%s", data.password);
			printf("Write again your password: ");
			scanf("%s", cpassword);
		} while (checkc(data.last_name, data.first_name, data.user_name, data.phone, data.age, data.city, data.adress, data.password, cpassword) == 0);

		if (termofuse() == 0)
			return 0;

		fseek(fic, 0, SEEK_END);
		fprintf(fic, "\n%s,%s,%s,%s,%d,%s,%s,%s", data.last_name, data.first_name, data.user_name, data.phone, data.age,data.city,data.adress, data.password);
		fclose(fic);
		return 1;
	}

	int checkm(char last[25], char first[25], char user[25], char phone[11], int age, char password1[25], char password2[25])
	{
		int cap_letter = 0;
		for (int i = 0; i < strlen(last); i++)
		{
			if (last[i] < 'A' || last[i]>'z' || (last[i] > 'Z' && last[i] < 'a'))
			{
				printf("\nYour last name is not correct. Please try again.\n");
				return 0;
			}
		}
		for (int i = 0; i < strlen(first); i++)
		{
			if (first[i] < 'A' || first[i]>'z' || (first[i] > 'Z' && first[i] < 'a'))
			{
				printf("\nYour first name is not correct. Please try again.\n");
				return 0;
			}
		}
		if (phone[0] != '0' || phone[1] != '5' ||phone[10]!='\0')
		{
			printf("\nYour phone number is not correct. Please try again.\n");
			return 0;
		}
		if(age>120)
		{
			printf("\nYour age is not correct. Please try again.\n");
			return 0;
		}
		for (int i = 2; i < 10; i++)
		{
			if (phone[i] < '0' || phone[i]>'9')
			{
				printf("\nYour phone number is not correct. Please try again.\n");
				return 0;
			}
		}
		for (int i = 0; i < strlen(password1); i++)
			if (password1[i] >= 'A' && password1[i] <= 'Z')
				cap_letter++;
		if (strlen(password1) < 6 || strlen(password2) < 6 || strlen(password1) != strlen(password2)|| cap_letter == 0|| strcmp(password1, password2) != 0)
		{
			printf("\nYour password is not correct. Please try again.\n");
			return 0;
		}
		return 1;
	}

	int checkc(char last[25], char first[25], char user[25], char phone[11], int age, char city[20], char adress[50], char password1[25], char password2[25])
	{
		int cap_letter = 0,number=0;
		for (int i = 0; i < strlen(last); i++)
		{
			if (last[i] < 'A' || last[i]>'z' || (last[i] > 'Z' && last[i] < 'a'))
			{
				printf("\nYour last name is not correct. Please try again.\n");
				return 0;
			}
		}
		for (int i = 0; i < strlen(first); i++)
		{
			if (first[i] < 'A' || first[i]>'z' || (first[i] > 'Z' && first[i] < 'a'))
			{
				printf("\nYour first name is not correct. Please try again.\n");
				return 0;
			}
		}
		if (phone[0] != '0' || phone[1] != '5' || phone[10] != '\0')
		{
			printf("\nYour phone number is not correct. Please try again.\n");
			return 0;
		}
		for (int i = 2; i < 10; i++)
		{
			if (phone[i] < '0' || phone[i]>'9')
			{
				printf("\nYour phone number is not correct. Please try again.\n");
				return 0;
			}
		}
		if (age > 120)
		{
			printf("\nYour age is not correct. Please try again.\n");
			return 0;
		}
		for (int i = 0; i < strlen(city); i++)
		{
			if (city[i] < 'A' || city[i]>'z' || (city[i] > 'Z' && city[i] < 'a'))
			{
				printf("\nYour city is not correct. Please try again.\n");
				return 0;
			}
		}
		for (int i = 0; i < strlen(adress); i++)
		{
			if ((adress[i] < '0' && adress[i] != ' ') || adress[i] > 'z' || (adress[i] > 'Z' && adress[i] < 'a') || (adress[i] > '9' && adress[i] < 'A'))
			{
				printf("\nYour adress is not correct. Please try again.\n");
				return 0;
			}
			if (adress[i] >= '0' && adress[i] <= '9')
				number++;
		}
		if (number == 0)
		{
			printf("\nYour age is not correct. Please try again.\n");
			return 0;
		}
		for (int i = 0; i < strlen(password1); i++)
			if (password1[i] >= 'A' && password1[i] <= 'Z')
				cap_letter++;
		if (strlen(password1) < 6 || strlen(password2) < 6 || strlen(password1) != strlen(password2) || cap_letter == 0 || strcmp(password1, password2) != 0)
		{
			printf("\nYour password is not correct. Please try again.\n");
			return 0;
		}
		return 1;
	}

	int termofuse()
	{
		int choice;
		printf("\n\n1- Accept\t\t\t2- Deny\n");
		scanf_s("%d", &choice);
		while (choice!=1&&choice!=2)
		{
			printf("Bad choice. Try again\n");
			scanf_s("%d", &choice);
		}
		if (choice == 2)
			return 0;
		return 1;
	}

	int login_manager() 
	{
		FILE* fic = fopen("ManagersInformation.csv", "r+");
		if (fic == NULL)
			exit(1);
		char username1[25];
		char password1[25];
		manager data;
		printf("User name: ");
		scanf("%s", username1);
		printf("Password: ");
		scanf("%s", password1);
		fseek(fic, 58, SEEK_SET);
		do
		{
			fscanf(fic, "%[^,],%[^,],%[^,],%[^,],%d,%[^\n]\n", data.last_name, data.first_name, data.user_name, data.phone, &data.age, data.password);
			if (strcmp(username1, data.user_name) == 0 && strcmp(password1, data.password) == 0)
			{
				fclose(fic);
				return 1;
			}
		} while (!feof(fic));
		fclose(fic);
		return 0;
	}

	int login_customer()
	{
		FILE* fic = fopen("CustomersInformation.csv", "r+");
		if (fic == NULL)
			exit(1);
		char username1[25];
		char password1[25];
		customer data;
		printf("User name: ");
		scanf("%s", username1);
		printf("Password: ");
		scanf("%s", password1);
		fseek(fic, 70, SEEK_SET);
		do
		{
			fscanf(fic, "%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n", data.last_name, data.first_name, data.user_name, data.phone, &data.age, data.city,data.adress,data.password);
			if (strcmp(username1, data.user_name) == 0 && strcmp(password1, data.password) == 0)
			{
				fclose(fic);
				return 1;
			}
		} while (!feof(fic));
		fclose(fic);
		return 0;
	}