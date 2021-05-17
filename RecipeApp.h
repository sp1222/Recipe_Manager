#pragma once
#ifndef RECIPEAPP_H
#define RECIPEAPP_H


#include "RecipeList.h"
#include<wx/listctrl.h>
#include<wx/combo.h>
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

class MainListCtrl;    // forward
class AddCategoryFrame : public wxFrame
{
public:
    AddCategoryFrame();
    void SetParent(MainListCtrl* p);
protected:
    void OnFinalize(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);

    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxStaticText* nameLabel;
    wxTextCtrl* nameText;
private:
    MainListCtrl* parent;
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
    void OnUpdate(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);

    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxPanel* ingredientCountPanel;
    wxStaticText* nameLabel;
    wxStaticText* ingredientCountLabel;
    wxTextCtrl* nameText;
    wxStaticText* ingredientCountDisplay;

private:
    Category* currentCategory = new Category();
    MainListCtrl* parent;
    wxDECLARE_NO_COPY_CLASS(CategoryFrame);
    wxDECLARE_EVENT_TABLE();
};

//*************************************************************************************************

// AddCategoryFrame

//*************************************************************************************************

class MainListCtrl;    // forward
class AddIngredientFrame : public wxFrame
{
public:
    AddIngredientFrame();
    void SetParent(MainListCtrl* p);
protected:
    void OnFinalize(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);

    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxPanel* descriptionPanel;
    wxPanel* categoryPanel;
    wxStaticText* nameLabel;
    wxStaticText* descriptionLabel;
    wxStaticText* categoryLabel;
    wxTextCtrl* nameText;
    wxTextCtrl* descriptionText;
    wxComboBox* categoryComboBox;

private:
    MainListCtrl* parent;
    list<string>* categoryNames = new list<string>();
    wxDECLARE_NO_COPY_CLASS(AddIngredientFrame);
    wxDECLARE_EVENT_TABLE();

};

//*************************************************************************************************

// IngredientFrame class

//*************************************************************************************************

class MainListCtrl;     // forward
class IngredientFrame : public wxFrame
{
public:
    IngredientFrame(const wxString& title);
    void SetIngredient(Ingredient& i, list<Category>& cat);
    void SetParent(MainListCtrl* p);
    void RebuildTextFields();
protected:

    // edit drop down menu
//    void OnUpdateRecipe(wxCommandEvent& e);
    void OnUpdate(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);

    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxPanel* descriptionPanel;
    wxPanel* categoryPanel;
    wxPanel* recipeUsingIngredientCountPanel;
    wxStaticText* nameLabel;
    wxStaticText* descriptionLabel;
    wxStaticText* categoryLabel;
    wxStaticText* recipeUsingIngredientCountLabel;
    wxTextCtrl* nameText;
    wxTextCtrl* descriptionText;
    wxComboBox* categoryComboBox;   // make this a dropdown box
    wxStaticText* currentCategoryLabel;
    wxStaticText* currentRecipeUsingIngredientCountLabel;

private:
    Ingredient* currentIngredient = new Ingredient();
    list<Category>* catList = nullptr;
    wxArrayString* catStringList;
    MainListCtrl* parent;
    wxDECLARE_NO_COPY_CLASS(IngredientFrame);
    wxDECLARE_EVENT_TABLE();
};


//*************************************************************************************************

// IngredientsInRecipeFrame class

//*************************************************************************************************



class IngredientsInRecipeListCtrl;  // forward
class RecipeFrame;                  // forward
class IngredientInRecipeFrame : public wxFrame
{
public:
    IngredientInRecipeFrame(const wxString& title);
    void SetIngredientInRecipe(IngredientInRecipe& ir, list<Ingredient>& iList);
    void RebuildTextFields();
    void SetParents(IngredientsInRecipeListCtrl* p, RecipeFrame* rf);
    void SetStringArrays(list<string>& ingredNames);
protected:
    void OnUpdateIngredientInRecipe(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);
private:
    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxPanel* quantityPanel;
    wxPanel* unitPanel;
    wxStaticText* nameLabel;
    wxStaticText* quantityLabel;
    wxStaticText* unitLabel;
    wxStaticText* nameText;
    wxComboBox* nameComboBox;       // consider changing this to a list view format?  or include a second dropdown to narrow list down by category?
    wxTextCtrl* quantityText;
    wxStaticText* unitsText;
    wxComboBox* unitsComboBox;

    IngredientInRecipe* currentIngredientInRecipe;
    IngredientsInRecipeListCtrl* parent;
    RecipeFrame* parentRF;
    list<Ingredient>* ingredList;
    list<string> unitList;
    wxDECLARE_NO_COPY_CLASS(IngredientInRecipeFrame);
    wxDECLARE_EVENT_TABLE();

};




//*************************************************************************************************

// IngredientsInRecipeListCtrl class

//*************************************************************************************************

class RecipeFrame;  //forward
class IngredientsInRecipeListCtrl : public wxListCtrl
{
public:
    IngredientsInRecipeListCtrl(wxWindow* parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
        :wxListCtrl(parent, id, pos, size, style)
    {
    }

    void InsertIngredientsInRecipeListReportDisplay(IngredientInRecipe& ing, int i);
    void SetParent(RecipeFrame* p);
    void SetIngredientsInRecipeList(list<IngredientInRecipe>& ingredInRecipe);
    void SetIngredientList(list<Ingredient>& iList);
    void SetSelectedItem(string name);
    void ResetListView(long wxFlags = wxLC_REPORT, bool withText = true);
    void BuildIngredientsInRecipeListReportDisplay();
    void UpdateModifiedIngredient();
    string GetSelectedIngredient();
protected:
    void OnActivated(wxListEvent& e);
    void OnSelected(wxListEvent& e);
    void OnColumnHeaderClick(wxListEvent& e);
private:

    list<IngredientInRecipe>* ingredients;
    IngredientInRecipe* selectedIngredient;
    IngredientInRecipeFrame* ingredientInRecipeFrame;
    RecipeFrame* parent;
    list<Ingredient>* ingredList;
    wxDECLARE_NO_COPY_CLASS(IngredientsInRecipeListCtrl);
    wxDECLARE_EVENT_TABLE();
};



//*************************************************************************************************

// AddIngredientToRecipeFrame class

//*************************************************************************************************

class RecipeFrame;  //forward
class AddIngredientToRecipeFrame : public wxFrame
{
public:
    AddIngredientToRecipeFrame();
    void SetParent(RecipeFrame* p);
    void SetComboBoxLists(list<Ingredient>& iList);
protected:
    void OnFinalize(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);
private:
    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxPanel* quantityPanel;
    wxPanel* unitsPanel;
    wxStaticText* nameLabel;
    wxStaticText* quantityLabel;
    wxStaticText* unitsLabel;
    wxComboBox* nameComboBox;
    wxTextCtrl* quantityText;
    wxComboBox* unitsComboBox;

    RecipeFrame* parent;
    list<Ingredient>* ingredList;
    list<string> unitList;
    wxDECLARE_NO_COPY_CLASS(AddIngredientToRecipeFrame);
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
    void SetRecipe(Recipe& r, list<pair<string, int>>& tList, list<Ingredient>& iList, bool in = false);
    void RebuildTextFields();
    void SetParent(MainListCtrl* p);
    void UpdateIngredientInRecipe();
    void AddIngredientToRecipe(string& name, float& qty, string& unit);
protected:

    // edit drop down menu
    void OnUpdateRecipe(wxCommandEvent& e);
    void OnAddIngredient(wxCommandEvent& e);
    void OnRemoveIngredient(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);

private:
    bool isnew = false;
    wxPanel* mainPanel;
    wxPanel* namePanel;
    wxPanel* cuisineMealtypePanel;
    wxPanel* servingsPanel;
    wxPanel* yieldPanel;
    wxPanel* descriptionPanel;
    wxPanel* directionPanel;
    wxPanel* ingredientsPanel;
    wxStaticText* nameLabel;
    wxStaticText* cuisineLabel;
    wxStaticText* mealtypeLabel;
    wxStaticText* servingsLabel;
    wxStaticText* yieldLabel;
    wxStaticText* descriptionLabel;
    wxStaticText* directionLabel;
    wxStaticText* ingredientsLabel;
    wxTextCtrl* nameText;
    wxTextCtrl* cuisineText;            // change to combobox?
    wxTextCtrl* mealtypeText;
//    wxStaticText* mealtypeText;
//    wxComboBox* mealtypeComboBox;
    wxTextCtrl* servingsText;
    wxTextCtrl* yieldText;
    wxStaticText* yieldUnitCurrent;
    wxComboBox* yieldUnitComboBox;
    wxTextCtrl* descriptionText;
    wxTextCtrl* directionText;
    IngredientsInRecipeListCtrl* listIngredientsInRecipe;

    Recipe* currentRecipe = new Recipe();
    MainListCtrl* parent;
    AddIngredientToRecipeFrame* addIngredientToRecipe;
    list<pair<string, int>>* typeList;
    list<Ingredient>* ingredList;
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
    void SaveCategories();
    void SaveIngredients();
    void SaveRecipes();

    void LoadLists();
    void AddNewCategory(string& c);
    void AddNewIngredient(string& name, string& desc, string& cat);
    void RemoveCategory();
    void RemoveIngredient();
    void RemoveRecipe();
    void CreateNewRecipe();
    void AddRecipe(Recipe& nr);
    void GetCategoryNamesList(list<string>& names);
    string GetSelectedCategoryName();
    string GetSelectedIngredientName();
    string GetSelectedRecipeName();

    void GetIngredientsList(list<string>& list);
    

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
    CategoryFrame* categoryFrame;
    IngredientFrame* ingredientFrame;
    RecipeFrame* recipeFrame;
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
    void SetParent(RecipeApp* p);

protected:
    // file drop down menu
    void OnAbout(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);

    // lists drop down menu
    void OnRecipeListReportDisplay(wxCommandEvent& e);
    void OnIngredientListReportDisplay(wxCommandEvent& e);
    void OnCategoryListReportDisplay(wxCommandEvent& e);


    void OnAddCategory(wxCommandEvent& e);
    void OnRemoveCategory(wxCommandEvent& e);
    void OnAddIngredient(wxCommandEvent& e);
    void OnRemoveIngredient(wxCommandEvent& e);
    void OnAddRecipe(wxCommandEvent& e);
    void OnRemoveRecipe(wxCommandEvent& e);

    wxPanel* panel;
    MainListCtrl* listController;

private:
    wxMenu* menuFile;
    wxMenu* menuList;
    wxMenu* menuCategoryListEditor;
    wxMenu* menuIngredientListEditor;
    wxMenu* menuRecipeListEditor;
    wxMenuBar* menuBar;
    RecipeApp* parent;


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


    LABEL,

    CATEGORY_ADD_NEW,
    CATEGORY_REMOVE_SELECTED,

    CATEGORY_NAME_TEXT_CTRL,
    CATEGORY_INGREDIENT_COUNT_TEXT_CTRL,


    INGREDIENT_ADD_NEW,
    INGREDIENT_REMOVE_SELECTED,

    INGREDIENT_NAME_TEXT_CTRL,
    INGREDIENT_DESCRIPTION_TEXT_CTRL,
    INGREDIENT_CATEGORY_TEXT_CTRL,
    INGREDIENT_RECIPES_COUNT_TEXT_CTRL,


    INGREDIENT_IN_RECIPE_NAME_TEXT_CTRL,
    INGREDIENT_IN_RECIPE_QUANTITY_TEXT_CTRL,
    INGREDIENT_IN_RECIPE_UNIT_TEXT_CTRL,



    RECIPE_ADD_NEW,
    RECIPE_REMOVE_SELECTED,
    RECIPE_NAME_TEXT_CTRL,
    RECIPE_MEALTYPE_TEXT_CTRL,
    RECIPE_CUISINE_TEXT_CTRL,
    RECIPE_SERVINGS_TEXT_CTRL,
    RECIPE_YIELD_TEXT_CTRL,
    RECIPE_YIELD_UNIT_COMBO_BOX,
    RECIPE_DESCRIPTION_TEXT_CTRL,
    RECIPE_DIRECTIONS_TEXT_CTRL,
    RECIPE_ADD_INGREDIENT,
    RECIPE_REMOVE_INGREDIENT,

    UPDATE,
    UPDATE_NEW,
    FINALIZE,
    SAVE,
    MAIN_LIST_CTRL,
    RECIPE_INGREDIENTS_LIST_CTRL

};

#endif // !RECIPEAPP_H
