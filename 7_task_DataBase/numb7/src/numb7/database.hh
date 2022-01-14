#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <ranges>

struct Account {
	unsigned int id; // идентификатор
	std::string login; // логин
	std::string name; // имя
	std::string shell; // оболочка
	std::string home_directory; // домашняя директория
};

std::vector<Account> generate_db(int num_sh, int num_bash, int num_ksh, int num_others, bool doub = false)
{
	std::vector<Account> result;
	int i = num_sh+num_bash+num_ksh+num_others;
	while ((num_sh>0) || (num_bash > 0) || (num_ksh > 0) || (num_others > 0))
	{
		Account tmp;
		tmp.id = i;
		if ((i % 5 == 0)&&(doub)) tmp.id = i + 1;
		tmp.login = "login_" + std::to_string(i);
		tmp.name = "name_" + std::to_string(i);
		tmp.home_directory = "/home/" + tmp.name;
		//std::cout << i << std::endl;
		i--;
		if (num_sh > 0)
		{
			tmp.shell = "/bin/sh";
			num_sh--;
			result.push_back(tmp);
			continue;
		}
		if (num_bash > 0)
		{
			tmp.shell = "/bin/bash";
			num_bash--;
			result.push_back(tmp);
			continue;
		}
		if (num_ksh > 0)
		{
			tmp.shell = "/bin/ksh";
			num_ksh--;
			result.push_back(tmp);
			continue;
		}
		if (num_others > 0)
		{
			tmp.shell = "other";
			num_others--;
			result.push_back(tmp);
			continue;
		}
		
	};
	return result;
}

std::map<int, Account> generate_db_map(const std::vector<Account>& db)
{
	std::map<int, Account> result;
	for (auto i : db)
	{
		result.insert({ i.id, i});
	}
	return result;
}

std::unordered_map<int, Account> generate_db_unordered_map(const std::vector<Account>& db)
{
	std::unordered_map<int, Account> result;
	for (auto i : db)
	{
		result.insert({ i.id, i });
	}
	return result;
}

std::unordered_set<std::string> create_unordered_set_fromdb(const std::vector<Account>& db)
{
	std::unordered_set<std::string> result;
	for (auto i : db)
	{
		result.insert(i.shell);
	}
	return result;
}
bool isBash(const Account& obj)
{
	return !((bool)(obj.shell.compare("/bin/bash")));
}
int main()
{
	//one
	std::vector<Account> db = generate_db(330, 24, 500, 450);
	auto it = std::ranges::find_if(db.begin(), db.end(), isBash);
	std::vector<Account> result1;
	while (true)
	{
		it = std::ranges::find_if(it, db.end(), isBash);
		if (it != db.end()) {
			result1.push_back(*it);
	//		std::cout << (*it).id << std::endl;
			++it;
		}
		else break;
	}
	//two
	std::map<int, Account> dbm = generate_db_map(db);
	std::vector<Account> result2;
	for (std::map<int, Account>::iterator i = dbm.lower_bound(1); (i!=dbm.upper_bound(1000) && i != dbm.end()); i++)
	{
		result2.push_back(i->second);
	}
	//three
	std::unordered_map<std::string, int> mp;
	for (Account R : db) {
		std::string& l = R.shell;
		if (mp.count(l) == 0)
			mp.insert({ l,0 });
		mp[l]++;
	};

	//four
	db = generate_db(330, 24, 500, 450, true);
	std::unordered_set<int> st1;
	std::vector<Account> result;
	for (auto i : db)
	{
		if (st1.insert(i.id).second == 0) result.push_back(i);
	}
	return 0;
}
