#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//ILAN

	/*FILE* fic = fopen("TestProjet.csv", "r+");
		if (fic == NULL)
			exit(1);*/
	/*int name=0, age=0;
	fscanf(fic, "%d,%d", &name, &age);
	printf("%d %d", name, age);
	name = 77;
	age = 66;
	fprintf(fic, "%d,%d,987\n44, , , ,88",name,age);

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

	typedef struct product
	{
		char product_name[25];
		char price[10];
		char amount_of_product[5];
	}product;

	void menu();
	int register_manager();
	int register_customer();
	int checkm(char last[25], char first[25], char user[25], char phone[11], int age, char password1[25], char password2[25]);
	int checkc(char last[25], char first[25], char user[25], char phone[11], int age,char city[20],char adress[50], char password1[25], char password2[25]);
	int termofuse();
	int login_manager();
	int login_customer();

	int string_check(char str[25]);                                                 ////////    v
	int capital_letters_check(char str[25]);                                        ////////    v
	int check_price(char price[25]);                                                ////////    v
	int check_number(char amount[25]);                                              ////////    v
	int add_category();                                                             ////////    v
	int add_product(char choice[3]);                                                ////////    v
	int delete_product(char choicecat[3], char choicepro[3]);                       ////////    v
	void update_product_by_search();                                                ////////    v
	//void choose_product_to_update();
	void print_all_orders();                                                        ////////    v

	int print_all_category(); //returns number of printed categories                ////////    v
	// view stock functions - 3
	void view_all_stock();                                                          ////////    v
	void view_specific_category();                                                  ////////    v
	//void view_stock_specific_product();





	int main()
	{
		view_specific_category();
		//update_product_by_search();
		//menu();

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


	// Checks the string is string of only letters
	int string_check(char str[25])
	{
		for (int i = 0; i < strlen(str); ++i)
		{
			if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i]>'z')
				return 1; //the stringis not only letters
			else
				return 0; //the string is correct
		}
	}

	// Checks if the string includes only capital letters
	int capital_letters_check(char str[25])
	{
		for (int i = 0; i < strlen(str); ++i)
		{
			if (str[i] < 'A' || str[i] > 'Z' )
				return 1; //the string is not only capital letters
		}
		return 0; //the string is correct
	}

	// Checking if the entered product price is valid
	int check_price(char price[25])
	{
		for (int i = 0; i < strlen(price); ++i)
		{
			if (price[i] < '0' || price[i]>'9')
				return 1; // The price is not valid
		}
		return 0; // The price is valid
	}

	// Checking if the input is number
	int check_number(char amount[25])
	{
		for (int i = 0; i < strlen(amount); i++)
		{
			if (amount[i] < '0' || amount[i] >'9')
				return 1; // The amount is not valid
		}
		return 0;
	}

	// Adds new category
	int add_category()
	{
		FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
		if (fic == NULL)
			exit(1);
		char category[25];
		char some_category[25];
		printf("Enter the new category you want to add: \n");
		scanf("%[^\n]", category);
		fseek(fic, 17, SEEK_SET);
		while (string_check(category) == 1)
		{
			printf("Your category name is not correct, Please try again\n");
			scanf("%[^\n]", category);
		}
		char test[5000];
		do
		{
			fscanf(fic, " %[^,],%[^\n]\n", some_category, test);
			if (strcmp(some_category, category) == 0)
			{
				printf("\nThe inserted category already exists\n");
				fclose(fic);
				return 0; 
			}
		} while (!feof(fic));

		fprintf(fic, "\n%s,", category);
		printf("\nThe new category has been added\n");
		fclose(fic);
		return 0;
	}

	//Adds new product
	int add_product(char choice[3])
	{
		FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
		if (fic == NULL)
			exit(1);
		product dataenter;
		char c = fgetc(fic);
		int choice2 = atoi(choice);
		int counter = 0;
		printf("Name of product (Only capital letters): ");
		scanf(" %[^\n]", dataenter.product_name);
		while (capital_letters_check(dataenter.product_name) == 1) 
		{
		 printf("Your product name is not valid, Please try again: ");
		 scanf(" %[^\n]", dataenter.product_name);
		}

		printf("Price of product (Positive integer number): ");
		scanf(" %[^\n]", dataenter.price);
		while (check_price(dataenter.price) == 1)
		{
		printf("Your product price is not valid, Please try again :");
		scanf(" %[^\n]", dataenter.price);
		}

		printf("Amount of product: ");
		scanf(" %[^\n]", dataenter.amount_of_product);
		while (check_number(dataenter.amount_of_product) == 1)
		{
		printf("Your product quantity is not valid, Please try again");
		scanf(" %[^\n]", dataenter.amount_of_product);
		}

		product data;
		fseek(fic, 21, SEEK_SET);
		while (!feof(fic))
		{
			if (counter == choice2 - 1)
				break;
			c = fgetc(fic);
			if (c == '\n')
				++counter;
		}
		while (c != ',')
			c = fgetc(fic);

		while (!feof(fic) && c != '\n')
		{
			c = ' ';
			fscanf(fic, "%[^;]", data.product_name);
			if (strcmp(data.product_name, dataenter.product_name) == 0)
			{
				printf("The inserted product already exists");
				fclose(fic);
				return 0;
			}
			while (c != '\n' && !feof(fic) && c != ',')
			{
				c = fgetc(fic);
				if (c == '\n' && !feof(fic))
					break;
			}
		}
		fseek(fic, 0, SEEK_SET);
		c = fgetc(fic);
		counter = 0;
		FILE* fic2 = fopen("CategoriesAndProductsTEST.csv", "w+");
		while (!feof(fic))
		{
			if (c == '\n')
				++counter;
			if (counter == choice2 + 1)
			{
				fputc(',', fic2);
				fprintf(fic2, "%s;%s;%s;", dataenter.product_name, dataenter.price, dataenter.amount_of_product);
				counter++;
			}
			fputc(c, fic2);
			c = fgetc(fic);
			if (feof(fic) && (counter == choice2))
			{
				fputc(',', fic2);
				fprintf(fic2, "%s;%s;%s;", dataenter.product_name, dataenter.price, dataenter.amount_of_product);
			}
		}
		fseek(fic, 0, SEEK_SET);
		fseek(fic2, 0, SEEK_SET);
		c = fgetc(fic2);
		while (!feof(fic2))
		{
			fputc(c, fic);
			c = fgetc(fic2);
		}
		fclose(fic2);
		fclose(fic);
		printf("\nThe product has been added successfully\n");
	}

	// Deletes product
	int delete_product(char choicecat[3], char choicepro[3])
	{
		FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
		if (fic == NULL)
			exit(1);
		char c = fgetc(fic), d = ' ';
		int choice2 = atoi(choicecat), choice3 = atoi(choicepro);
		int counter1 = 0, counter2 = 0;
		product data;

		FILE* fic2 = fopen("CategoriesAndProductsTEST.csv", "w+");
		while (counter1 != choice2)
		{
			putc(c, fic2);
			c = fgetc(fic);
			if (c == '\n')
				counter1++;
		}
		while (counter2 != choice3)
		{
			putc(c, fic2);
			c = fgetc(fic);
			if (c == ',')
				counter2++;
		}
		while (d != '\n' && d != ',' && d != EOF)
		{
			d = fgetc(fic);
		}
		while (!feof(fic))
		{
			putc(d, fic2);
			d = fgetc(fic);
		}

		fseek(fic, 0, SEEK_SET);
		fclose(fic);
		fic = fopen("CategoriesAndProducts.csv", "w");
		fclose(fic);
		fic = fopen("CategoriesAndProducts.csv", "r+");
		fseek(fic2, 0, SEEK_SET);
		c = fgetc(fic2);
		while (!feof(fic2))
		{
			fputc(c, fic);
			c = fgetc(fic2);
		}
		fclose(fic2);
		fclose(fic);
		printf("\nThe product has been deleted successfully\n");
	}

	//Prints all categories
	int print_all_category()
	{
		FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
		if (fic == NULL)
			exit(1);
		fseek(fic, 18, SEEK_SET);
		char category[25];
		int num = 0;
		printf("CATEGORIES: \n");
		char c = fgetc(fic);
		while (!feof(fic))
		{
			++num;
			fscanf(fic, "%[^,]", category);
			printf("%d -  %s\n", num, category);
			c = fgetc(fic);
			while (c != '\n' && !feof(fic))
			{
				c = fgetc(fic);
			}
		}
		fclose(fic);
		return num;
	}

	// print all orders
	void print_all_orders()
	{
		FILE* fic = fopen("Orders.csv", "r+");
		if (fic == NULL)
			exit(1);

		char nbr_orders[5], status[2], nameofcustomer[25], product[31];
		int amount;
		char c = ' ';
		int counter = 1;
		fseek(fic, 53, SEEK_SET);
		printf("\nNumber of the order / Status / Customer / Amount / Products\n\n", nbr_orders, status, nameofcustomer);
		while (!feof(fic))
		{
			c = ' ';
			fscanf(fic, "%[^;];%[^;];%[^;];%d;", nbr_orders, status, nameofcustomer, &amount);
			printf("%s / %s / %s / %d /", nbr_orders, status, nameofcustomer, amount);
			while (c != '\n' && c != EOF)
			{
				fscanf(fic, "%[^,],", product);
				printf("%s, ", product);
				c = fgetc(fic);
			}
			if (c == '\n')
				printf("\n");
		}
		fclose(fic);
	}

	// View all stock
	void view_all_stock()
	{
		int serial_num = 0;
		product some_product;
		FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
		if (fic == NULL)
			exit(1);
		char c = fgetc(fic);
		fseek(fic, 19, SEEK_SET);

		while (!feof(fic))
		{
			while (c != ',')
				c = fgetc(fic);

			while (!feof(fic) && c != '\n')
			{
				++serial_num;
				fscanf(fic, " %[^;];%[^;];%[^;]", some_product.product_name, some_product.price, some_product.amount_of_product);
				printf("%d - %s\nPRICE: %s\nQUANTITY: %s\n", serial_num, some_product.product_name, some_product.price, some_product.amount_of_product);
				printf("\n");
				c = fgetc(fic);
				c = fgetc(fic);
			}
		}
		fclose(fic);
	}

	//View stock of specific category
	void view_specific_category()
	{
		int serial_num = 0;
		char c;
		int categories_num;
		char choice[3];
		int counter = 0;
		product some_pro;
		FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
		if (fic == NULL)
			exit(1);
		categories_num = print_all_category();
		printf("\nPlease select the category you want to view: ");
		scanf(" %s", &choice);
		
		while (check_number(choice) != 0 || atoi(choice) > categories_num)
		{
			printf("The input is not valid!, please try again\n");
			scanf(" %s", &choice);
		}
		fseek(fic, 19, SEEK_SET);
		while (!feof(fic))
		{
			c = fgetc(fic);
			if (c == '\n')
			{
				++counter;
			}
			if (counter == atoi(choice))
				break;
		}
		while (c != ',')
			c = fgetc(fic);

		while (!feof(fic) && c != '\n')
		{
			++serial_num;
			fscanf(fic, " %[^;];%[^;];%[^;]", some_pro.product_name, some_pro.price, some_pro.amount_of_product);
			printf("%d - %s\nPRICE: %s\nQUANTITY: %s\n", serial_num, some_pro.product_name, some_pro.price, some_pro.amount_of_product);
			printf("\n");
			c = fgetc(fic);
			c = fgetc(fic);
		}
		fclose(fic);
	}

	// Updates details of product by searching the product
	void update_product_by_search()
	{
		FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
		if (fic == NULL)
			exit(1);
		char price[10], amount_of_product[5];
		char choice;
		printf("\nPlease enter the name of the product you want to update (only with capital letters): ");
		char product_name[25], product_nameNew[25];
		product data;
		scanf("%[^\n]", product_name);
		while (capital_letters_check(product_name) == 1)
		{
			printf("Your product name is not valid, Please try again: ");
			scanf(" %[^\n]", product_name);
		}
		fseek(fic, 21, SEEK_SET);
		char c = fgetc(fic), d = ' ';
		while (!feof(fic))
		{
			while (c != ',')
			{
				c = fgetc(fic);
			}
			c = ' ';
			while (c != '\n' && c != EOF)
			{
				fscanf(fic, "%[^;];%[^;];%[^;];", data.product_name, data.price, data.amount_of_product);
				if (strcmp(data.product_name, product_name) == 0)
				{
					break;
				}
				c = fgetc(fic);
			}
			if (strcmp(data.product_name, product_name) == 0)
			{
				break;
			}
		}
		if (strcmp(data.product_name, product_name) != 0)
		{
			printf("\nThe searched product has not been found.");
			return;////////////////////////////////////////////////////////////////////////////menu
		}

		printf("\n1 - Name\n2 - Price\n3 - Quantity\n");
		getchar();
		scanf("%c", &choice);
		while (choice < '0' && choice>'3')
		{
			printf("Your choice is not good. Try again.\n");
			getchar();
			scanf("%c", &choice);
		}
		if (choice == '1')
		{
			printf("\nPlease enter the new name of the product(only with capital letters): ");
			getchar();
			scanf("%[^\n]", product_nameNew);
			while (capital_letters_check(product_nameNew) == 1)
			{
				printf("Your product name is not valid, Please try again: ");
				getchar();
				scanf(" %[^\n]", product_nameNew);
			}
		}
		if (choice == '2')
		{
			printf("\nPlease enter the new price of the product (Positive integer number): ");
			getchar();
			scanf(" %[^\n]", price);
			while (check_price(price) == 1)
			{
				printf("Your product price is not valid, Please try again :");
				getchar();
				scanf(" %[^\n]", price);
			}
		}
		if (choice == '3')
		{
			printf("\nPlease enter the new amount of the product: ");
			getchar();
			scanf(" %[^\n]", amount_of_product);
			while (check_number(amount_of_product) == 1)
			{
				printf("Your product quantity is not valid, Please try again");
				getchar();
				scanf(" %[^\n]", amount_of_product);
			}
		}

		FILE* fic2 = fopen("CategoriesAndProductsTEST.csv", "w+");
		fseek(fic, 0, SEEK_SET);
		c = fgetc(fic);
		while (c != '\n')
		{
			putc(c, fic2);
			c = fgetc(fic);
		}
		while (!feof(fic))
		{
			while (c != ',')
			{
				putc(c, fic2);
				c = fgetc(fic);
			}
			while (c != '\n' && c != EOF)
			{
				putc(c, fic2);
				fscanf(fic, "%[^;];%[^;];%[^;];", data.product_name, data.price, data.amount_of_product);
				if (choice == '1')
				{
					if (strcmp(data.product_name, product_name) == 0)
						fprintf(fic2, "%s;%s;%s;", product_nameNew, data.price, data.amount_of_product);
				}
				else if (choice == '2')
				{
					if (strcmp(data.product_name, product_name) == 0)
						fprintf(fic2, "%s;%s;%s;", data.product_name, price, data.amount_of_product);
				}
				else if (strcmp(data.product_name, product_name) == 0)
					fprintf(fic2, "%s;%s;%s;", data.product_name, data.price, amount_of_product);
				if (strcmp(data.product_name, product_name) != 0)
					fprintf(fic2, "%s;%s;%s;", data.product_name, data.price, data.amount_of_product);
				c = fgetc(fic);
			}
		}
		fclose(fic);
		fic = fopen("CategoriesAndProducts.csv", "w");
		fclose(fic);
		fic = fopen("CategoriesAndProducts.csv", "r+");
		fseek(fic2, 0, SEEK_SET);
		c = fgetc(fic2);
		while (!feof(fic2))
		{
			fputc(c, fic);
			c = fgetc(fic2);
		}
		fclose(fic2);
		fclose(fic);
		printf("Product successfully updated\n");
	}

	//// Updates product the manager choose from list of products
	//void choose_product_to_update()
	//{
	//	int category_num;
	//	product some_product;
	//	FILE* fic = fopen("CategoriesAndProducts.csv", "r+");
	//	if (fic == NULL)
	//		exit(1);
	//	printf("Please select the category of the product you want to update: \n");
	//	category_num = print_all_category();

	////shmuel!!!


	//}

