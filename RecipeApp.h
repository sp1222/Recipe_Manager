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

class RecipeApp: public wxApp
{
public:
    virtual bool OnInit();
private:
};


//*************************************************************************************************
// ListCtrl

class ListCtrl : public wxListCtrl
{
public:
    ListCtrl(wxWindow* parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
        :wxListCtrl(parent, id, pos, size, style)
    {
        updated = -1;
    }

    void InsertItemInRecipeListReportDisplay(Recipe& r, int& i);
    void InsertItemInIngredientListReportDisplay(Ingredient& ingred, int& i);
    void InsertItemInCategoryListReportDisplay(Category& n, int& i);
private:
    long updated;
};


//*************************************************************************************************
// MainFrame

class MainFrame: public wxFrame
{
public:
    MainFrame(const wxString& title);

protected:
    // file drop down menu
    void OnAbout(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);

    void OnRecipeListReportDisplay(wxCommandEvent& e);
    void OnIngredientListReportDisplay(wxCommandEvent& e);
    void OnCategoryListReportDisplay(wxCommandEvent& e);

//    void OnToggleBell(wxCommandEvent& e);
//    void OnSetRowLines(wxCommandEvent& e);


//    void OnUpdateRowLines(wxUpdateUIEvent& e);

    wxPanel* panel;
    // MyListCtrl pointer object
    ListCtrl* listController;

private:
    // do these objects go here?
    list<Category> categories;
    list<Ingredient> ingredients;
    list<pair<string, int>> mealTypes;
    list<Recipe> recipes;
    string catFile = "testCategoryFile.csv";
    string ingredFile = "testIngredientFile.csv";
    string recipeFile = "testRecipeFile.csv";

    // functions that redefine the list controller object.
    void RebuildList(long custFlags, long wxFlags = wxLC_REPORT, bool withText = true);
    void BuildRecipeListReportDisplay();
    void BuildIngredientListReportDisplay();
    void BuildCategoryListReportDisplay();

    wxDECLARE_NO_COPY_CLASS(MainFrame);
    wxDECLARE_EVENT_TABLE();
};

wxDECLARE_APP(RecipeApp);

//*************************************************************************************************
// IDs for menu commands.

enum
{
    ABOUT = wxID_ABOUT,
    EXIT = wxID_EXIT,

    RECIPE_LIST_REPORT_DISPLAY = wxID_HIGHEST + 1,
    INGREDIENT_LIST_REPORT_DISPLAY,
    CATEGORY_LIST_REPORT_DISPLAY,


//    LIST_TOGGLE_BELL,
//    LIST_ROW_LINES,



    LIST_CTRL

};

#endif // !RECIPEAPP_H
