#include "CategoryList.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>


bool addCategory(string& str, list<Category>& list)
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
		return true;
	}
	return false;
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

// Change to using indices to quickly locate and remove the category from the list.
// now that the lists will now be sorted to match MainListCtrl.
bool removeCategory(string& category, list<Category>& list)
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
				return true;
			}
		}
	}
	return false;
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

void sortCategories(int byCol, list<Category>& list)
{
	switch (byCol)
	{
	case 0:
		list.sort(compareCategoryNames);
		break;
	case 1:
		list.sort(compareCategoryIngredientCount);
		break;
	default:
		break;
	}
}

bool compareCategoryNames(const Category& first, const Category& second)
{
	unsigned  i = 0;
	while ((i < first.getCategory().length()) && (i < second.getCategory().length()))
	{
		if (tolower(first.getCategory()[i]) < tolower(second.getCategory()[i]))
			return true;
		else if (tolower(first.getCategory()[i]) > tolower(second.getCategory()[i]))
			return false;
		i++;
	}
	return (first.getCategory().length() < second.getCategory().length());
}

bool compareCategoryIngredientCount(const Category& first, const Category& second)
{
	return (first.getIngredientsUsingCategoryCount() < second.getIngredientsUsingCategoryCount());
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