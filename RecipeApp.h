#pragma once
#ifndef RECIPEAPP_H
#define RECIPEAPP_H

#include<wx/calctrl.h>
#include<wx/combo.h>
#include<wx/datectrl.h>
#include<wx/datetime.h>
#include<wx/grid.h>
#include<wx/listctrl.h>
#include<wx/scrolbar.h>
#include<wx/timectrl.h>
#include<wx/wxprec.h>

#include "MealList.h"

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
    void SetFieldsToBlank();
protected:
    void OnUpdate(wxCommandEvent& e);
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
    void SetCategoryComboBox(std::list<std::string> nms);
    void SetFieldsToBlank();
protected:
    void OnUpdate(wxCommandEvent& e);
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
    std::list<std::string> categoryNames;
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
    void SetIngredient(Ingredient& i);  
    void SetParent(MainListCtrl* p);
    void PassCategoryList(std::list<Category>& cat);  
    void SetCategoryComboBox();  
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
    std::list<Category>* catList = nullptr;
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
    void SetIngredientInRecipe(IngredientInRecipe& ir);
    void PassIngredientList_SetComboBoxes(std::list<Ingredient>& iList);
    void SetIngredientComboBox();
    void SetUnitComboBox();
    void SetFieldsToBlank();
    void RebuildTextFields();
    void SetParents(IngredientsInRecipeListCtrl* p);
protected:
    void OnUpdate(wxCommandEvent& e);
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
    std::list<Ingredient>* ingredList = nullptr;
    std::list<std::string> unitList;
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
    void SetIngredientsInRecipeList(std::list<IngredientInRecipe>& ingredInRecipe);
    void SetIngredientList(std::list<Ingredient>& iList);
    void SetSelectedItem(std::string name);
    void ResetListView(long wxFlags = wxLC_REPORT, bool withText = true);
    void BuildIngredientsInRecipeListReportDisplay();
    void UpdateIngredientInRecipe();
    std::string GetSelectedIngredient();
protected:
    void OnActivated(wxListEvent& e);
    void OnSelected(wxListEvent& e);
    void OnColumnHeaderClick(wxListEvent& e);
private:

    std::list<IngredientInRecipe>* ingredients = nullptr;
    IngredientInRecipe* selectedIngredient = nullptr;
    IngredientInRecipeFrame* ingredientInRecipeFrame = nullptr;
    RecipeFrame* parent = nullptr;
    std::list<Ingredient>* ingredList = nullptr;
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
    void PassIngredientList(std::list<Ingredient>& iList);
    void SetIngredientComboBox();
    void SetUnitComboBox();
protected:
    void OnUpdate(wxCommandEvent& e);
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
    std::list<Ingredient>* ingredList = nullptr;
    std::list<std::string> unitList;
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
    void SetRecipe();
    void SetRecipe(Recipe& r);
    void PassTypeList(std::list<std::pair< std::string, int > > & tList); 
    void PassIngredientList(std::list<Ingredient>& iList); 
    void SetUnitComboBox(); 
    void SetIngredientsInRecipeListCtrl();
    void RebuildTextFields();
    void SetParent(MainListCtrl* p);
    void UpdateIngredientInRecipe();
    void AddIngredientToRecipe(std::string& name, float& qty, std::string& unit);
protected:

    // edit drop down menu
    void OnUpdate(wxCommandEvent& e);
    void OnAddIngredient(wxCommandEvent& e);
    void OnRemoveIngredient(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);

private:
    bool isnew = false;
    wxMenu* menuOptions;
    wxMenuBar* menuBar;
    wxScrolledWindow* mainPanel = nullptr;
    wxPanel* namePanel = nullptr;
    wxPanel* cuisinerecipetypePanel = nullptr;
    wxPanel* servingsPanel = nullptr;
    wxPanel* yieldPanel = nullptr;
    wxPanel* descriptionPanel = nullptr;
    wxPanel* directionPanel = nullptr;
    wxPanel* ingredientsPanel = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxStaticText* cuisineLabel = nullptr;
    wxStaticText* recipetypeLabel = nullptr;
    wxStaticText* servingsLabel = nullptr;
    wxStaticText* yieldLabel = nullptr;
    wxStaticText* descriptionLabel = nullptr;
    wxStaticText* directionLabel = nullptr;
    wxStaticText* ingredientsLabel = nullptr;
    wxTextCtrl* nameText = nullptr;
    wxTextCtrl* cuisineText = nullptr;            // change to ComboBox?
    wxTextCtrl* recipetypeText = nullptr;
//    wxStaticText* recipetypeText = nullptr;
//    wxComboBox* recipetypeComboBox = nullptr;
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
    std::list<std::pair<std::string, int>>* typeList = nullptr;
    std::list<Ingredient>* ingredList = nullptr;
    wxDECLARE_NO_COPY_CLASS(RecipeFrame);
    wxDECLARE_EVENT_TABLE();
};

//*************************************************************************************************

// AddRecipeToMealFrame class

//*************************************************************************************************

class MealFrame;
class AddRecipeToMealFrame : public wxFrame
{
public:
    AddRecipeToMealFrame();
    void SetParent(MealFrame* p);
    void SetComboBox(std::list<Recipe>& recipes);

protected:
    void OnUpdate(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);

private:
    wxMenu* menuOptions = nullptr;
    wxPanel* mainPanel = nullptr;
    wxPanel* recipePanel = nullptr;
    wxStaticText* recipeText = nullptr;
    wxComboBox* recipeComboBox = nullptr;
    MealFrame* parent = nullptr;


    wxDECLARE_EVENT_TABLE();
    wxDECLARE_NO_COPY_CLASS(AddRecipeToMealFrame);
};

//*************************************************************************************************

// MealFrame class

//*************************************************************************************************

class MealPlannerFrame; // forward.
class MealFrame : public wxFrame
{
public:

    MealFrame(const wxDateTime& dt);
    void SetParent(MealPlannerFrame* p);
    void SetMeal(Meal& currentMeal);
    void SetMeal();
    void SetFrameTitle(wxString date, wxString nm, unsigned short id);
    void PassRecipes(std::list<Recipe>* lst);
    void ResetTextFields();
    void RebuildList();
    void AddRecipe(std::string name);

protected:
    void OnAddRecipe(wxCommandEvent& e);
    void OnUpdate(wxCommandEvent& e);
    void OnExit(wxCloseEvent& e);
private:

    wxMenu* menuOptions = nullptr;
    wxMenuBar* menuBar = nullptr;

    wxPanel* mainPanel = nullptr;
    wxPanel* namePanel = nullptr;
    wxPanel* scheduledPanel = nullptr;
    wxPanel* descriptionPanel = nullptr;
    wxPanel* numberOfServingsIsArchivedPanel = nullptr;
    wxPanel* recipesListCtrlPanel = nullptr;
    wxStaticText* nameLabel = nullptr;
    wxStaticText* dateLabel = nullptr;
    wxStaticText* timeLabel = nullptr;
    wxStaticText* descriptionLabel = nullptr;
    wxStaticText* numberOfServingsLabel = nullptr;
    wxStaticText* isArchivedLabel = nullptr;
    wxStaticText* recipesListLabel = nullptr;
    wxTextCtrl* nameText = nullptr;
    wxDatePickerCtrl* datePicker = nullptr;
    wxTimePickerCtrl* timePicker = nullptr;
    wxTextCtrl* descriptionText = nullptr;
    wxTextCtrl* numberOfServingsText = nullptr;
    wxTextCtrl* isArchivedText = nullptr;
    wxListCtrl* recipesListCtrl;

    AddRecipeToMealFrame* addRecipeToMealFrame = nullptr;
    MealPlannerFrame* parent = nullptr;
    Meal newMeal = Meal();
    Meal* currentMeal = nullptr;
    std::list<Recipe>* recipes;
    bool isnew = true;

    wxDECLARE_NO_COPY_CLASS(MealFrame);
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
    void SetMealList(std::list<Meal>* lst);
    void SetRecipeList(std::list<Recipe>* lst);
    void SetupSideCalendar();
    void SetupDailyHeader();
    void SetupDailyView();
    void SetupWeekDayHeader();
    void SetupMonthlyGrid();
    void ToggleMenuToCalendarDailyOptions();
    void RebuildCalendarView(); 
    void InitializeCalendarTableDaily();
    void InsertItemsInDailyListDisplay(Meal& m, int& i);
    void BuildDailyCalendarView();
    void BuildMonthlyCalendarView();
    void MealUpdated();
    void AddMealToList(std::string& nm, std::string& ds, wxDateTime& sch, int& noSer, bool& isArc, std::list<Recipe*>& reclist);
    void MoveMealInList(unsigned short id);

protected:
    void OnChangeDate(wxCalendarEvent& e);
    void OnAddMeal(wxCommandEvent& e);
    void OnEditMeal(wxCommandEvent& e);
    void OnActivated(wxListEvent& e);
    void OnSelected(wxListEvent& e);
    void OnExit(wxCloseEvent& e);

private:
    wxMenu* menuOptions = nullptr;
    wxMenu* menuView = nullptr;
    wxMenuBar* menuBar = nullptr;

    wxPanel* mainPanel = nullptr;

    // Right panel will display all of the daily/weekly/monthly details.
    wxPanel* rightPanel = nullptr;
    wxPanel* calendarDisplayPanel = nullptr;   // make wxScrolledWindow?

    // for monthly setup
    wxPanel* monthPanel = nullptr;              // monthly header
    wxTextCtrl* monthLabel = nullptr;           // for month header
    std::vector< std::vector<wxListBox*> > calendarTableMonthly;

    // for days of the week, to be used in weekly and monthly display.
    wxPanel* calendarWeekDayHeaderPanel = nullptr;
    wxTextCtrl* sundayLabel = nullptr;
    wxTextCtrl* mondayLabel = nullptr;
    wxTextCtrl* tuesdayLabel = nullptr;
    wxTextCtrl* wednesdayLabel = nullptr;
    wxTextCtrl* thursdayLabel = nullptr;
    wxTextCtrl* fridayLabel = nullptr;
    wxTextCtrl* saturdayLabel = nullptr;

    // for daily display.
    wxPanel* calendarDailyHeaderPanel = nullptr;
    wxPanel* headerPanel = nullptr;
    wxTextCtrl* headerLabel = nullptr;
    wxListCtrl* calendarTableDaily;

    // Left panel will be the mini calendar to the side.
    wxPanel* leftPanel = nullptr;
    wxCalendarCtrl* sideCalendar = nullptr;

    MainListCtrl* parent = nullptr;
    MealFrame* mealFrame = nullptr;

    long currentView;
    wxDateTime selectedDate;

    std::list<Meal>* meals;
    std::list<Recipe>* recipeList;
    Meal selectedMeal = Meal();

    wxDECLARE_NO_COPY_CLASS(MealPlannerFrame);
    wxDECLARE_EVENT_TABLE();
};


//*************************************************************************************************

// MainListCtrl class

//*************************************************************************************************

class ListMgrFrame;   // forward
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

    void SetParent(ListMgrFrame* p);
    void SaveAllLists();
    void SaveCategories();
    void SaveIngredients();
    void SaveRecipes();
    void SaveMeals();
    void LoadLists();
    void AddNewCategory(std::string& c);
    void AddNewIngredient(std::string& name, std::string& desc, std::string& cat);
    void AddNewRecipe(std::string& name, std::string& cuisine, std::string& description, std::string& direction, int& servingCount, int& yield, std::string& yieldUnit, std::string& recipetype, std::list<IngredientInRecipe>& ingredients);
    void RemoveCategory();
    void RemoveIngredient();
    void RemoveRecipe();
    void CreateNewCategory();
    void CreateNewIngredient();
    void CreateNewRecipe();
    std::string GetSelectedCategoryName();
    std::string GetSelectedIngredientName();
    std::string GetSelectedRecipeName();

    void SetCurrentList(long c);
    long GetCurrentList();   

    void SetSelectedItem(std::string name);
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
    ListMgrFrame* parent;
    // data.
    CategoryFrame* categoryFrame = nullptr;
    AddCategoryFrame* addCategoryFrame = nullptr;
    IngredientFrame* ingredientFrame = nullptr;
    AddIngredientFrame* addIngredientFrame = nullptr;
    RecipeFrame* recipeFrame = nullptr;
    MealPlannerFrame* mealPlannerFrame;

    // lists being managed.
    std::list<Category> categories;
    std::list<Ingredient> ingredients;
    std::list<std::pair<std::string, int>> recipetypes;
    std::list<Recipe> recipes;
    std::list<Meal> meals;

    // files storing list data.
    std::string categoryFile = "testCategoryFile.csv";
    std::string ingredFile = "testIngredientFile.csv";
    std::string recipeFile = "testRecipeFile.csv";
    std::string mealFile = "testMealFile.csv";

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
    void MessageSuccess(std::string msg);
    void MessageFailure(std::string msg);

protected:
    void SetRecipeListOptions();
    void SetIngredientListOptions();
    void SetCategoryListOptions();
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
    RECIPE_RECIPETYPE_TEXT_CTRL,
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
    MEAL_PLANNER_CALENDAR_DAY,
    MEAL_PLANNER_CALENDAR_MONTHLY_VIEW,
    MEAL_PLANNER_CALENDAR_WEEKLY_VIEW,
    MEAL_PLANNER_CALENDAR_DAILY_VIEW,
    MEAL_PLANNER_ADD_MEAL,
    MEAL_PLANNER_EDIT_MEAL,
    MEAL_PLANNER_CHANGE_DATE,
    MEAL_NAME_TEXT_CTRL,
    MEAL_DATE_PICKER,
    MEAL_TIME_PICKER,
    MEAL_DESCRIPTION_TEXT_CTRL,
    MEAL_NO_OF_SERVINGS,
    MEAL_RECIPE_LIST_CTRL,
    MEAL_ADD_RECIPE,
    MEAL_RECIPE_COMBO_BOX,
    MEAL_UPDATE,
    CALENDAR_SIDE_PANEL,

};

#endif // !RECIPEAPP_H
