#include "CategoryList.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>


void addCategory(string& str, list<Category>& list)
{
	for (auto& s : str)
	{
		if (s == ',')
			s = ' ';
		s = toupper(s);
	}
	if (!doesCategoryExist(str, list))
	{
		Category category(str);
		list.push_back(category);
	}
}

// FOR LOADING, IS THIS NECESSARY?
void addCategory(string& str, int& ct, list<Category>& list)
{
	for (auto& s : str)
	{
		if (s == ',')
			s = ' ';
		s = toupper(s);
	}
	if (!doesCategoryExist(str, list))
	{
		Category category(str);
		list.push_back(category);
	}
}

void removeCategory(string& category, list<Category>& list)
{
	// check that there are no ingredients utilizing this category object first.
	// and chech that the category being removed is not NONE.
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?

	if (list.size() > 1)
	{
		for (auto& c : list)
		{
			if (c.getCategory() == category && c.getCategory() != "NONE" && c.getIngredientsUsingCategoryCount() == 0)
			{
				list.remove(c);
				break;
			}
		}
	}
//	else
//		cout << "There are ingredients using this category, cannot remove " << category << " from the category list." << endl;

}

bool doesCategoryExist(string& category, list<Category>& list)
{
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		if (it->getCategory() == category)
			return true;
	}
	return false;
}

void saveCategoryList(string& categoryListFile, list<Category>& list)
{
	ofstream fout;
	fout.open(categoryListFile, ios::out);
	for (auto& c : list)
	{
		fout << c.getCategory() << endl;
	}
	fout.close();
}

void loadCategoryList(string& categoryListFile, list<Category>& list)
{
	ifstream fin;
	fin.open(categoryListFile, ios::in);
	if (fin.is_open())
	{
		string line = "";
		while (getline(fin, line))
		{
			stringstream s(line);
			string token;
			vector<string> row;
			while (getline(s, token, ','))
				row.push_back(token);
			//			string cat = row[0];
			//			int count = stoi(row[1]);
			//			addCategory(cat, count);
			addCategory(row[0], list);
		}
	}
	else
		cout << categoryListFile << " was not found, load aborted." << endl;
	fin.close();
}

Category& getCategoryInList(string& cat, list<Category>& list)
{
	// decrement the current category's ingredientsUsingCategoryCount value that the ingredient is categorized as.
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?
	for (auto& c : list)
	{
		if (c.getCategory() == cat)
			return c;
	}
	return list.front();
}

/*

CategoryList::CategoryList()
{
	string str = "NONE";
	Category category(str);
	//	Category category(str, -1);
	categoryList.push_back(category);
	categoryListFile = "Category_List.csv";
}

CategoryList::CategoryList(string& fileName)
{
	string str = "NONE";
	Category category(str);
	//	Category category(str, -1);
	categoryList.push_back(category);
	categoryListFile = fileName;
}

void CategoryList::addCategory(string& str)
{
	for (auto& s : str)
	{
		if (s == ',')
			s = ' ';
		s = toupper(s);
	}
	if (!doesCategoryExist(str))
	{
		Category category(str);
		categoryList.push_back(category);
	}
}

// FOR LOADING, IS THIS NECESSARY?
void CategoryList::addCategory(string& str, int& ct)
{
	for (auto& s : str)
	{
		if (s == ',')
			s = ' ';
		s = toupper(s);
	}
	if (!doesCategoryExist(str))
	{
		Category category(str);
		categoryList.push_back(category);
	}
}

void CategoryList::removeCategory(string& category)
{
	// check that there are no ingredients utilizing this category object first.
	// and chech that the category being removed is not NONE.
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?

	for (auto& c : categoryList)
	{
		if (c.getCategory() == category && c.getCategory() != "NONE" && c.getIngredientsUsingCategoryCount() == 0)
		{
			categoryList.remove(c);
			break;
		}
	}
}

bool CategoryList::doesCategoryExist(string& category)
{
	for (auto it = categoryList.begin(); it != categoryList.end(); ++it)
	{
		if (it->getCategory() == category)
			return true;
	}
	return false;
}

void CategoryList::saveCategoryList()
{
	ofstream fout; 
	fout.open(categoryListFile, ios::out);
	for (auto& c : categoryList)
	{
		fout << c.getCategory() << endl;
	}
	fout.close();
}

void CategoryList::loadCategoryList()
{
	ifstream fin;
	fin.open(categoryListFile, ios::in);
	if (fin.is_open())
	{
		string line = "";
		while (getline(fin, line))
		{
			stringstream s(line);
			string token;
			vector<string> row;
			while (getline(s, token, ','))
				row.push_back(token);
//			string cat = row[0];
//			int count = stoi(row[1]);
//			addCategory(cat, count);
			addCategory(row[0]);
		}
	}
	else
		cout << categoryListFile << " was not found, load aborted." << endl;
	fin.close();
}

int CategoryList::getSize()
{
	return categoryList.size();
}

Category& CategoryList::getCategoryInList(string& cat)
{
	// decrement the current category's ingredientsUsingCategoryCount value that the ingredient is categorized as.
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?
	for (auto& c : categoryList)
	{
		if(c.getCategory() == cat)
			return c;
	}
	return categoryList.front();
}
*/