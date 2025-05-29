#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <windows.h>


class postgre_client {

	pqxx::connection c;

public:

	postgre_client() : c{
		"host=localhost "
		"port=5432 "
		"dbname=MusicSite2 "
		"user=postgres "
		"password=123456" } {};

	postgre_client(const postgre_client& p) = delete;
	postgre_client& operator=(const postgre_client& p) = delete;

	void create_table() {
		pqxx::work tx{ c };
		tx.exec("create table client (id integer primary key, name varchar, lastname varchar, email varchar)");
		tx.exec("create table phone (id integer primary key, value varchar, client_id integer)");
		tx.commit();
	}

	void add_client(int id, std::string name, std::string lastname, std::string email) {
		pqxx::work tx{ c };
		std::string query{ "insert into client values (" };
		query += std::to_string(id); query += ", '"; query += name; query += "', '"; query += lastname; query += "', '"; query += email; query += "')";
		std::cout << query << std::endl;
		tx.exec(query);
		tx.commit();
	}

	void add_phone(int id, std::string phone, int client_id) {
		pqxx::work tx{ c };
		std::string query{ "insert into phone values (" };
		query += std::to_string(id), query += ", '";  query += phone; query += "', "; query += std::to_string(client_id); query += ")";
		tx.exec(query);
		tx.commit();
	}

	void alter_client(std::string new_name, std::string new_lastname, std::string new_email, int new_id) {
		pqxx::work tx{ c };
		std::string query{ "update client set name = '" };
		query += new_name; query += "', lastname = '"; query += new_lastname; query += "', email = '"; query += new_email; query += "' where id = "; query += std::to_string(new_id);
		tx.exec(query);
		tx.commit();
	}

	void del_phone(int del_id) {
		pqxx::work tx{ c };
		std::string query{ "delete from phone where client_id = " }; query += std::to_string(del_id);
		tx.exec(query);
		tx.commit();
	}

	void del_client(int del_id) {
		pqxx::work tx{ c };
		std::string query{ "delete from client where id = " }; query += std::to_string(del_id);
		tx.exec(query);
		tx.commit();
	}

	void find_client_id(std::string s, std::string param) {
		pqxx::work tx{ c };
		std::string query{};
		if (param == "name") {
			query = { "select id from client where name = '" }; query += s; query += "'";
		}

		else if (param == "lastname") {
			query = { "select id from client where lastname = '" }; query += s; query += "'";
		}

		else if (param == "email") {
			query = { "select id from client where email = '" }; query += s; query += "'";
		}

		else if (param == "phone") {
			query = { "select id from client where id = (select client_id from phone where value = '" }; query += s; query += "')";
		}
		else {
			std::runtime_error("Wrong value of parameter!");
		}
		tx.exec(query);
		tx.commit();
		std::cout << "Client is found successfully!" << std::endl;
	}

};
