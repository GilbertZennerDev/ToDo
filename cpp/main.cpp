#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

const unsigned int genId()
{
	static unsigned int id = 0;
	return (++id);
}

void loadTasks(vector<string> &tasks, const vector<string> &cmds)
{
	string t;
	string filename;

	tasks.clear();
	try
	{
		filename = "todo.md";
		if (cmds.size() == 2) filename = cmds[1];
		ifstream file(filename);
		while (getline(file, t, '\n'))
			tasks.push_back(t);
		file.close();
	}
	catch (const exception &e)
	{
		cout << "Error loading List.\n";
	}
}

void saveTasks(const vector<string> &tasks, const vector<string> &cmds)
{
	string filename;

	try
	{
		filename = "todo.md";
		if (cmds.size() == 2) filename = cmds[1];
		ofstream file(filename);
		vector<string>::const_iterator it;
		
		it = tasks.begin() - 1;
		while (++it != tasks.end())
			file << *it << "\n";
		file.close();
	}
	catch (const exception &e)
	{
		cout << "Error saving List.\n";
	}
}

void listTasks(const vector<string> &tasks)
{
	unsigned int id;
	vector<string>::const_iterator it;

	id = 0;
	it = tasks.begin() - 1;
	cout << "Listing all tasks.\n";
	while (++it != tasks.end())
		cout << *it << " id: " << id++ << "\n";
}

void deleteTask(vector<string> &tasks, const string &deletetask)
{
	vector<string>::iterator it;

	cout << "Deleting task " << deletetask << "\n";
	it = find(tasks.begin(), tasks.end(), deletetask);
	if (it != tasks.end())
		tasks.erase(it);
	else
		cout << "Task " << deletetask << " not found\n";
}

void deleteId(vector<string> &tasks, const string &_id)
{
	unsigned int id;
	vector<string>::iterator it;

	cout << "Deleting task with id " << _id << "\n";
	try{
		id = stoi(_id);
		if (id < tasks.size())
			tasks.erase(tasks.begin() + id);
		else
			cout << "Error: Bad Id.\n";
	}
	catch (const exception &e)
	{
		cout << "Error bad input in deletetask\n";
	}
}

void addTask(vector<string> &tasks, const string &task)
{
	tasks.push_back(task);
}

const string concatText(const vector<string> &cmds)
{
	string concat;
	vector<string>::const_iterator it;

	if (cmds.size() < 2) return ""; 
	it = cmds.begin();
	while (++it != cmds.end() - 1)
		concat += *it + " ";
	concat += *it;
	return (concat);
}

int main(int ac, char **av)
{
	string t;
	string cmd;
	stringstream ss;
	vector<string> cmds;
	vector<string> tasks;

	tasks.push_back("flav");
	while (1)
	{
		cout << "Usage: 'add milk' or 'list' or 'delete milk' or exit:\nCommands: \nls: list items, \nsave x.md: save tasks to list, \nload x.md: load list from file.\n";
		getline(cin, cmd);
		ss.clear();
		ss.str(cmd);
		cmds.clear();
		while (getline(ss, t, ' '))
			cmds.push_back(t);
		if (cmds[0] == string("add")){addTask(tasks, concatText(cmds));}
		else if (cmds[0] == string("del")){deleteTask(tasks, concatText(cmds));}
		else if (cmds[0] == string("del_id")){deleteId(tasks, concatText(cmds));}
		else if (cmds[0] == string("list") || cmds[0] == string("ls")){listTasks(tasks);}
		else if (cmds[0] == string("save")){saveTasks(tasks, cmds);}
		else if (cmds[0] == string("load")){loadTasks(tasks, cmds);}
		else if (cmds[0] == string("exit")){cout << "Exiting ToDo...\n"; return (0);}
	}
	return (0);
}
