#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iterator>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Account {
    unsigned int id; // идентификатор
    string login; // логин
    string name; // имя
    string shell; // оболочка
    string home_directory; // домашняя директория
};

vector<Account> LoadData(int sh, int bash, int ksh, int csh, int tcsh, int duplicate = 0)
{
    vector<Account> result;
    int i = sh + bash + ksh + csh + tcsh;
    for (int j = 1; j < i + 1; j++) {
        Account rec;
        rec.id = j;
        if ((duplicate != 0) && (j % 2 == 0)){
            duplicate--;
            rec.id += 1;
        }
        rec.login = "login" + to_string(i);
        rec.name = "user" + to_string(i);
        rec.home_directory = "home/" + rec.name;
        if (sh > 0)
        {
            rec.shell = "/bin/sh";
            sh--;
            result.push_back(rec);
        }
        else {
            if (bash > 0)
            {
                rec.shell = "/bin/bash";
                bash--;
                result.push_back(rec);
            }
            else {
                if (ksh > 0)
                {
                    rec.shell = "/bin/ksh";
                    ksh--;
                    result.push_back(rec);
                }
                else {
                    if (csh > 0)
                    {
                        rec.shell = "/bin/csh ";
                        csh--;
                        result.push_back(rec);
                    }
                    else
                    {
                        if (tcsh > 0)
                        {
                            rec.shell = "/bin/tcsh ";
                            tcsh--;
                            result.push_back(rec);

                        }
                    }
                }
            }
        }

    }
    return result;
};

map<int, Account> LoadData_map(const vector<Account>& base)
{
    map<int, Account> result;
    for (auto i : base)
    {
        result.insert({ i.id, i });
    }
    return result;
}

unordered_map<int, Account> LoadData_unordered_map(const vector<Account>& base)
{
    unordered_map<int, Account> result;
    for (auto i : base)
    {
        result.insert({ i.id, i });
    }
    return result;
}

unordered_set<string> create_unordered_set_frombase(const vector<Account>& base)
{
    unordered_set<string> result;
    for (auto i : base)
    {
        result.insert(i.shell);
    }
    return result;
}
bool Bash(const Account& obj)
{
    if (obj.shell == "/bin/bash")
        return true;
    else
        return false;
}

auto task_1(vector<Account> base) {
    auto x = find_if(base.begin(), base.end(), Bash);
    vector<Account> result;
    while (true)
    {
        x = find_if(x, base.end(), Bash);
        if (x != base.end()) {
            result.push_back(*x);
            ++x;
        }
        else break;
    }
    return result;
}

auto task_2(vector<Account> base) {
    map<int, Account> map_data = LoadData_map(base);
    vector<Account> result;
    for (auto i = map_data.lower_bound(1); (i != map_data.upper_bound(1000) && i != map_data.end()); i++)
    {
        result.push_back(i->second);
    }
    return result;
}

auto task_3(vector<Account> base) {
    unordered_map<string, int> umap_data;
    for (auto i : base) {
        string& l = i.shell;
        if (umap_data.count(l) == 0)
            umap_data.insert({ l,0 });
        umap_data[l]++;
    };
    return umap_data;
}

auto task_4(vector<Account> base) {
    unordered_set<int> u_set;
    vector<Account> result;
    for (auto i : base)
    {
        if (u_set.insert(i.id).second == 0) result.push_back(i);
    }
    return result;
}
