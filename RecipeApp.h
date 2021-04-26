#pragma once
#ifndef RECIPEAPP_H
#define RECIPEAPP_H

#include "RecipeList.h"
#include<wx/listctrl.h>
#include<wx/notebook.h>
#include<wx/wxprec.h>
#ifndef WX_PRECOMP
#include<wx/wx.h>
#endif
    

//*************************************************************************************************

// RecipeApp

//*************************************************************************************************

class RecipeApp: public wxApp
{
public:
    virtual bool OnInit();
private:
};

//*************************************************************************************************

// AddCategoryFrame

//*************************************************************************************************

class MainFrame;    // forward
class AddCategoryFrame : public wxFrame
{
public:
    AddCategoryFrame();
    void SetParent(MainFrame* p);
protected:
    void OnFinalize(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);

    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxStaticText* nameLabel;
    wxTextCtrl* nameText;
private:
    MainFrame* parent;
    wxDECLARE_NO_COPY_CLASS(AddCategoryFrame);
    wxDECLARE_EVENT_TABLE();

};

//*************************************************************************************************

// CategoryFrame

//*************************************************************************************************

class MainListCtrl;     // forward
class CategoryFrame : public wxFrame
{
public:
    CategoryFrame(const wxString& title);
    void SetCategory(Category& c);
    void SetParent(MainListCtrl* p);
    void RebuildTextFields();
protected:

    // edit drop down menu
//    void OnUpdateRecipe(wxCommandEvent& e);
    void OnAdd(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);

    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxPanel* ingredientCountPanel;
    wxPanel* labelPanel;
    wxPanel* textPanel;
    wxStaticText* nameLabel;
    wxStaticText* ingredientCountLabel;
    wxStaticText* nameText;
    wxStaticText* ingredientCountDisplay;

private:
    Category* currentCategory = new Category();
    MainListCtrl* parent;
    wxDECLARE_NO_COPY_CLASS(CategoryFrame);
    wxDECLARE_EVENT_TABLE();
};



//*************************************************************************************************

// IngredientsInRecipeListCtrl class

//*************************************************************************************************

class IngredientsInRecipeListCtrl : public wxListCtrl
{
public:
    IngredientsInRecipeListCtrl(wxWindow* parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
        :wxListCtrl(parent, id, pos, size, style)
    {
        updated = -1;
    }

    void InsertIngredientsInRecipeListReportDisplay();
    void SetIngredientsInRecipeList(list<IngredientInRecipe>& list);
    void SetSelectedItem(string name);
    void OnActivated(wxListEvent& e);
    void OnSelected(wxListEvent& e);
    void OnColumnHeaderClick(wxListEvent& e);
    void ResetListView(long wxFlags = wxLC_REPORT, bool withText = true);
    void BuildIngredientsInListReportDisplay();

protected:
private:

    long updated;
    list<IngredientInRecipe>* ingredients;
    IngredientInRecipe* selectedIngredient;

    wxDECLARE_NO_COPY_CLASS(IngredientsInRecipeListCtrl);
    wxDECLARE_EVENT_TABLE();
};



//*************************************************************************************************

// RecipeFrame

//*************************************************************************************************

class MainListCtrl;     // forward
class RecipeFrame : public wxFrame
{
public:
    RecipeFrame(const wxString& title);
    void SetRecipe(Recipe& r, list<pair<string, int>>& tList);
    void RebuildTextFields();
    void SetParent(MainListCtrl* p);

protected:

    // edit drop down menu
    void OnUpdateRecipe(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);

    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxPanel* mealTypePanel;
    wxPanel* descriptionPanel;
    wxPanel* directionPanel;
    wxPanel* labelPanel;
    wxPanel* textPanel;
    wxStaticText* nameLabel;
    wxStaticText* mealtypeLabel;
    wxStaticText* descriptionLabel;
    wxStaticText* directionLabel;
    wxTextCtrl* nameText;
    wxTextCtrl* mealtypeText;
    wxTextCtrl* descriptionText;
    wxTextCtrl* directionText;
    IngredientsInRecipeListCtrl* listIngredientsInRecipe;

private:
    Recipe* currentRecipe = new Recipe();
    MainListCtrl* parent;
    list<pair<string, int>>* typeList;
    wxDECLARE_NO_COPY_CLASS(RecipeFrame);
    wxDECLARE_EVENT_TABLE();
};


//*************************************************************************************************

// MainListCtrl class

//*************************************************************************************************

class MainListCtrl : public wxListCtrl
{
public:
    MainListCtrl(wxWindow* parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
        :wxListCtrl(parent, id, pos, size, style)
    {
    }

    void InsertItemsInRecipeListReportDisplay(Recipe& r, int& i);
    void InsertItemsInIngredientListReportDisplay(Ingredient& ingred, int& i);
    void InsertItemsInCategoryListReportDisplay(Category& n, int& i);

    void SaveAllLists();
    // build these
    void SaveCategories();
    void SaveRecipes();
    void SaveIngredients();

    void LoadLists();
    void AddNewCategory(string& c);
    void RemoveCategory();
    string GetSelectedCategoryName();

    // when the listController is renewed in RebuildList in MainFrame.
    // we use the following to pass lists from old listController to new listController

    void SetCurrentList(long c);
    long GetCurrentList();   

    void SetSelectedItem(string name);
    void OnActivated(wxListEvent& e);
    void OnSelected(wxListEvent& e);
    void OnColumnHeaderClick(wxListEvent& e);
    void ResetListView(long custFlags, long wxFlags = wxLC_REPORT, bool withText = true);
    void BuildRecipeListReportDisplay();
    void BuildIngredientListReportDisplay();
    void BuildCategoryListReportDisplay();


protected:
    RecipeFrame* recipeFrame;
    CategoryFrame* categoryFrame;

private:
    // data.
    list<Category> categories;
    list<Ingredient> ingredients;
    list<pair<string, int>> mealTypes;
    list<Recipe> recipes;

    // files storing list data.
    string categoryFile = "testCategoryFile.csv";
    string ingredFile = "testIngredientFile.csv";
    string recipeFile = "testRecipeFile.csv";

    long currentList;       // tracker for which list we are currently viewing, used to open approrpiate windows to display details on the item selected

    Recipe* selectedRecipe = nullptr;
    Ingredient* selectedIngredient = nullptr;
    Category* selectedCategory = nullptr;
    wxListItem selectedItem;

    wxDECLARE_NO_COPY_CLASS(MainListCtrl);
    wxDECLARE_EVENT_TABLE();
};

//*************************************************************************************************

// MainFrame class

//*************************************************************************************************

class MainFrame: public wxFrame
{
public:
    MainFrame(const wxString& title);
    void AddCategory(string& c);

protected:
    // file drop down menu
    void OnAbout(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);

    // lists drop down menu
    void OnRecipeListReportDisplay(wxCommandEvent& e);
    void OnIngredientListReportDisplay(wxCommandEvent& e);
    void OnCategoryListReportDisplay(wxCommandEvent& e);


    void OnAddCategory(wxCommandEvent& e);
    void OnRemoveCategory(wxCommandEvent& e);



//    void OnToggleBell(wxCommandEvent& e);
//    void OnSetRowLines(wxCommandEvent& e);


//    void OnUpdateRowLines(wxUpdateUIEvent& e);

    wxPanel* panel;
    MainListCtrl* listController;

private:
    wxMenu* menuFile;
    wxMenu* menuList;
    wxMenu* menuCategoryListEditor;
    wxMenu* menuIngredientListEditor;
    wxMenu* menuRecipeListEditor;
    wxMenuBar* menuBar;


    wxDECLARE_NO_COPY_CLASS(MainFrame);
    wxDECLARE_EVENT_TABLE();
};

wxDECLARE_APP(RecipeApp);

//*************************************************************************************************

// IDs for menu commands.

//*************************************************************************************************

enum
{
    ABOUT = wxID_ABOUT,
    EXIT = wxID_EXIT,

    NO_LIST_DISPLAY = wxID_HIGHEST + 1,
    RECIPE_LIST_REPORT_DISPLAY,
    INGREDIENT_LIST_REPORT_DISPLAY,
    CATEGORY_LIST_REPORT_DISPLAY,


    //    LIST_TOGGLE_BELL,
    //    LIST_ROW_LINES,
    LABEL,

    CATEGORY_ADD_NEW,
    CATEGORY_REMOVE_SELECTED,

    CATEGORY_NAME_TEXT_CTRL,
    CATEGORY_INGREDIENT_COUNT_TEXT_CTRL,


    INGREDIENT_ADD_NEW,
    INGREDIENT_REMOVE_SELECTED,


    RECIPE_ADD_NEW,
    RECIPE_REMOVE_SELECTED,
    RECIPE_NAME_TEXT_CTRL,
    RECIPE_MEALTYPE_TEXT_CTRL,
    RECIPE_DESCRIPTION_TEXT_CTRL,
    RECIPE_DIRECTIONS_TEXT_CTRL,


    UPDATE,
    FINALIZE,
    SAVE,
    MAIN_LIST_CTRL,
    RECIPE_INGREDIENTS_LIST_CTRL

};

#endif // !RECIPEAPP_H