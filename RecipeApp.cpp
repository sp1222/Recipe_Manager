#include "RecipeApp.h"

//*************************************************************************************************

// RecipeApp definition

//*************************************************************************************************

wxIMPLEMENT_APP(RecipeApp);
bool RecipeApp::OnInit()
{
    MainFrame* Main = new MainFrame(_("Recipe Manager App"));
    Main->Show(true);
    SetTopWindow(Main);
    return true;
}


//*************************************************************************************************

// RecipeFrame definition

//*************************************************************************************************

RecipeFrame::RecipeFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 500))
{
    // need to get currentRecipe here.

    // Menu Bar
    // File menu 
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ABOUT, "&About\tAlt-A");
    menuFile->AppendSeparator();
    menuFile->Append(EXIT, "&Quit\tAlt-Q");

    // Define menu bar
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    panel = new wxPanel(this, wxID_ANY);

    // display recipe information here.
    // void DisplayRecipe();

    wxBoxSizer* const sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(this, wxSizerFlags(2).Expand().Border());
    panel->SetSizer(sizer);

    SetClientSize(panel->GetMaxSize());
}




//*************************************************************************************************

// MainListCtrl Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(MainListCtrl, wxListCtrl)
    EVT_LIST_ITEM_ACTIVATED(LIST_CTRL, MainListCtrl::OnActivated)
    EVT_LIST_ITEM_SELECTED(LIST_CTRL, MainListCtrl::OnSelected)
    EVT_LIST_COL_CLICK(LIST_CTRL, MainListCtrl::OnColumnHeaderClick)
wxEND_EVENT_TABLE()

//*************************************************************************************************

// MainListCtrl definition

//*************************************************************************************************


//*************************************************************************************************

// MainListCtrl function definitions

//*************************************************************************************************

void MainListCtrl::InsertItemsInRecipeListReportDisplay(Recipe& r, int& i)
{
    wxString str;
    str = wxString(r.getName());
    long temp = InsertItem(i, str);
    SetItemData(temp, i);

    str = wxString(r.getMealType());
    SetItem(temp, 1, str);

    str = wxString(to_string(r.getServingCount()));
    SetItem(temp, 2, str);
}

void MainListCtrl::InsertItemsInIngredientListReportDisplay(Ingredient& n, int& i)
{
    wxString str;
    str = wxString(n.getName());
    long temp = InsertItem(i, str);
    SetItemData(temp, i);

    str = wxString(n.getCategoryStr());
    SetItem(temp, 1, str);

    str = wxString(to_string(n.getRecipesUsingIngredientCount()));
    SetItem(temp, 2, str);
}

void MainListCtrl::InsertItemsInCategoryListReportDisplay(Category& c, int& i)
{
    wxString str;
    str = wxString(c.getCategory());
    long temp = InsertItem(i, str);
    SetItemData(temp, i);

    str = wxString(to_string(c.getIngredientsUsingCategoryCount()));
    SetItem(temp, 1, str);
}

void MainListCtrl::LoadLists()
{
    // load lists.
    loadCategoryList(catFile, categories);
    loadIngredientList(ingredFile, ingredients, categories);
    loadRecipeList(recipeFile, recipes, ingredients, mealTypes);
}

list<Recipe> MainListCtrl::GetRecipes()
{
    return recipes;
}

list<Ingredient> MainListCtrl::GetIngredients()
{
    return ingredients;
}

list<Category> MainListCtrl::GetCategories()
{
    return categories;
}

void MainListCtrl::SetCurrentList(long c)
{
    currentList = c;
}

long MainListCtrl::GetCurrentList()
{
    return currentList;
}

void MainListCtrl::SetSelectedItem(string name)
{
    switch (GetCurrentList())
    {
    case RECIPE_LIST_REPORT_DISPLAY:
        selectedRecipe = &getRecipeInList(name, recipes);
        break;
    case INGREDIENT_LIST_REPORT_DISPLAY:
        selectedIngredient = &getIngredientInList(name, ingredients);
        break;
    case CATEGORY_LIST_REPORT_DISPLAY:
        selectedCategory = &getCategoryInList(name, categories);
        break;

    default:
        wxFAIL_MSG("Currently not in an updatable list.");
        break;
    }
}

void MainListCtrl::OnActivated(wxListEvent& e)
{
    // here we open a window to the activated item, depending on the currentList we are in.
    switch (GetCurrentList())
    {
    case RECIPE_LIST_REPORT_DISPLAY:
        // here we open a recipe Frame, make it the primary window, and populate fields with the recipe we have clicked on.
        // use GetSelectedItem to get the name of the recipe being displayed in RecipeFrame

//        recipeFrame = new RecipeFrame(selectedRecipe->getName());
//        recipeFrame->Show(true);
                                                   
        break;
    case INGREDIENT_LIST_REPORT_DISPLAY:
        // here we open an ingredient Frame, make it the primary window, and populate fields with the ingredient information we have clicked on.
        break;
    case CATEGORY_LIST_REPORT_DISPLAY:
        // here we open a category Frame, make it the primary window, and populate fields with the category we have clicked on.
        break;
    default:
        wxFAIL_MSG("Currently not in an updatable list.");
        break;
    }
}

void MainListCtrl::OnSelected(wxListEvent& e)
{
    wxListItem info;
    info.m_itemId = e.m_itemIndex;  // getting the index of the selected item.
    info.m_col = 0;                 // get the first column information, or the name of the recipe/ingredient/category
                                    // designed to be unduplicated values and to not be reliant on indexing when lists are sorted.
    info.m_mask = wxLIST_MASK_TEXT;
    if (GetItem(info))
    {
        SetSelectedItem(string(info.m_text));
    }
    else
        wxFAIL_MSG("wxListCtrl::GetItem() failed");
}

void MainListCtrl::OnColumnHeaderClick(wxListEvent& e)
{
    // this is where we sort the lists by the column clicked.
    // first, we need to determine which list we are sorting.
    int col = e.GetColumn();

    switch (GetCurrentList())
    {
        // if current list is recipes
    case RECIPE_LIST_REPORT_DISPLAY:
        sortRecipes(col, recipes);
        ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
        break;
        // if current list is ingredients
    case INGREDIENT_LIST_REPORT_DISPLAY:
        sortIngredients(col, ingredients);
        ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
        break;
        // if current list is categories
    case CATEGORY_LIST_REPORT_DISPLAY:
        sortCategories(col, categories);
        ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
        break;
    default:
        wxMessageDialog d(this, "List to sort does not exist!", "Sort Error");
        break;
    }
}

void MainListCtrl::ResetListView(long custFlags, long wxFlags, bool withText)
{
#if 0
    if (!this || ((flags & wxLC_VIRTUAL) 1 = (this->GetWindowStyleFlag() & wxLC_VIRTUAL)))
#endif
    Hide();
    ClearAll();
    SetSingleStyle(wxFlags | wxLC_SINGLE_SEL);
    switch (wxFlags & wxLC_MASK_TYPE)
    {
    case wxLC_REPORT:
        switch (custFlags)
        {
        case RECIPE_LIST_REPORT_DISPLAY:
            BuildRecipeListReportDisplay();
            break;
        case INGREDIENT_LIST_REPORT_DISPLAY:
            BuildIngredientListReportDisplay();
            break;
        case CATEGORY_LIST_REPORT_DISPLAY:
            BuildCategoryListReportDisplay();
            break;
        default:
            wxFAIL_MSG("Unknown Display Request");
            break;
        }
        break;
    default:
        wxFAIL_MSG("Unknown wxLC_STYLE Request");
        break;
    }
    Show();
}

void MainListCtrl::BuildRecipeListReportDisplay()
{
    wxListItem col;
    col.SetText("Recipe Name");
    col.SetImage(-1);
    InsertColumn(0, col);

    col.SetText("Meal Type");
    InsertColumn(1, col);

    col.SetText("Servings");
    InsertColumn(2, col);

    // populate the list with the recipe information.
    int i = -1;
    for (auto& recipe : recipes)
    {
        i++;
        InsertItemsInRecipeListReportDisplay(recipe, i);
    }

    SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
    SetCurrentList(RECIPE_LIST_REPORT_DISPLAY);
}


void MainListCtrl::BuildIngredientListReportDisplay()
{
    wxListItem col;
    col.SetText("Ingredient Name");
    col.SetImage(-1);
    InsertColumn(0, col);

    col.SetText("Ingredient Type");
    InsertColumn(1, col);

    col.SetText("Recipe Count");
    InsertColumn(2, col);

    // populate the list with the recipe information.
    int i = -1;
    for (auto& ingredient : ingredients)
    {
        i++;
        InsertItemsInIngredientListReportDisplay(ingredient, i);

    }

    SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
    SetCurrentList(INGREDIENT_LIST_REPORT_DISPLAY);
}

void MainListCtrl::BuildCategoryListReportDisplay()
{
    wxListItem col;
    col.SetText("Category");
    col.SetImage(-1);
    InsertColumn(0, col);

    col.SetText("Ingredient Count");
    InsertColumn(1, col);

    // populate the list with the recipe information.
    int i = -1;
    for (auto& category : categories)
    {
        i++;
        InsertItemsInCategoryListReportDisplay(category, i);

    }
    SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    SetCurrentList(CATEGORY_LIST_REPORT_DISPLAY);
}

//*************************************************************************************************

// MainFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ABOUT, MainFrame::OnAbout)
    EVT_MENU(EXIT, MainFrame::OnExit)

    EVT_MENU(RECIPE_LIST_REPORT_DISPLAY, MainFrame::OnRecipeListReportDisplay)
    EVT_MENU(INGREDIENT_LIST_REPORT_DISPLAY, MainFrame::OnIngredientListReportDisplay)
    EVT_MENU(CATEGORY_LIST_REPORT_DISPLAY, MainFrame::OnCategoryListReportDisplay)

//    EVT_MENU(LIST_TOGGLE_BELL, MainFrame::OnToggleBell)
//    EVT_MENU(LIST_ROW_LINES, MainFrame::OnSetRowLines)



//    EVT_UPDATE_UI(LIST_ROW_LINES, MainFrame::OnUpdateRowLines)
wxEND_EVENT_TABLE()

//*************************************************************************************************

// MainFrame definition

//*************************************************************************************************

MainFrame::MainFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 500))
{

    // Menu Bar
    // File menu
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ABOUT, "&About\tAlt-A");
    menuFile->AppendSeparator();
    menuFile->Append(EXIT, "&Quit\tAlt-Q");

    // List menu
    wxMenu* menuList = new wxMenu;
    menuList->Append(RECIPE_LIST_REPORT_DISPLAY, "Display &Recipe List\tAlt-R");
    menuList->Append(INGREDIENT_LIST_REPORT_DISPLAY, "Display &Ingredient List\tAlt-I");
    menuList->Append(CATEGORY_LIST_REPORT_DISPLAY, "Display &Category List\tAlt-C");
    menuList->AppendSeparator();

    // Define menu bar
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuList, "&Lists");
    SetMenuBar(menuBar);

    panel = new wxPanel(this, wxID_ANY);

    // default startup of list display to 
    listController = new MainListCtrl(panel, LIST_CTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxBORDER_THEME | wxLC_SINGLE_SEL);
    listController->LoadLists();
    listController->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);

    wxBoxSizer* const sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(listController, wxSizerFlags(2).Expand().Border());
    panel->SetSizer(sizer);

    SetClientSize(panel->GetBestSize());
}

//*************************************************************************************************

// MainFrame function definitions

//*************************************************************************************************

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(e))
{
    wxMessageDialog dialog(this, "Recipe Manager System\nStephen Polozoff (c) 2021", "About Recipe Manager");
    dialog.ShowModal();
}

void MainFrame::OnExit(wxCommandEvent& WXUNUSED(e))
{
    Close(TRUE);
}

void MainFrame::OnRecipeListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the recipe list.
    listController->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
}

void MainFrame::OnIngredientListReportDisplay(wxCommandEvent& e)
{
    // here we clear the current listController and display the ingredient list.
    listController->ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
}

void MainFrame::OnCategoryListReportDisplay(wxCommandEvent& e)
{
    // here we clear the current listController and display the category list.
    listController->ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
}