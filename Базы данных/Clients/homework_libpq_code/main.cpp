#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include "postgre_client.h"
#include <windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try{
	
		postgre_client pc;
		//pc.create_table();
		//pc.add_client(1, "Vasiliy", "Ivanov", "vasia@mail.ru");
		//pc.add_client(2, "Petr", "Petrov", "petia@mail.ru");
		//pc.find_client_id("Ivanov", "lastname");
		//pc.add_phone(1, "765765", 1);
		//pc.alter_client("Semen", "Semenov", "semka@mail.ru", 1);
		//pc.del_phone(1);
		//pc.del_client(1);


	}
	catch (pqxx::sql_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}