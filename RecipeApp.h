#pragma once
#ifndef RECIPEAPP_H
#define RECIPEAPP_H

#include<wx/calctrl.h>
#include<wx/combo.h>
#include<wx/datetime.h>
#include<wx/grid.h>
#include<wx/listctrl.h>
#include<wx/scrolbar.h>
#include<wx/wxprec.h>

#include "RecipeList.h"

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

private:
    wxMenu* menuOptions;
    wxMenuBar* menuBar;
    wxPanel* mainPanel = nullptr;
    wxPanel* namePanel = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxTextCtrl* nameText = nullptr;
    MainListCtrl* parent = nullptr;
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

private:
    wxMenu* menuOptions = nullptr;
    wxMenuBar* menuBar = nullptr;
    wxPanel* mainPanel = nullptr;
    wxPanel* namePanel = nullptr;
    wxPanel* ingredientCountPanel = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxStaticText* ingredientCountLabel = nullptr;
    wxTextCtrl* nameText = nullptr;
    wxStaticText* ingredientCountDisplay = nullptr;
    Category* currentCategory = nullptr;
    MainListCtrl* parent;
    wxDECLARE_NO_COPY_CLASS(CategoryFrame);
    wxDECLARE_EVENT_TABLE();
};

//*************************************************************************************************

// AddIngredientFrame

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

private:
    wxMenu* menuOptions;
    wxMenuBar* menuBar;
    wxPanel* mainPanel = nullptr;
    wxPanel* namePanel = nullptr;
    wxPanel* descriptionPanel = nullptr;
    wxPanel* categoryPanel = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxStaticText* descriptionLabel = nullptr;
    wxStaticText* categoryLabel = nullptr;
    wxTextCtrl* nameText = nullptr;
    wxTextCtrl* descriptionText = nullptr;
    wxComboBox* categoryComboBox = nullptr;
    MainListCtrl* parent = nullptr;
    list<string> categoryNames;
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

    void OnUpdate(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);


private:
    wxMenu* menuOptions;
    wxMenuBar* menuBar;
    wxScrolledWindow* mainPanel = nullptr;
    wxPanel* namePanel = nullptr;
    wxPanel* descriptionPanel = nullptr;
    wxPanel* categoryPanel = nullptr;
    wxPanel* recipeUsingIngredientCountPanel = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxStaticText* descriptionLabel = nullptr;
    wxStaticText* categoryLabel = nullptr;
    wxStaticText* recipeUsingIngredientCountLabel = nullptr;
    wxTextCtrl* nameText = nullptr;
    wxTextCtrl* descriptionText = nullptr;
    wxComboBox* categoryComboBox = nullptr;   // make this a dropdown box
    wxStaticText* currentCategoryLabel = nullptr;
    wxStaticText* currentRecipeUsingIngredientCountLabel = nullptr;
    Ingredient* currentIngredient = nullptr;
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
    wxMenu* menuOptions;
    wxMenuBar* menuBar;
    wxPanel* mainPanel = nullptr;
    wxPanel* namePanel = nullptr;
    wxPanel* quantityPanel = nullptr;
    wxPanel* unitPanel = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxStaticText* quantityLabel = nullptr;
    wxStaticText* unitLabel = nullptr;
    wxStaticText* nameText = nullptr;
    wxComboBox* nameComboBox = nullptr;       // consider changing this to a list view format?  or include a second dropdown to narrow list down by category?
    wxTextCtrl* quantityText = nullptr;
    wxStaticText* unitsText = nullptr;
    wxComboBox* unitsComboBox = nullptr;

    IngredientInRecipe* currentIngredientInRecipe = nullptr;
    IngredientsInRecipeListCtrl* parent = nullptr;
    RecipeFrame* parentRF = nullptr;
    list<Ingredient>* ingredList = nullptr;
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

    list<IngredientInRecipe>* ingredients = nullptr;
    IngredientInRecipe* selectedIngredient = nullptr;
    IngredientInRecipeFrame* ingredientInRecipeFrame = nullptr;
    RecipeFrame* parent = nullptr;
    list<Ingredient>* ingredList = nullptr;
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
    wxMenu* menuOptions;
    wxMenuBar* menuBar;
    wxPanel* mainPanel = nullptr;
    wxPanel* namePanel = nullptr;
    wxPanel* quantityPanel = nullptr;
    wxPanel* unitsPanel = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxStaticText* quantityLabel = nullptr;
    wxStaticText* unitsLabel = nullptr;
    wxComboBox* nameComboBox = nullptr;
    wxTextCtrl* quantityText = nullptr;
    wxComboBox* unitsComboBox = nullptr;

    RecipeFrame* parent = nullptr;
    list<Ingredient>* ingredList = nullptr;
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
    void SetRecipe(Recipe& r, list<pair<string, int>>& tList, list<Ingredient>& iList);
    void SetRecipe(list<pair<string, int>>& tList, list<Ingredient>& iList);
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
    wxMenu* menuOptions;
    wxMenuBar* menuBar;
    wxScrolledWindow* mainPanel = nullptr;
    wxPanel* namePanel = nullptr;
    wxPanel* cuisineMealtypePanel = nullptr;
    wxPanel* servingsPanel = nullptr;
    wxPanel* yieldPanel = nullptr;
    wxPanel* descriptionPanel = nullptr;
    wxPanel* directionPanel = nullptr;
    wxPanel* ingredientsPanel = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxStaticText* cuisineLabel = nullptr;
    wxStaticText* mealtypeLabel = nullptr;
    wxStaticText* servingsLabel = nullptr;
    wxStaticText* yieldLabel = nullptr;
    wxStaticText* descriptionLabel = nullptr;
    wxStaticText* directionLabel = nullptr;
    wxStaticText* ingredientsLabel = nullptr;
    wxTextCtrl* nameText = nullptr;
    wxTextCtrl* cuisineText = nullptr;            // change to combobox?
    wxTextCtrl* mealtypeText = nullptr;
//    wxStaticText* mealtypeText = nullptr;
//    wxComboBox* mealtypeComboBox = nullptr;
    wxTextCtrl* servingsText = nullptr;
    wxTextCtrl* yieldText = nullptr;
    wxStaticText* yieldUnitCurrent = nullptr;
    wxComboBox* yieldUnitComboBox = nullptr;
    wxTextCtrl* descriptionText = nullptr;
    wxTextCtrl* directionText = nullptr;
    IngredientsInRecipeListCtrl* listIngredientsInRecipe = nullptr;

    Recipe newRecipe = Recipe();
    Recipe* currentRecipe = nullptr;
    MainListCtrl* parent = nullptr;
    AddIngredientToRecipeFrame* addIngredientToRecipe = nullptr;
    list<pair<string, int>>* typeList = nullptr;
    list<Ingredient>* ingredList = nullptr;
    wxDECLARE_NO_COPY_CLASS(RecipeFrame);
    wxDECLARE_EVENT_TABLE();
};


//*************************************************************************************************

// MealPlannerFrame class

//*************************************************************************************************

class MealPlannerFrame : public wxFrame
{
public:
    MealPlannerFrame();
    void SetParent(MainListCtrl* p);
    void RebuildCalendarView();
    void BuildMonthlyCalendarView();

protected:
    void OnExit(wxCloseEvent& e);

private:
    wxMenu* menuOptions = nullptr;
    wxMenu* menuView = nullptr;
    wxMenuBar* menuBar = nullptr;

    wxPanel* mainPanel = nullptr;

    wxPanel* rightPanel = nullptr;
    wxPanel* monthPanel = nullptr;
    wxTextCtrl* monthLabel = nullptr;
    wxPanel* calendarWeekDayHeaderPanel = nullptr;
    wxTextCtrl* sundayLabel = nullptr;
    wxTextCtrl* mondayLabel = nullptr;
    wxTextCtrl* tuesdayLabel = nullptr;
    wxTextCtrl* wednesdayLabel = nullptr;
    wxTextCtrl* thursdayLabel = nullptr;
    wxTextCtrl* fridayLabel = nullptr;
    wxTextCtrl* saturdayLabel = nullptr;
    wxPanel* calendarMonthlyDisplayPanel = nullptr;   // make wxScrolledWindow?

    wxPanel* leftPanel = nullptr;
    wxCalendarCtrl* sideCalendar = nullptr;

    MainListCtrl* parent = nullptr;

    long currentView;
    wxDateTime selectedDate;

    wxDECLARE_NO_COPY_CLASS(MealPlannerFrame);
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
//    void SaveCategories();
//    void SaveIngredients();
//    void SaveRecipes();
    void LoadLists();
    void AddNewCategory(string& c);
    void AddNewIngredient(string& name, string& desc, string& cat);
    void AddRecipe(Recipe& nr);
    void RemoveCategory();
    void RemoveIngredient();
    void RemoveRecipe();
    void CreateNewCategory();
    void CreateNewIngredient();
    void CreateNewRecipe();
    void GetCategoryNamesList(list<string>& names);
    string GetSelectedCategoryName();
    string GetSelectedIngredientName();
    string GetSelectedRecipeName();

    void GetIngredientsList(list<string>& list);

    void SetCurrentList(long c);
    long GetCurrentList();   

    void SetSelectedItem(string name);
    void ResetListView(long custFlags, long wxFlags = wxLC_REPORT, bool withText = true);
    void BuildRecipeListReportDisplay();
    void BuildIngredientListReportDisplay();
    void BuildCategoryListReportDisplay();
    void OpenPlanner();

protected:
    void OnActivated(wxListEvent& e);
    void OnSelected(wxListEvent& e);
    void OnColumnHeaderClick(wxListEvent& e);
private:
    // data.
    CategoryFrame* categoryFrame = nullptr;
    AddCategoryFrame* addCategoryFrame = nullptr;
    IngredientFrame* ingredientFrame = nullptr;
    AddIngredientFrame* addIngredientFrame = nullptr;
    RecipeFrame* recipeFrame = nullptr;
    MealPlannerFrame* mealPlannerFrame;
    list<Category> categories;
    list<Ingredient> ingredients;
    list<pair<string, int>> mealTypes;
    list<Recipe> recipes;

    // files storing list data.
    string categoryFile = "testCategoryFile.csv";
    string ingredFile = "testIngredientFile.csv";
    string recipeFile = "testRecipeFile.csv";

    long currentList = 0;       // tracker for which list we are currently viewing, used to open approrpiate windows to display details on the item selected

    Recipe* selectedRecipe = nullptr;
    Ingredient* selectedIngredient = nullptr;
    Category* selectedCategory = nullptr;
    wxListItem selectedItem;

    wxDECLARE_NO_COPY_CLASS(MainListCtrl);
    wxDECLARE_EVENT_TABLE();
};


//*************************************************************************************************

// ListMgrFrame class

//*************************************************************************************************

class ListMgrFrame: public wxFrame
{
public:
    ListMgrFrame(const wxString& title);
    void SetParent(RecipeApp* p);

protected:
    // file drop down menu
    void OnAbout(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);
    void OnChangeListReportDisplay(wxCommandEvent& e);

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

    // Meal Planner
    void OnOpenPlanner(wxCommandEvent& e);


private:
    wxPanel* panel = nullptr;
    wxMenu* menuFile = nullptr;
    wxMenu* menuList = nullptr;
    wxMenu* menuCalendar = nullptr;
    wxMenuBar* menuBar = nullptr;
    MainListCtrl* listController = nullptr;
    RecipeApp* parent = nullptr;


    wxDECLARE_NO_COPY_CLASS(ListMgrFrame);
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
    RECIPE_INGREDIENTS_LIST_CTRL,

    MEAL_PLANNER_DISPLAY,
    MEAL_PLANNER_CALENDAR_MONTHLY_VIEW,
    MEAL_PLANNER_CALENDAR_WEEKLY_VIEW,
    MEAL_PLANNER_CALENDAR_DAILY_VIEW,
    CALENDAR_SIDE_PANEL,

};

#endif // !RECIPEAPP_H
