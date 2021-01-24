#pragma once
#include "mysql.h"
#include <string>
#include <vector>

class DataBaseManager {
public:
	DataBaseManager();
	~DataBaseManager();

	enum class Action { NONE, INSERT, SELECT };

	void Listening();
	void setQuery(Action action, const std::string query);

	std::vector<std::vector<std::string>> getResults();
	bool isResultsReady();
	
	void clear();
private:
	MYSQL* con;

	bool Connect();

	bool Insert();
	bool Select();

	Action currentAction;

	std::string query;
	std::vector<std::vector<std::string>> results;
	bool readyResults;

};