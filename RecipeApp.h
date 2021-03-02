#pragma once
#ifndef RECIPEAPP_H
#define RECIPEAPP_H

#include "RecipeList.h"
#include<wx/listctrl.h>
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

// RecipeFrame

//*************************************************************************************************

class RecipeFrame : public wxFrame
{
public:
    RecipeFrame(const wxString& title);
    void SetRecipe(Recipe& r);

protected:
    // file drop down menu
    void OnAbout(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);

    // edit drop down menu
    void OnSave(wxCommandEvent& e);

    wxPanel* panel;


private:
    Recipe currentRecipe;
    wxDECLARE_NO_COPY_CLASS(RecipeFrame);
//    wxDECLARE_EVENT_TABLE();
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
        updated = -1;
    }

    void InsertItemsInRecipeListReportDisplay(Recipe& r, int& i);
    void InsertItemsInIngredientListReportDisplay(Ingredient& ingred, int& i);
    void InsertItemsInCategoryListReportDisplay(Category& n, int& i);
    
    void LoadLists();
    // when the listController is renewed in RebuildList in MainFrame.
    // we use the following to pass lists from old listController to new listController
    list<Recipe> GetRecipes();
    list<Ingredient> GetIngredients();
    list<Category> GetCategories();

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

private:
    // do these objects go here?
    list<Category> categories;
    list<Ingredient> ingredients;
    list<pair<string, int>> mealTypes;
    list<Recipe> recipes;

    // files storing list data.
    string catFile = "testCategoryFile.csv";
    string ingredFile = "testIngredientFile.csv";
    string recipeFile = "testRecipeFile.csv";

    long updated;
    long currentList;       // tracker for which list we are currently viewing, used to open approrpiate windows to display details on the item selected

    Recipe* selectedRecipe = nullptr;
    Ingredient* selectedIngredient = nullptr;
    Category* selectedCategory = nullptr;

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

protected:
    // file drop down menu
    void OnAbout(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);

    // lists drop down menu
    void OnRecipeListReportDisplay(wxCommandEvent& e);
    void OnIngredientListReportDisplay(wxCommandEvent& e);
    void OnCategoryListReportDisplay(wxCommandEvent& e);


//    void OnToggleBell(wxCommandEvent& e);
//    void OnSetRowLines(wxCommandEvent& e);


//    void OnUpdateRowLines(wxUpdateUIEvent& e);

    wxPanel* panel;
    // MyListCtrl pointer object
    MainListCtrl* listController;

private:

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



    LIST_CTRL

};

#endif // !RECIPEAPP_H
