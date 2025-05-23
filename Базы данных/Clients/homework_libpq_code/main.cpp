#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include "postgre_client.h"
#include <stdarg.h>
#include <windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try{
	pqxx::connection c(
		"host=localhost "
		"port=5432 "
		"dbname=MusicSite2 "
		"user=postgres "
		"password=123456");

		postgre_client pc;
		//pc.create_table(tx);
		//pc.add_client(c, 1, "Vasiliy", "Ivanov", "vasia@mail.ru");
		//pc.add_client(c, 2, "Petr", "Petrov", "petia@mail.ru");
		//pc.find_client_id(c, "Ivanov", "lastname");
		//pc.add_phone(c, 1, "765765", 1);
		//pc.alter_client(c, "Semen", "Semenov", "semka@mail.ru", 1);
		//pc.del_phone(c, 1);
		//pc.del_client(c, 1);


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