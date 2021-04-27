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

// AddCategoryFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(AddCategoryFrame, wxFrame)
EVT_MENU(FINALIZE, AddCategoryFrame::OnFinalize)
EVT_MENU(EXIT, AddCategoryFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// AddCategoryFrame definition

//*************************************************************************************************

AddCategoryFrame::AddCategoryFrame() : wxFrame(NULL, wxID_ANY, wxString("New Category"), wxDefaultPosition, wxSize(400, 300))
{
    // need to get currentRecipe here.

    // Menu Bar
    // File menu
    wxMenu* menuOptions = new wxMenu;
    menuOptions->Append(FINALIZE, "&Add Category\tAlt-A");
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "&Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);
    
    namePanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Category Name:"), wxDefaultPosition, wxSize(100, 20));
    nameText = new wxTextCtrl(namePanel, CATEGORY_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);

    SetClientSize(mainPanel->GetMaxSize());
}


//*************************************************************************************************

// AddCategoryFrame function definition

//*************************************************************************************************

void AddCategoryFrame::SetParent(MainFrame* p)
{
    parent = p;
}

void AddCategoryFrame::OnFinalize(wxCommandEvent& WXUNUSED(e))
{
    string val = string(nameText->GetValue());
    parent->AddCategory(val);
}

void AddCategoryFrame::OnExit(wxCommandEvent& WXUNUSED(e))
{
    //    parent->SaveAllLists();
    Close(TRUE);
}


//*************************************************************************************************

// CategoryFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(CategoryFrame, wxFrame)
//    EVT_MENU(UPDATE, CategoryFrame::OnUpdateRecipe)
EVT_MENU(EXIT, CategoryFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// CategoryFrame definition

//*************************************************************************************************

CategoryFrame::CategoryFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 200))
{
    // need to get currentRecipe here.

    // Menu Bar
    // File menu
    wxMenu* menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "&Update\tAlt-U");
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "&Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);

    namePanel = new wxPanel(mainPanel, wxID_ANY);
    ingredientCountPanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Category Name:"), wxDefaultPosition, wxSize(200, 20));
    nameText = new wxStaticText(namePanel, CATEGORY_NAME_TEXT_CTRL, wxString(currentCategory->getCategory()), wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    ingredientCountLabel = new wxStaticText(ingredientCountPanel, LABEL, wxString("Ingredients in Category Count:"), wxDefaultPosition, wxSize(200, 20));
    ingredientCountDisplay = new wxStaticText(ingredientCountPanel, CATEGORY_INGREDIENT_COUNT_TEXT_CTRL, wxString(to_string(currentCategory->getIngredientsUsingCategoryCount())), wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* const ingredientCountSizer = new wxBoxSizer(wxHORIZONTAL);
    ingredientCountSizer->Add(ingredientCountLabel, wxSizerFlags().Expand().Border(wxALL));
    ingredientCountSizer->Add(ingredientCountDisplay, wxSizerFlags().Expand().Border(wxALL));
    ingredientCountPanel->SetSizer(ingredientCountSizer);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(ingredientCountPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);

    SetClientSize(mainPanel->GetMaxSize());
}


//*************************************************************************************************

// CategoryFrame function definition

//*************************************************************************************************

void CategoryFrame::SetCategory(Category& c)
{
    currentCategory = &c;
}


void CategoryFrame::RebuildTextFields()
{
    nameText->SetLabel(currentCategory->getCategory());
    ingredientCountDisplay->SetLabel(wxString(to_string(currentCategory->getIngredientsUsingCategoryCount())));
}


void CategoryFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}

/*
void CategoryFrame::OnUpdateRecipe(wxCommandEvent& WXUNUSED(e))
{
    string val = string(nameText->GetValue());
    currentCategory->setCategoryName(val);
    val = string(mealtypeText->GetValue());
    currentCategory->setMealType(val, *typeList);
    val = string(descriptionText->GetValue());
    currentCategory->setDescription(val);
    val = string(directionText->GetValue());
    currentCategory->setDirection(val);
    parent->SaveAllLists();
}
*/

void CategoryFrame::OnExit(wxCommandEvent& WXUNUSED(e))
{
    //    parent->SaveAllLists();
    Close(TRUE);
}


//*************************************************************************************************

// IngredientFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(IngredientFrame, wxFrame)
EVT_MENU(UPDATE, IngredientFrame::OnUpdate)
EVT_MENU(EXIT, IngredientFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// IngredientFrame definition

//*************************************************************************************************

IngredientFrame::IngredientFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    // need to get currentRecipe here.

    // Menu Bar
    // File menu
    wxMenu* menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "&Update\tAlt-U");
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "&Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);

    namePanel = new wxPanel(mainPanel, wxID_ANY);
    descriptionPanel = new wxPanel(mainPanel, wxID_ANY);
    categoryPanel = new wxPanel(mainPanel, wxID_ANY);
    recipeUsingIngredientCountPanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Category Name:"), wxDefaultPosition, wxSize(200, 20));
    nameText = new wxTextCtrl(namePanel, INGREDIENT_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    descriptionLabel = new wxStaticText(descriptionPanel, LABEL, wxString("Ingredients in Category Count:"), wxDefaultPosition, wxSize(200, 20));
    descriptionText = new wxTextCtrl(descriptionPanel, INGREDIENT_DESCRIPTION_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    descriptionSizer->Add(descriptionLabel, wxSizerFlags().Expand().Border(wxALL));
    descriptionSizer->Add(descriptionText, wxSizerFlags().Expand().Border(wxALL));
    descriptionPanel->SetSizer(descriptionSizer);

    categoryLabel = new wxStaticText(categoryPanel, LABEL, wxString("Ingredients in Category Count:"), wxDefaultPosition, wxSize(200, 20));
    categoryComboBox = new wxComboBox(categoryPanel, INGREDIENT_CATEGORY_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* const categorySizer = new wxBoxSizer(wxHORIZONTAL);
    categorySizer->Add(categoryLabel, wxSizerFlags().Expand().Border(wxALL));
    categorySizer->Add(categoryComboBox, wxSizerFlags().Expand().Border(wxALL));
    categoryPanel->SetSizer(categorySizer);

    recipeUsingIngredientCountLabel = new wxStaticText(recipeUsingIngredientCountPanel, LABEL, wxString("Ingredients in Category Count:"), wxDefaultPosition, wxSize(200, 20));
    recipeUsingIngredientCountText = new wxStaticText(recipeUsingIngredientCountPanel, INGREDIENT_RECIPES_COUNT_TEXT_CTRL, wxString(to_string(currentIngredient->getRecipesUsingIngredientCount())), wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const recipeCountSizer = new wxBoxSizer(wxHORIZONTAL);
    recipeCountSizer->Add(recipeUsingIngredientCountLabel, wxSizerFlags().Expand().Border(wxALL));
    recipeCountSizer->Add(recipeUsingIngredientCountText, wxSizerFlags().Expand().Border(wxALL));
    recipeUsingIngredientCountPanel->SetSizer(recipeCountSizer);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(descriptionPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(categoryPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(recipeUsingIngredientCountPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);

    SetClientSize(mainPanel->GetMaxSize());
}


//*************************************************************************************************

// IngredientFrame function definition

//*************************************************************************************************

void IngredientFrame::SetIngredient(Ingredient& i)
{
    currentIngredient = &i;
}

void IngredientFrame::SetCategoryList(list<Category>& c, const wxString cstr[], const int size)
{
    catList = &c;
    categoryComboBox = new wxComboBox(categoryPanel, INGREDIENT_CATEGORY_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20), size, cstr);
}


void IngredientFrame::RebuildTextFields()
{
    nameText->SetValue(currentIngredient->getName());
    descriptionText->SetValue(currentIngredient->getDescription());
//    categoryText->SetValue(currentIngredient->getCategoryStr());
    recipeUsingIngredientCountText->SetLabel(to_string(currentIngredient->getRecipesUsingIngredientCount()));
}


void IngredientFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}


void IngredientFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string val = string(nameText->GetValue());
    currentIngredient->setName(val);
    val = string(descriptionText->GetValue());
    currentIngredient->setDescription(val);
//    val = string(categoryText->GetValue());
    currentIngredient->setCategory(getCategoryInList(val, *catList));
    parent->SaveAllLists();
    parent->ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
}


void IngredientFrame::OnExit(wxCommandEvent& WXUNUSED(e))
{
    //    parent->SaveAllLists();
    Close(TRUE);
}


//*************************************************************************************************

// IngredientsInRecipeListCtrl Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(IngredientsInRecipeListCtrl, wxListCtrl)
    EVT_LIST_ITEM_ACTIVATED(RECIPE_INGREDIENTS_LIST_CTRL, IngredientsInRecipeListCtrl::OnActivated)
    EVT_LIST_ITEM_SELECTED(RECIPE_INGREDIENTS_LIST_CTRL, IngredientsInRecipeListCtrl::OnSelected)
    EVT_LIST_COL_CLICK(RECIPE_INGREDIENTS_LIST_CTRL, IngredientsInRecipeListCtrl::OnColumnHeaderClick)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// IngredientsInRecipeListCtrl definition

//*************************************************************************************************


//*************************************************************************************************

// IngredientsInRecipeListCtrl function definitions

//*************************************************************************************************
void IngredientsInRecipeListCtrl::InsertIngredientsInRecipeListReportDisplay()
{

}

void IngredientsInRecipeListCtrl::SetIngredientsInRecipeList(list<IngredientInRecipe>& list)
{
    ingredients = &list;
}

void IngredientsInRecipeListCtrl::SetSelectedItem(string name)
{
 //   selectedIngredient = getIngredientInRecipe(name);
}

void IngredientsInRecipeListCtrl::OnActivated(wxListEvent& e)
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

}

void IngredientsInRecipeListCtrl::OnSelected(wxListEvent& e)
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

void IngredientsInRecipeListCtrl::OnColumnHeaderClick(wxListEvent& e)
{
    // this is where we sort the lists by the column clicked.
    // first, we need to determine which list we are sorting.
    int col = e.GetColumn();

}

void IngredientsInRecipeListCtrl::ResetListView(long wxFlags, bool withText)
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

        break;
    default:
        wxFAIL_MSG("Unknown wxLC_STYLE Request");
        break;
    }
    Show();
}
/*
void IngredientsInRecipeListCtrl::BuildIngredientsInListReportDisplay()
{
    wxListItem col;
    col.SetText("Ingredient Name");
    col.SetImage(-1);
    InsertColumn(0, col);

    col.SetText("Quantity");
    InsertColumn(1, col);

    col.SetText("Units");
    InsertColumn(2, col);

    // populate the list with the recipe information.
    int i = -1;
    for (auto& ingred : ingredients)
    {
        i++;
        InsertIngredientsInRecipeListReportDisplay(ingred, i);
    }

    SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
}
*/

//*************************************************************************************************

// RecipeFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(RecipeFrame, wxFrame)
    EVT_MENU(UPDATE, RecipeFrame::OnUpdateRecipe)
    EVT_MENU(EXIT, RecipeFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// RecipeFrame definition

//*************************************************************************************************

RecipeFrame::RecipeFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 800))
{
    // need to get currentRecipe here.

    // Menu Bar
    // File menu
    wxMenu* menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "&Update\tAlt-A");
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "&Options");
    SetMenuBar(menuBar);


    mainPanel = new wxPanel(this, wxID_ANY);
    
    namePanel = new wxPanel(mainPanel, wxID_ANY);
    mealTypePanel = new wxPanel(mainPanel, wxID_ANY);
    descriptionPanel = new wxPanel(mainPanel, wxID_ANY);
    directionPanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Recipe Name:"), wxDefaultPosition, wxSize(100, 20));
    nameText = new wxTextCtrl(namePanel, RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);


    mealtypeLabel = new wxStaticText(mealTypePanel, LABEL, wxString("Meal Type:"), wxDefaultPosition, wxSize(100, 20));
    mealtypeText = new wxTextCtrl(mealTypePanel, RECIPE_MEALTYPE_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 20));

    wxBoxSizer* const mealtypeSizer = new wxBoxSizer(wxHORIZONTAL);
    mealtypeSizer->Add(mealtypeLabel, wxSizerFlags().Expand().Border(wxALL));
    mealtypeSizer->Add(mealtypeText, wxSizerFlags().Expand().Border(wxALL));
    mealTypePanel->SetSizer(mealtypeSizer);


    descriptionLabel = new wxStaticText(descriptionPanel, LABEL, wxString("Description:"), wxDefaultPosition, wxSize(100, 20));
    descriptionText = new wxTextCtrl(descriptionPanel, RECIPE_DESCRIPTION_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 100));

    wxBoxSizer* const descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    descriptionSizer->Add(descriptionLabel, wxSizerFlags().Expand().Border(wxALL));
    descriptionSizer->Add(descriptionText, wxSizerFlags().Expand().Border(wxALL));
    descriptionPanel->SetSizer(descriptionSizer);


    directionLabel = new wxStaticText(directionPanel, LABEL, wxString("Directions:"), wxDefaultPosition, wxSize(100, 20));
    directionText = new wxTextCtrl(directionPanel, RECIPE_DIRECTIONS_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 300));

    wxBoxSizer* const directionSizer = new wxBoxSizer(wxHORIZONTAL);
    directionSizer->Add(directionLabel, wxSizerFlags().Expand().Border(wxALL));
    directionSizer->Add(directionText, wxSizerFlags().Expand().Border(wxALL));
    directionPanel->SetSizer(directionSizer);

    listIngredientsInRecipe = new IngredientsInRecipeListCtrl(mainPanel, RECIPE_INGREDIENTS_LIST_CTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxBORDER_THEME | wxLC_SINGLE_SEL);
    listIngredientsInRecipe->SetIngredientsInRecipeList(currentRecipe->getAllIngredientsInRecipe());
    listIngredientsInRecipe->ResetListView(wxLC_REPORT);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(mealTypePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(descriptionPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(directionPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(listIngredientsInRecipe, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);


    SetClientSize(mainPanel->GetMaxSize());
}

//*************************************************************************************************

// RecipeFrame function definition

//*************************************************************************************************

void RecipeFrame::SetRecipe(Recipe& r, list<pair<string, int>>& tList)
{
    currentRecipe = &r;
    typeList = &tList;
}

void RecipeFrame::RebuildTextFields()
{
    nameText->SetValue(currentRecipe->getName());
    mealtypeText->SetValue(currentRecipe->getMealType());
    descriptionText->SetValue(currentRecipe->getDescription());
    directionText->SetValue(currentRecipe->getDirection());
}

void RecipeFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}

void RecipeFrame::OnUpdateRecipe(wxCommandEvent& WXUNUSED(e))
{
    string val = string(nameText->GetValue());
    currentRecipe->setName(val);
    val = string(mealtypeText->GetValue());
    currentRecipe->setMealType(val, *typeList);
    val = string(descriptionText->GetValue());
    currentRecipe->setDescription(val);
    val = string(directionText->GetValue());
    currentRecipe->setDirection(val);
    parent->SaveRecipes();
    parent->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
}

void RecipeFrame::OnExit(wxCommandEvent& WXUNUSED(e))
{
    parent->SaveRecipes();
    Close(TRUE);
}

//*************************************************************************************************

// MainListCtrl Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(MainListCtrl, wxListCtrl)
    EVT_LIST_ITEM_ACTIVATED(MAIN_LIST_CTRL, MainListCtrl::OnActivated)
    EVT_LIST_ITEM_SELECTED(MAIN_LIST_CTRL, MainListCtrl::OnSelected)
    EVT_LIST_COL_CLICK(MAIN_LIST_CTRL, MainListCtrl::OnColumnHeaderClick)
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

void MainListCtrl::SaveAllLists()
{
    saveCategoryList(categoryFile, categories);
    saveIngredientList(ingredFile, ingredients);
    saveRecipeList(recipeFile, recipes);

}

void MainListCtrl::SaveCategories()
{
    saveCategoryList(categoryFile, categories);
}

void MainListCtrl::SaveIngredients()
{
    saveIngredientList(ingredFile, ingredients);
}

void MainListCtrl::SaveRecipes()
{
    saveRecipeList(recipeFile, recipes);
}

void MainListCtrl::LoadLists()
{
    // load lists.
    loadCategoryList(categoryFile, categories);
    loadIngredientList(ingredFile, ingredients, categories);
    loadRecipeList(recipeFile, recipes, ingredients, mealTypes);
}

void MainListCtrl::AddNewCategory(string& c)
{
    if (addCategory(c, categories))
    {
        SaveCategories();
        ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

void MainListCtrl::RemoveCategory()
{
    string cat = selectedCategory->getCategory();
    if (removeCategory(cat, categories))
    {
        SaveCategories();
        ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

string MainListCtrl::GetSelectedCategoryName()
{
    if (selectedCategory != nullptr)
        return selectedCategory->getCategory();
    else
        return "";
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
    wxListItem info;
    info.m_itemId = e.m_itemIndex;  // getting the index of the selected item.
    info.m_col = 0;                 // get the first column information, or the name of the recipe/ingredient/category
                                    // designed to be unduplicated values and to not be reliant on indexing when lists are sorted.
                                    // 
    // NOTE LATEST 4.26.21: lists in the backend will be sorted and reflect the displayed list
    // thus, it is now safe to use indices to reference an item in the list.
    // this is to make the project more efficient!

    selectedItem = info;

    info.m_mask = wxLIST_MASK_TEXT;
    if (GetItem(info))
    {
        SetSelectedItem(string(info.m_text));
    }

    const int sz = 100;
    wxString catStringList[sz];
    auto c_iter = categories.begin();

    // here we open a window to the activated item, depending on the currentList we are in.
    switch (GetCurrentList())
    {
    case RECIPE_LIST_REPORT_DISPLAY:
        // here we open a recipe Frame, make it the primary window, and populate fields with the recipe we have clicked on.

        recipeFrame = new RecipeFrame(selectedRecipe->getName());
        recipeFrame->SetRecipe(*selectedRecipe, mealTypes);
        recipeFrame->SetParent(this);
        recipeFrame->RebuildTextFields();
        recipeFrame->Show(true);

        break;
    case INGREDIENT_LIST_REPORT_DISPLAY:
        // here we open an ingredient Frame, make it the primary window, and populate fields with the ingredient information we have clicked on.

        ingredientFrame = new IngredientFrame(selectedIngredient->getName());
        ingredientFrame->SetIngredient(*selectedIngredient);
        for (int i = 0; i < categories.size(); i++)
            *(catStringList + i) = wxString(c_iter->getCategory());
        ingredientFrame->SetCategoryList(categories, catStringList, sz);
        ingredientFrame->SetParent(this);
        ingredientFrame->RebuildTextFields();
        ingredientFrame->Show(true);

        break;
    case CATEGORY_LIST_REPORT_DISPLAY:
        // here we open a category Frame, make it the primary window, and populate fields with the category we have clicked on.

        categoryFrame = new CategoryFrame(selectedCategory->getCategory());
        categoryFrame->SetCategory(*selectedCategory);
        categoryFrame->SetParent(this);
        categoryFrame->RebuildTextFields();
        categoryFrame->Show(true);

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

    EVT_MENU(CATEGORY_ADD_NEW, MainFrame::OnAddCategory)
    EVT_MENU(CATEGORY_REMOVE_SELECTED, MainFrame::OnRemoveCategory)

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
    menuFile = new wxMenu;
    menuFile->Append(ABOUT, "&About\tAlt-A");
    menuFile->AppendSeparator();
    menuFile->Append(EXIT, "&Quit\tAlt-Q");

    // List menu
    menuList = new wxMenu;
    menuList->Append(RECIPE_LIST_REPORT_DISPLAY, "Display &Recipe List\tAlt-R");
    menuList->Append(INGREDIENT_LIST_REPORT_DISPLAY, "Display &Ingredient List\tAlt-I");
    menuList->Append(CATEGORY_LIST_REPORT_DISPLAY, "Display &Category List\tAlt-C");
    menuList->AppendSeparator();

    // Category List Editor menu
    menuCategoryListEditor = new wxMenu;
    menuCategoryListEditor->Append(CATEGORY_ADD_NEW, "Create Category");
    menuCategoryListEditor->Append(CATEGORY_REMOVE_SELECTED, "Remove Selected Category");
     
    // Ingredient List Editor menu
    menuIngredientListEditor = new wxMenu;
    menuIngredientListEditor->Append(INGREDIENT_ADD_NEW, "Create Ingredient");
    menuIngredientListEditor->Append(INGREDIENT_REMOVE_SELECTED, "Remove Selected Ingredient");
     
    
    // Recipe List Editor menu
    menuRecipeListEditor = new wxMenu;
    menuRecipeListEditor->Append(RECIPE_ADD_NEW, "Create Recipe");
    menuRecipeListEditor->Append(RECIPE_REMOVE_SELECTED, "Remove Selected Recipe");



    // Define menu bar
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuList, "&Lists");
    menuBar->Append(menuRecipeListEditor, "Recipe List Options");
    SetMenuBar(menuBar);

    panel = new wxPanel(this, wxID_ANY);

    // default startup of list display to 
    listController = new MainListCtrl(panel, MAIN_LIST_CTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxBORDER_THEME | wxLC_SINGLE_SEL);
    listController->LoadLists();
    listController->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);

    wxBoxSizer* const sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(listController, wxSizerFlags(2).Expand().Border(wxALL, 10));
    panel->SetSizer(sizer);

    SetClientSize(panel->GetBestSize());
}

//*************************************************************************************************

// MainFrame function definitions

//*************************************************************************************************

void MainFrame::AddCategory(string& c)
{
    listController->AddNewCategory(c);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(e))
{
    wxMessageDialog dialog(this, "Recipe Manager System\nStephen Polozoff (c) 2021", "About Recipe Manager");
    dialog.ShowModal();
}

void MainFrame::OnExit(wxCommandEvent& WXUNUSED(e))
{
    listController->SaveAllLists();
    Close(TRUE);
}

void MainFrame::OnRecipeListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the recipe list.
    listController->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
    menuBar->Remove(2);
    menuBar->Append(menuRecipeListEditor, "Recipe List Options");
}

void MainFrame::OnIngredientListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the ingredient list.
    listController->ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
    menuBar->Remove(2);
    menuBar->Append(menuIngredientListEditor, "Ingredient List Options");
}

void MainFrame::OnCategoryListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the category list.
    listController->ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
    menuBar->Remove(2);
    menuBar->Append(menuCategoryListEditor, "Category List Options");
}

void MainFrame::OnAddCategory(wxCommandEvent& WXUNUSED(e))
{
    AddCategoryFrame* addCategoryFrame = new AddCategoryFrame();
    addCategoryFrame->SetParent(this);
    addCategoryFrame->Show();
}

void MainFrame::OnRemoveCategory(wxCommandEvent& e)
{
    if (listController->GetSelectedCategoryName() != "")
    {
        // confirmation message.
        int choiceValue = wxNO;
        string cat = listController->GetSelectedCategoryName();
        wxMessageDialog* d = new wxMessageDialog(NULL, _("You are about to remove a category!\n" + cat + "  will not be removed if there are ingredients categorized as " + cat + "\n\nAre you sure you want to remove " + cat + "?"), _("Remove " + cat), wxYES_NO | wxCENTRE);
        choiceValue = d->ShowModal();
        switch (choiceValue)
        {
        case wxYES:
        case wxID_YES:
            listController->RemoveCategory();
        default:
            break;
        }
    }
}