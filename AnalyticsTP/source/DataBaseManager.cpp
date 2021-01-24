#include "DataBaseManager.h"
#include <iostream>

DataBaseManager::DataBaseManager() {
	this->currentAction = Action::NONE;
	this->query = u8"";

	this->con = nullptr;

	this->results.clear();
	this->readyResults = false;
}

DataBaseManager::~DataBaseManager() {
	//if (this->con != NULL)
		//mysql_close(this->con);
}

void DataBaseManager::clear() {
	this->currentAction = Action::NONE;
	// this->query = u8"";

	//this->con = nullptr;

	this->results.clear();
	this->readyResults = false;
}

void DataBaseManager::Listening() {
	switch (this->currentAction) {
	case Action::INSERT:
		this->Insert();
		break;
	case Action::SELECT:
		this->readyResults = false;
		if(this->Select())
			this->readyResults = true;
		break;
	}

	if (this->currentAction != Action::NONE)
		this->currentAction = Action::NONE;
}

bool DataBaseManager::isResultsReady() {
	if (this->readyResults) {
		this->readyResults = false;
		return true;
	}
	else
		return false;
}

void DataBaseManager::setQuery(Action action, const std::string query) {
	this->currentAction = action;
	this->query = query;
}

bool DataBaseManager::Connect() {
	this->con = mysql_init(NULL);
	mysql_set_character_set(this->con, "utf8");
	if (this->con == NULL)
	{
		std::cerr << mysql_error(this->con);
		return false;
	}
	if (mysql_real_connect(this->con, "remotemysql.com", "3vcjUeGfHf", "bHLiKnXBaa", "3vcjUeGfHf", 3306, NULL, 0) == NULL) // username, pass, db, port
	{
		std::cerr << mysql_error(this->con);
		mysql_close(this->con);
		return false;
	}
	std::cout << "Connected to DB" << std::endl;
	return true;
}

std::vector<std::vector<std::string>> DataBaseManager::getResults() {
	return this->results;
}

//#include <fstream>
bool DataBaseManager::Insert() {
	/*std::fstream plik("nazwa_pliku.txt", std::ios::in | std::ios::out);
	this->query = u8"INSERT INTO `errands` (`id`, `nazwa`, `data`, `dojazd`, `holowanie`, `powrot`, `kierowca`, `cena`) VALUES (NULL, 'nowytest', '2020-10-10', '11', '11', '11', '¿¹Ÿêæñó³¯¥ÊÆÑÓ£', '11');";
	if (plik.good() == true)
	{
		plik.write(this->query.c_str(), this->query.length());
	}*/
	if (!this->Connect())
		return false;
	if (mysql_query(this->con, this->query.c_str()))
	{
		std::cerr << mysql_error(this->con);
		mysql_close(this->con);
		return false;
	}

	mysql_close(this->con);
	std::cout << "[INSERT] Success" << std::endl;
	this->query = u8"";

	return true;
}

bool DataBaseManager::Select() {
	this->results.clear();
	if (!this->Connect())
		return false;
	if (mysql_query(this->con, this->query.c_str()))
	{
		std::cerr << mysql_error(this->con);
		mysql_close(this->con);
		return false;
	}

	MYSQL_RES* res = mysql_store_result(con);
	std::cout << "Wyszukano " << mysql_num_rows(res) << " wierszy" << std::endl;
	for (unsigned long long i = 0; i < mysql_num_rows(res); i++) {
		MYSQL_ROW row = mysql_fetch_row(res);
		std::cout << "Wiersz[" << i << "], ilosc pol " << mysql_num_fields(res) << std::endl;
		std::vector<std::string> row_result;
		for (unsigned long long j = 0; j < mysql_num_fields(res); j++) {
			//std::cout << row[j] << " ";
			if (row[j] != NULL)
				row_result.push_back(row[j]);
			else
				row_result.push_back("");
		}
		std::cout << std::endl;
		if (row_result.empty()) {
			std::cerr << "Zapytanie zwraca puste wiersze!" << std::endl;
			row_result.clear();
			return false;
		}
		this->results.push_back(row_result);
		row_result.clear();
	}

	mysql_free_result(res);
	mysql_close(con);
	std::cout << "[SELECT] Success" << std::endl;
	return true;
}