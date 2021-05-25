#include "RecipeApp.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif
//*************************************************************************************************

// RecipeApp definition

//*************************************************************************************************

wxIMPLEMENT_APP(RecipeApp);
bool RecipeApp::OnInit()
{
    MainFrame* Main = new MainFrame(_("Recipe Manager App"));
    Main->SetParent(this);
    Main->Show(true);
    SetTopWindow(Main);
    return true;
}


//*************************************************************************************************

// AddCategoryFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(AddCategoryFrame, wxFrame)
EVT_MENU(FINALIZE, AddCategoryFrame::OnFinalize)
EVT_CLOSE(AddCategoryFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// AddCategoryFrame definition

//*************************************************************************************************

AddCategoryFrame::AddCategoryFrame() : wxFrame(NULL, wxID_ANY, wxString("New Category"), wxDefaultPosition, wxSize(400, 300), wxSTAY_ON_TOP | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(FINALIZE, "&Add Category\tAlt-A");
    menuBar = new wxMenuBar;
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

void AddCategoryFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}

// updates the category list with the newly created category
void AddCategoryFrame::OnFinalize(wxCommandEvent& WXUNUSED(e))
{
    string val = string(nameText->GetValue());
    parent->AddNewCategory(val);
}

void AddCategoryFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    menuOptions->~wxMenu();
    Destroy();
}


//*************************************************************************************************

// CategoryFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(CategoryFrame, wxFrame)
EVT_MENU(UPDATE, CategoryFrame::OnUpdate)
EVT_CLOSE(CategoryFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// CategoryFrame definition

//*************************************************************************************************

CategoryFrame::CategoryFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 200), wxSTAY_ON_TOP | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "&Update\tAlt-U");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "&Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);

    namePanel = new wxPanel(mainPanel, wxID_ANY);
    ingredientCountPanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Category Name:"), wxDefaultPosition, wxSize(200, 20));
    nameText = new wxTextCtrl(namePanel, CATEGORY_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    ingredientCountLabel = new wxStaticText(ingredientCountPanel, LABEL, wxString("Ingredients in Category Count:"), wxDefaultPosition, wxSize(200, 20));
    ingredientCountDisplay = new wxStaticText(ingredientCountPanel, CATEGORY_INGREDIENT_COUNT_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));

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

// assign currentCategory object with category being edited
void CategoryFrame::SetCategory(Category& c)
{
    currentCategory = &c;
    RebuildTextFields();
}

void CategoryFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}

// rebuilds the text fields after an update is made on currentCategory.
void CategoryFrame::RebuildTextFields()
{
    nameText->SetValue(currentCategory->getName());
    ingredientCountDisplay->SetLabel(wxString(to_string(currentCategory->getIngredientsUsingCategoryCount())));
}

// save changes and rebuild the list view in MainFrame after an update to a category is made
void CategoryFrame::OnUpdate(wxCommandEvent& e)
{
    string val = string(nameText->GetValue());
    currentCategory->setName(val);
    parent->SaveAllLists();
    parent->ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
}

void CategoryFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    menuOptions->~wxMenu();
    Destroy();
}

//*************************************************************************************************

// AddIngredientFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(AddIngredientFrame, wxFrame)
EVT_MENU(FINALIZE, AddIngredientFrame::OnFinalize)
EVT_CLOSE(AddIngredientFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// AddIngredientFrame definition

//*************************************************************************************************

AddIngredientFrame::AddIngredientFrame() : wxFrame(NULL, wxID_ANY, wxString("New Ingredient"), wxDefaultPosition, wxSize(400, 300), wxSTAY_ON_TOP | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(FINALIZE, "&Add Category\tAlt-A");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "&Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);
    namePanel = new wxPanel(mainPanel, wxID_ANY);
    descriptionPanel = new wxPanel(mainPanel, wxID_ANY);
    categoryPanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Ingredient Name:"), wxDefaultPosition, wxSize(100, 20));
    nameText = new wxTextCtrl(namePanel, INGREDIENT_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    descriptionLabel = new wxStaticText(descriptionPanel, LABEL, wxString("Description:"), wxDefaultPosition, wxSize(100, 20));
    descriptionText = new wxTextCtrl(descriptionPanel, INGREDIENT_DESCRIPTION_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 40));

    wxBoxSizer* const descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    descriptionSizer->Add(descriptionLabel, wxSizerFlags().Expand().Border(wxALL));
    descriptionSizer->Add(descriptionText, wxSizerFlags().Expand().Border(wxALL));
    descriptionPanel->SetSizer(descriptionSizer);

    categoryLabel = new wxStaticText(categoryPanel, LABEL, wxString("Category:"), wxDefaultPosition, wxSize(100, 20));
    categoryComboBox = new wxComboBox(categoryPanel, INGREDIENT_CATEGORY_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20), wxArrayString(), wxCB_READONLY);

    wxBoxSizer* const categorySizer = new wxBoxSizer(wxHORIZONTAL);
    categorySizer->Add(categoryLabel, wxSizerFlags().Expand().Border(wxALL));
    categorySizer->Add(categoryComboBox, wxSizerFlags().Expand().Border(wxALL));
    categoryPanel->SetSizer(categorySizer);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(descriptionPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(categoryPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);

    SetClientSize(mainPanel->GetMaxSize());
}


//*************************************************************************************************

// AddIngredientFrame function definition

//*************************************************************************************************

// set the parent object and populate drop down box list of strings to present
void AddIngredientFrame::SetParent(MainListCtrl* p)
{
    parent = p;
    parent->GetCategoryNamesList(categoryNames);
    for (auto& c : categoryNames)
        categoryComboBox->Append(wxString(c));    
}

// add a new ingredient to the ingredient list
void AddIngredientFrame::OnFinalize(wxCommandEvent& WXUNUSED(e))
{
    string nm = string(nameText->GetValue());
    string ds = string(descriptionText->GetValue());
    string ct = string(categoryComboBox->GetStringSelection());
    if(!nm.empty() && !ct.empty())
        parent->AddNewIngredient(nm, ds, ct);
}

void AddIngredientFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    menuOptions->~wxMenu();
    Destroy();
}

//*************************************************************************************************

// IngredientFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(IngredientFrame, wxFrame)
EVT_MENU(UPDATE, IngredientFrame::OnUpdate)
EVT_CLOSE(IngredientFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// IngredientFrame definition

//*************************************************************************************************

IngredientFrame::IngredientFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600), wxSTAY_ON_TOP | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "&Update\tAlt-U");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "&Options");
    SetMenuBar(menuBar);

    mainPanel = new wxScrolledWindow(this, wxID_ANY);

    namePanel = new wxPanel(mainPanel, wxID_ANY);
    descriptionPanel = new wxPanel(mainPanel, wxID_ANY);
    categoryPanel = new wxPanel(mainPanel, wxID_ANY);
    recipeUsingIngredientCountPanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Ingredient Name:"), wxDefaultPosition, wxSize(200, 20));
    nameText = new wxTextCtrl(namePanel, INGREDIENT_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    descriptionLabel = new wxStaticText(descriptionPanel, LABEL, wxString("Ingredients Description:"), wxDefaultPosition, wxSize(200, 20));
    descriptionText = new wxTextCtrl(descriptionPanel, INGREDIENT_DESCRIPTION_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    descriptionSizer->Add(descriptionLabel, wxSizerFlags().Expand().Border(wxALL));
    descriptionSizer->Add(descriptionText, wxSizerFlags().Expand().Border(wxALL));
    descriptionPanel->SetSizer(descriptionSizer);

    categoryLabel = new wxStaticText(categoryPanel, LABEL, wxString("Ingredient Category:"), wxDefaultPosition, wxSize(200, 20));
    categoryComboBox = new wxComboBox(categoryPanel, INGREDIENT_CATEGORY_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20), wxArrayString(), wxCB_READONLY);
    currentCategoryLabel = new wxStaticText(categoryPanel, LABEL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* const categorySizer = new wxBoxSizer(wxHORIZONTAL);
    categorySizer->Add(categoryLabel, wxSizerFlags().Expand().Border(wxALL));
    categorySizer->Add(currentCategoryLabel, wxSizerFlags().Expand().Border(wxALL));
    categorySizer->Add(categoryComboBox, wxSizerFlags().Expand().Border(wxALL));
    categoryPanel->SetSizer(categorySizer);

    recipeUsingIngredientCountLabel = new wxStaticText(recipeUsingIngredientCountPanel, LABEL, wxString("Recipes in Ingredient Count:"), wxDefaultPosition, wxSize(200, 20));
    currentRecipeUsingIngredientCountLabel = new wxStaticText(recipeUsingIngredientCountPanel, INGREDIENT_RECIPES_COUNT_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const recipeCountSizer = new wxBoxSizer(wxHORIZONTAL);
    recipeCountSizer->Add(recipeUsingIngredientCountLabel, wxSizerFlags().Expand().Border(wxALL));
    recipeCountSizer->Add(currentRecipeUsingIngredientCountLabel, wxSizerFlags().Expand().Border(wxALL));
    recipeUsingIngredientCountPanel->SetSizer(recipeCountSizer);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(descriptionPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(categoryPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(recipeUsingIngredientCountPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);

    SetClientSize(mainPanel->GetMaxSize());
    mainPanel->SetScrollRate(5, 5);
}


//*************************************************************************************************

// IngredientFrame function definition

//*************************************************************************************************

void IngredientFrame::SetIngredient(Ingredient& i, list<Category>& cat)
{
    currentIngredient = &i;
    catList = &cat;
    for (auto& c : *catList)
        categoryComboBox->Append(wxString(c.getName()));
    RebuildTextFields();
}

void IngredientFrame::RebuildTextFields()
{
    nameText->SetValue(currentIngredient->getName());
    descriptionText->SetValue(currentIngredient->getDescription());
    currentCategoryLabel->SetLabel(currentIngredient->getCategoryStr());
    currentRecipeUsingIngredientCountLabel->SetLabel(to_string(currentIngredient->getRecipesUsingIngredientCount()));
}


void IngredientFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}

void IngredientFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string nm = string(nameText->GetValue());
    currentIngredient->setName(nm);
    string ds = string(descriptionText->GetValue());
    currentIngredient->setDescription(ds);
    string ct = string(categoryComboBox->GetStringSelection());
    if(!ct.empty() || ct != currentIngredient->getCategoryStr())
        currentIngredient->setCategory(getCategoryInList(ct, *catList));
    parent->ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
    RebuildTextFields();
    parent->SaveAllLists();
}

void IngredientFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    // destroy dependents here!
    menuOptions->~wxMenu();
    Destroy();
}


//*************************************************************************************************

// IngredientInRecipeFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(IngredientInRecipeFrame, wxFrame)
EVT_MENU(UPDATE, IngredientInRecipeFrame::OnUpdateIngredientInRecipe)
EVT_CLOSE(IngredientInRecipeFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// IngredientInRecipeFrame definition

//*************************************************************************************************


IngredientInRecipeFrame::IngredientInRecipeFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 300), wxSTAY_ON_TOP | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "&Update\tAlt-A");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "&Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);

    namePanel = new wxPanel(mainPanel, wxID_ANY);
    quantityPanel = new wxPanel(mainPanel, wxID_ANY);
    unitPanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Ingredient:"), wxDefaultPosition, wxSize(100, 20));
    nameText = new wxStaticText(namePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20));
    nameComboBox = new wxComboBox(namePanel, INGREDIENT_IN_RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameComboBox, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);


    quantityLabel = new wxStaticText(quantityPanel, LABEL, wxString("Quantity:"), wxDefaultPosition, wxSize(100, 20));
    quantityText = new wxTextCtrl(quantityPanel, INGREDIENT_IN_RECIPE_QUANTITY_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const quantitySizer = new wxBoxSizer(wxHORIZONTAL);
    quantitySizer->Add(quantityLabel, wxSizerFlags().Expand().Border(wxALL));
    quantitySizer->Add(quantityText, wxSizerFlags().Expand().Border(wxALL));
    quantityPanel->SetSizer(quantitySizer);


    unitLabel = new wxStaticText(unitPanel, LABEL, wxString("Units:"), wxDefaultPosition, wxSize(100, 20));
    unitsText = new wxStaticText(unitPanel, INGREDIENT_IN_RECIPE_UNIT_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));
    unitsComboBox = new wxComboBox(unitPanel, INGREDIENT_IN_RECIPE_UNIT_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);


    wxBoxSizer* const unitSizer = new wxBoxSizer(wxHORIZONTAL);
    unitSizer->Add(unitLabel, wxSizerFlags().Expand().Border(wxALL));
    unitSizer->Add(unitsText, wxSizerFlags().Expand().Border(wxALL));
    unitSizer->Add(unitsComboBox, wxSizerFlags().Expand().Border(wxALL));
    unitPanel->SetSizer(unitSizer);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(quantityPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(unitPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);


    SetClientSize(mainPanel->GetMaxSize());
}

//*************************************************************************************************

// IngredientInRecipeFrame function definitions

//*************************************************************************************************

void IngredientInRecipeFrame::SetIngredientInRecipe(IngredientInRecipe& ir, list<Ingredient>& iList)
{
    currentIngredientInRecipe = &ir;
    ingredList = &iList;
    for (auto& i : iList)
        nameComboBox->Append(wxString(i.getName()));
    GetUnitStringList(unitList);
    for (list<string>::const_iterator i = unitList.begin(); i != unitList.end(); ++i)
        unitsComboBox->Append(wxString(i->c_str()));
}

void IngredientInRecipeFrame::RebuildTextFields()
{
    nameText->SetLabel(currentIngredientInRecipe->getIngredientName());
    quantityText->SetValue(to_string(currentIngredientInRecipe->getIngredientQuantity()));
    unitsText->SetLabel(currentIngredientInRecipe->getIngredientUnitStr());
}

void IngredientInRecipeFrame::SetParents(IngredientsInRecipeListCtrl* p, RecipeFrame* rf)
{
    parent = p;
}

void IngredientInRecipeFrame::OnUpdateIngredientInRecipe(wxCommandEvent& WXUNUSED(e))
{
    string nm = string(nameComboBox->GetStringSelection());
    if (ingredList->size() > 0)
    {
        for (auto& i : *ingredList)
        {
            if (nm == i.getName())
            {
                currentIngredientInRecipe->setIngredient(i);
                break;
            }
        }
    }
    string qSTR = string(quantityText->GetValue());
    float q = -1;
    if (!qSTR.empty() && all_of(qSTR.begin(), qSTR.end(), ::isdigit))
        q = stof(qSTR);
    currentIngredientInRecipe->setIngredientQuantity(q);

    string u = string(unitsComboBox->GetStringSelection());
    if(!u.empty())
        currentIngredientInRecipe->setIngredientUnit(u);

    parent->UpdateModifiedIngredient();
    RebuildTextFields();
}

void IngredientInRecipeFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    // destroy dependents here!
    menuOptions->~wxMenu();
    Destroy();
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

// Done in RecipeFrame object.

//*************************************************************************************************

// IngredientsInRecipeListCtrl function definitions

//*************************************************************************************************

void IngredientsInRecipeListCtrl::InsertIngredientsInRecipeListReportDisplay(IngredientInRecipe& ing, int i)
{
    wxString str;
    str = wxString(ing.getIngredientName());
    long temp = InsertItem(i, str);
    SetItemData(temp, i);

    str = wxString(to_string(ing.getIngredientQuantity()));
    SetItem(temp, 1, str);

    str = wxString(ing.getIngredientUnitStr());
    SetItem(temp, 2, str);
}

void IngredientsInRecipeListCtrl::SetParent(RecipeFrame* p)
{
    parent = p;
}

void IngredientsInRecipeListCtrl::SetIngredientsInRecipeList(list<IngredientInRecipe>& ingredInRecipe)
{
    ingredients = &ingredInRecipe;
}

void IngredientsInRecipeListCtrl::SetIngredientList(list<Ingredient>& iList)
{
    ingredList = &iList;
}

void IngredientsInRecipeListCtrl::SetSelectedItem(string name)
{
    for (auto& ir : *ingredients)
    {
        if (ir.getIngredientName() == name)
        {
            selectedIngredient = &ir;
            break;
        }
    }
}

void IngredientsInRecipeListCtrl::UpdateModifiedIngredient()
{
    parent->UpdateIngredientInRecipe();
    ResetListView(wxLC_REPORT);
}

string IngredientsInRecipeListCtrl::GetSelectedIngredient()
{    
    return (selectedIngredient ? selectedIngredient->getIngredientName() : "" );
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

    
    ingredientInRecipeFrame = new IngredientInRecipeFrame(selectedIngredient->getIngredientName());
    ingredientInRecipeFrame->SetIngredientInRecipe(*selectedIngredient, *ingredList);
    ingredientInRecipeFrame->SetParents(this, parent);
    ingredientInRecipeFrame->RebuildTextFields();
    ingredientInRecipeFrame->Show(true);
    
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

    sortRecipeIngredients(col, *ingredients);
    ResetListView(wxLC_REPORT);
}

// resets the list view of ingredeints in recipe in RecipeFrame object when updated
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
        BuildIngredientsInRecipeListReportDisplay();
        break;
    default:
        wxFAIL_MSG("Unknown wxLC_STYLE Request");
        break;
    }
    Show();
}

// Builds the list of ingredients to display in RecipeFrame object.
void IngredientsInRecipeListCtrl::BuildIngredientsInRecipeListReportDisplay()
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
    for (auto& ingred : *ingredients)
    {
        i++;
        InsertIngredientsInRecipeListReportDisplay(ingred, i);
    }

    SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
}



//*************************************************************************************************

// AddIngredientToRecipeFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(AddIngredientToRecipeFrame, wxFrame)
EVT_MENU(UPDATE, AddIngredientToRecipeFrame::OnFinalize)
EVT_CLOSE(AddIngredientToRecipeFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// AddIngredientToRecipeFrame definition

//*************************************************************************************************


AddIngredientToRecipeFrame::AddIngredientToRecipeFrame() : wxFrame(NULL, wxID_ANY, wxString("Add Ingredient"), wxDefaultPosition, wxSize(1000, 800), wxSTAY_ON_TOP | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "&Add Ingredient\tAlt-A");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);

    namePanel = new wxPanel(mainPanel, wxID_ANY);
    quantityPanel = new wxPanel(mainPanel, wxID_ANY);
    unitsPanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, wxID_ANY, wxString("Ingredient: "), wxDefaultPosition, wxSize(100, 20));
    nameComboBox = new wxComboBox(namePanel, INGREDIENT_IN_RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameComboBox, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    quantityLabel = new wxStaticText(quantityPanel, wxID_ANY, wxString("Quantity: "), wxDefaultPosition, wxSize(100, 20));
    quantityText = new wxTextCtrl(quantityPanel, INGREDIENT_IN_RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const quantitySizer = new wxBoxSizer(wxHORIZONTAL);
    quantitySizer->Add(quantityLabel, wxSizerFlags().Expand().Border(wxALL));
    quantitySizer->Add(quantityText, wxSizerFlags().Expand().Border(wxALL));
    quantityPanel->SetSizer(quantitySizer);

    unitsLabel = new wxStaticText(unitsPanel, wxID_ANY, wxString("Units: "), wxDefaultPosition, wxSize(100, 20));
    unitsComboBox = new wxComboBox(unitsPanel, INGREDIENT_IN_RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);

    wxBoxSizer* const unitsSizer = new wxBoxSizer(wxHORIZONTAL);
    unitsSizer->Add(unitsLabel, wxSizerFlags().Expand().Border(wxALL));
    unitsSizer->Add(unitsComboBox, wxSizerFlags().Expand().Border(wxALL));
    unitsPanel->SetSizer(unitsSizer);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(quantityPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(unitsPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);

    SetClientSize(mainPanel->GetMaxSize());
}

//*************************************************************************************************

// AddIngredientToRecipeFrame function definitions

//*************************************************************************************************

void AddIngredientToRecipeFrame::SetParent(RecipeFrame* p)
{
    parent = p;
}

void AddIngredientToRecipeFrame::SetComboBoxLists(list<Ingredient>& iList)
{
    ingredList = &iList;
    for (auto& i : iList)
        nameComboBox->Append(wxString(i.getName()));
    GetUnitStringList(unitList);
    if (unitList.size() > 0)
    {
        for (list<string>::const_iterator i = unitList.begin(); i != unitList.end(); ++i)
            unitsComboBox->Append(wxString(i->c_str()));
    }
}

void AddIngredientToRecipeFrame::OnFinalize(wxCommandEvent& WXUNUSED(e))
{
    string n = string(nameComboBox->GetStringSelection());
    string qSTR = string(quantityText->GetValue());
    float q = -1;
    if (!qSTR.empty() && all_of(qSTR.begin(), qSTR.end(), ::isdigit))
        q = stof(qSTR);
    string u = string(unitsComboBox->GetStringSelection());

    if (!n.empty() && q > 0 && !u.empty())
    {
        parent->AddIngredientToRecipe(n, q, u);
    }
    else
    {
        if (n.empty())
            wxMessageDialog d(this, "An ingredient must be chosen before adding to the recipe!", "Ingredient Selection Error");
        if (q <= 0)
            wxMessageDialog d(this, "Quantity value must be greater than zero!", "Quantity Value Error");
        if (u.empty())
            wxMessageDialog d(this, "A unit must be chosen before adding to the recipe!", "Unit Selection Error");
    }
}

void AddIngredientToRecipeFrame::OnExit(wxCloseEvent& e)
{
    // destroy dependents here!
    Destroy();
}

//*************************************************************************************************

// RecipeFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(RecipeFrame, wxFrame)
EVT_MENU(UPDATE, RecipeFrame::OnUpdateRecipe)
EVT_MENU(RECIPE_ADD_INGREDIENT, RecipeFrame::OnAddIngredient)
EVT_MENU(RECIPE_REMOVE_INGREDIENT, RecipeFrame::OnRemoveIngredient)
EVT_CLOSE(RecipeFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// RecipeFrame definition

//*************************************************************************************************

RecipeFrame::RecipeFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 800), wxSTAY_ON_TOP | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "&Update\tAlt-U");
    menuOptions->AppendSeparator();
    menuOptions->Append(RECIPE_ADD_INGREDIENT, "Add Ingredient");
    menuOptions->Append(RECIPE_REMOVE_INGREDIENT, "Remove Ingredient");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "&Options");
    SetMenuBar(menuBar);


    mainPanel = new wxScrolledWindow(this, wxID_ANY);

    namePanel = new wxPanel(mainPanel, wxID_ANY);
    cuisineMealtypePanel = new wxPanel(mainPanel, wxID_ANY);
    servingsPanel = new wxPanel(mainPanel, wxID_ANY);
    yieldPanel = new wxPanel(mainPanel, wxID_ANY);
    descriptionPanel = new wxPanel(mainPanel, wxID_ANY);
    directionPanel = new wxPanel(mainPanel, wxID_ANY);
    ingredientsPanel = new wxPanel(mainPanel, wxID_ANY);

    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Recipe Name:"), wxDefaultPosition, wxSize(100, 20));
    nameText = new wxTextCtrl(namePanel, RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    cuisineLabel = new wxStaticText(cuisineMealtypePanel, LABEL, wxString("Cuisine Type:"), wxDefaultPosition, wxSize(100, 20));
    cuisineText = new wxTextCtrl(cuisineMealtypePanel, RECIPE_CUISINE_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));
    mealtypeLabel = new wxStaticText(cuisineMealtypePanel, LABEL, wxString("Meal Type:"), wxDefaultPosition, wxSize(100, 20));
    mealtypeText = new wxTextCtrl(cuisineMealtypePanel, RECIPE_MEALTYPE_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));
//    mealtypeText = new wxStaticText(mealTypePanel, RECIPE_MEALTYPE_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));
//    mealtypeComboBox = new wxComboBox(mealTypePanel, RECIPE_MEALTYPE_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);


    wxBoxSizer* const cuisineMealtypeSizer = new wxBoxSizer(wxHORIZONTAL);
    cuisineMealtypeSizer->Add(cuisineLabel, wxSizerFlags().Expand().Border(wxALL));
    cuisineMealtypeSizer->Add(cuisineText, wxSizerFlags().Expand().Border(wxALL));
    cuisineMealtypeSizer->Add(mealtypeLabel, wxSizerFlags().Expand().Border(wxALL));
    cuisineMealtypeSizer->Add(mealtypeText, wxSizerFlags().Expand().Border(wxALL));
    cuisineMealtypePanel->SetSizer(cuisineMealtypeSizer);


    servingsLabel = new wxStaticText(servingsPanel, LABEL, wxString("Serves:"), wxDefaultPosition, wxSize(100, 20));
    servingsText = new wxTextCtrl(servingsPanel, RECIPE_SERVINGS_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* servingsSizer = new wxBoxSizer(wxHORIZONTAL);
    servingsSizer->Add(servingsLabel, wxSizerFlags().Expand().Border(wxALL));
    servingsSizer->Add(servingsText, wxSizerFlags().Expand().Border(wxALL));
    servingsPanel->SetSizer(servingsSizer);


    yieldLabel = new wxStaticText(yieldPanel, LABEL, wxString("Yields:"), wxDefaultPosition, wxSize(100, 20));
    yieldText = new wxTextCtrl(yieldPanel, RECIPE_YIELD_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));
    yieldUnitCurrent = new wxStaticText(yieldPanel, LABEL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));
    yieldUnitComboBox = new wxComboBox(yieldPanel, RECIPE_YIELD_UNIT_COMBO_BOX, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);

    wxBoxSizer* yieldsSizer = new wxBoxSizer(wxHORIZONTAL);
    yieldsSizer->Add(yieldLabel, wxSizerFlags().Expand().Border(wxALL));
    yieldsSizer->Add(yieldText, wxSizerFlags().Expand().Border(wxALL));
    yieldsSizer->Add(yieldUnitCurrent, wxSizerFlags().Expand().Border(wxALL));
    yieldsSizer->Add(yieldUnitComboBox, wxSizerFlags().Expand().Border(wxALL));
    yieldPanel->SetSizer(yieldsSizer);

    descriptionLabel = new wxStaticText(descriptionPanel, LABEL, wxString("Description:"), wxDefaultPosition, wxSize(100, 20));
    descriptionText = new wxTextCtrl(descriptionPanel, RECIPE_DESCRIPTION_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 100));

    wxBoxSizer* const descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    descriptionSizer->Add(descriptionLabel, wxSizerFlags().Expand().Border(wxALL));
    descriptionSizer->Add(descriptionText, wxSizerFlags().Expand().Border(wxALL));
    descriptionPanel->SetSizer(descriptionSizer);


    directionLabel = new wxStaticText(directionPanel, LABEL, wxString("Directions:"), wxDefaultPosition, wxSize(100, 20));
    directionText = new wxTextCtrl(directionPanel, RECIPE_DIRECTIONS_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 300), wxTE_MULTILINE);

    wxBoxSizer* const directionSizer = new wxBoxSizer(wxHORIZONTAL);
    directionSizer->Add(directionLabel, wxSizerFlags().Expand().Border(wxALL));
    directionSizer->Add(directionText, wxSizerFlags().Expand().Border(wxALL));
    directionPanel->SetSizer(directionSizer);

    ingredientsLabel = new wxStaticText(ingredientsPanel, LABEL, wxString("Ingredients:"), wxDefaultPosition, wxSize(100, 20));
    listIngredientsInRecipe = new IngredientsInRecipeListCtrl(ingredientsPanel, RECIPE_INGREDIENTS_LIST_CTRL, wxDefaultPosition, wxSize(600, 200), wxLC_REPORT | wxBORDER_THEME | wxLC_SINGLE_SEL);


    wxBoxSizer* const ingredientsSizer = new wxBoxSizer(wxHORIZONTAL);
    ingredientsSizer->Add(ingredientsLabel, wxSizerFlags().Expand().Border(wxALL));
    ingredientsSizer->Add(listIngredientsInRecipe, wxSizerFlags().Expand().Border(wxALL));
    ingredientsPanel->SetSizer(ingredientsSizer);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(cuisineMealtypePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(servingsPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(yieldPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(descriptionPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(directionPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(ingredientsPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);

    SetClientSize(mainPanel->GetMaxSize());
    mainPanel->SetScrollRate(5, 5);
}

//*************************************************************************************************

// RecipeFrame function definition

//*************************************************************************************************

void RecipeFrame::SetRecipe(Recipe& r, list<pair<string, int>>& tList, list<Ingredient>& iList)
{    
    isnew = false;
    currentRecipe = &r;

    typeList = &tList;
//    for (auto& t : *typeList)
//        mealtypeComboBox->Append(wxString(t.first));
    ingredList = &iList;
    list<string> unitList;
    GetUnitStringList(unitList);
    for (list<string>::const_iterator i = unitList.begin(); i != unitList.end(); ++i)
        yieldUnitComboBox->Append(wxString(i->c_str()));
    listIngredientsInRecipe->SetParent(this);
    listIngredientsInRecipe->SetIngredientsInRecipeList(currentRecipe->getAllIngredientsInRecipe());
    listIngredientsInRecipe->SetIngredientList(*ingredList);
    listIngredientsInRecipe->ResetListView(wxLC_REPORT);
}

void RecipeFrame::SetRecipe(list<pair<string, int>>& tList, list<Ingredient>& iList)
{
    isnew = true;
    newRecipe = Recipe();
    currentRecipe = &newRecipe;
    typeList = &tList;
    //    for (auto& t : *typeList)
    //        mealtypeComboBox->Append(wxString(t.first));
    ingredList = &iList;
    list<string> unitList;
    GetUnitStringList(unitList);
    for (list<string>::const_iterator i = unitList.begin(); i != unitList.end(); ++i)
        yieldUnitComboBox->Append(wxString(i->c_str()));
    listIngredientsInRecipe->SetParent(this);
    listIngredientsInRecipe->SetIngredientsInRecipeList(currentRecipe->getAllIngredientsInRecipe());
    listIngredientsInRecipe->SetIngredientList(*ingredList);
    listIngredientsInRecipe->ResetListView(wxLC_REPORT);
}

void RecipeFrame::RebuildTextFields()
{
    nameText->SetValue(currentRecipe->getName());
    cuisineText->SetValue(currentRecipe->getCuisine());
    mealtypeText->SetValue(currentRecipe->getMealType());
    servingsText->SetValue(wxString(to_string(currentRecipe->getServingCount())));
    yieldText->SetValue(wxString(to_string(currentRecipe->getYield())));
    yieldUnitCurrent->SetLabel(currentRecipe->getYieldUnitStr());
    descriptionText->SetValue(currentRecipe->getDescription());
    directionText->SetValue(currentRecipe->getDirection());
}

void RecipeFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}

void RecipeFrame::UpdateIngredientInRecipe()
{
    parent->SaveAllLists();
}

void RecipeFrame::AddIngredientToRecipe(string& name, float& qty, string& unit)
{
    currentRecipe->addIngredientInRecipe(name, qty, unit, *ingredList);
    parent->SaveAllLists();
    listIngredientsInRecipe->ResetListView();
}

void RecipeFrame::OnUpdateRecipe(wxCommandEvent& WXUNUSED(e))
{
    string nm = string(nameText->GetValue());
    if (!nm.empty())
        currentRecipe->setName(nm);
    string cu = string(cuisineText->GetValue());
    if (!cu.empty())
        currentRecipe->setCuisine(cu);
//    string mt = string(mealtypeComboBox->GetStringSelection());
    string mt = string(mealtypeText->GetValue());
    if(!mt.empty())
        currentRecipe->setMealType(mt, *typeList);
    int sc = stoi(string(servingsText->GetValue()));
    if (sc > 0)
        currentRecipe->setServingCount(sc);
    int yld = stoi(string(yieldText->GetValue()));
    if(yld > 0)
        currentRecipe->setYield(yld);
    string yldu = string(yieldUnitComboBox->GetStringSelection());
    if (!yldu.empty())
        currentRecipe->setYieldUnit(yldu);
    string ds = string(descriptionText->GetValue());
    if(!ds.empty())
        currentRecipe->setDescription(ds);
    string dr = string(directionText->GetValue());
    if(!dr.empty())
        currentRecipe->setDirection(dr);
    if (isnew)
        parent->AddRecipe(newRecipe);
    parent->SaveAllLists();
    RebuildTextFields();
    parent->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
}

void RecipeFrame::OnAddIngredient(wxCommandEvent& WXUNUSED(e))
{
    addIngredientToRecipe = new AddIngredientToRecipeFrame();
    addIngredientToRecipe->SetParent(this);
    addIngredientToRecipe->SetComboBoxLists(*ingredList);
    addIngredientToRecipe->Show(true);
}

void RecipeFrame::OnRemoveIngredient(wxCommandEvent& WXUNUSED(e))
{
    string i = listIngredientsInRecipe->GetSelectedIngredient();
    currentRecipe->removeIngredientFromRecipe(i);
    listIngredientsInRecipe->ResetListView();
    parent->SaveAllLists();
}

void RecipeFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    // destroy dependents here!
    menuOptions->~wxMenu();
    Destroy();
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

// Done in MainFrame object.


//*************************************************************************************************

// MainListCtrl function definitions

//*************************************************************************************************

void MainListCtrl::InsertItemsInRecipeListReportDisplay(Recipe& r, int& i)
{
    wxString str;
    str = wxString(r.getName());
    long temp = InsertItem(i, str);
    SetItemData(temp, i);

    str = wxString(r.getCuisine());
    SetItem(temp, 1, str);

    str = wxString(r.getMealType());
    SetItem(temp, 2, str);

    str = wxString(to_string(r.getServingCount()));
    SetItem(temp, 3, str);
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
    str = wxString(c.getName());
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

/*
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
*/

// Loads the list of user created categories, ingredients, and recipes from csv files
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
        SaveAllLists();
        ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

void MainListCtrl::AddNewIngredient(string& name, string& desc, string& cat)
{
    if (addIngredient(name, desc, getCategoryInList(cat, categories), ingredients))
    {
        SaveAllLists();
        ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

void MainListCtrl::RemoveCategory()
{
    string cat = selectedCategory->getName();
    if (removeCategory(cat, categories))
    {
        SaveAllLists();
        ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

void MainListCtrl::RemoveIngredient()
{
    string ing = selectedIngredient->getName();
    if (removeIngredient(ing, ingredients))
    {
        SaveAllLists();
        ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

void MainListCtrl::RemoveRecipe()
{
    string rec = selectedRecipe->getName();
    if (removeRecipe(rec, recipes))
    {
        SaveAllLists();
        ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

void MainListCtrl::CreateNewCategory()
{
    if (addCategoryFrame != nullptr)
        delete(addCategoryFrame);
    addCategoryFrame = new AddCategoryFrame();
    addCategoryFrame->SetParent(this);
    addCategoryFrame->Show();
}

void MainListCtrl::CreateNewIngredient()
{
    if (addIngredientFrame != nullptr)
        delete(addIngredientFrame);
    addIngredientFrame = new AddIngredientFrame();
    addIngredientFrame->SetParent(this);
    addIngredientFrame->Show();
}

void MainListCtrl::CreateNewRecipe()
{
    if (recipeFrame != nullptr)
        delete(recipeFrame);
    recipeFrame = new RecipeFrame("Create New Recipe");
    recipeFrame->SetRecipe(mealTypes, ingredients);
    recipeFrame->SetParent(this);
    recipeFrame->Show(true);
}

void MainListCtrl::AddRecipe(Recipe& nr)
{
    addRecipe(nr, recipes);
    SaveAllLists();
}

void MainListCtrl::GetCategoryNamesList(list<string>& names)
{
    for (auto& c : categories)
        names.push_back(c.getName());
}

string MainListCtrl::GetSelectedCategoryName()
{
    if (selectedCategory != nullptr)
        return selectedCategory->getName();
    else
        return "";
}

string MainListCtrl::GetSelectedIngredientName()
{
    if (selectedIngredient != nullptr)
        return selectedIngredient->getName();
    else
        return "";
}

string MainListCtrl::GetSelectedRecipeName()
{
    if (selectedRecipe != nullptr)
        return selectedRecipe->getName();
    else
        return "";
}

void MainListCtrl::GetIngredientsList(list<string>& list)
{
    for (auto& i : ingredients)
        list.push_back(i.getName());
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

    selectedItem = info;   

    info.m_mask = wxLIST_MASK_TEXT;
    if (GetItem(info))
    {
        SetSelectedItem(string(info.m_text));
    }
    
    // here we open a window to the activated item, depending on the currentList we are in.
    switch (GetCurrentList())
    {
    case RECIPE_LIST_REPORT_DISPLAY:
        // here we open a recipe Frame, make it the primary window, and populate fields with the recipe we have clicked on.

        recipeFrame = new RecipeFrame(selectedRecipe->getName());
        recipeFrame->SetRecipe(*selectedRecipe, mealTypes, ingredients);
        recipeFrame->SetParent(this);
        recipeFrame->RebuildTextFields();
        recipeFrame->Show(true);

        break;
    case INGREDIENT_LIST_REPORT_DISPLAY:
        // here we open an ingredient Frame, make it the primary window, and populate fields with the ingredient information we have clicked on.

        ingredientFrame = new IngredientFrame(selectedIngredient->getName());
        ingredientFrame->SetIngredient(*selectedIngredient, categories);
        ingredientFrame->SetParent(this);
        ingredientFrame->RebuildTextFields();
        ingredientFrame->Show(true);

        break;
    case CATEGORY_LIST_REPORT_DISPLAY:
        // here we open a category Frame, make it the primary window, and populate fields with the category we have clicked on.

        categoryFrame = new CategoryFrame(selectedCategory->getName());
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

    col.SetText("Cuisine");
    InsertColumn(1, col);

    col.SetText("Meal Type");
    InsertColumn(2, col);

    col.SetText("Servings");
    InsertColumn(3, col);

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
    EVT_CLOSE(MainFrame::OnExit)

    EVT_MENU(RECIPE_LIST_REPORT_DISPLAY, MainFrame::OnRecipeListReportDisplay)
    EVT_MENU(INGREDIENT_LIST_REPORT_DISPLAY, MainFrame::OnIngredientListReportDisplay)
    EVT_MENU(CATEGORY_LIST_REPORT_DISPLAY, MainFrame::OnCategoryListReportDisplay)


    EVT_MENU(CATEGORY_ADD_NEW, MainFrame::OnAddCategory)
    EVT_MENU(CATEGORY_REMOVE_SELECTED, MainFrame::OnRemoveCategory)
    EVT_MENU(INGREDIENT_ADD_NEW, MainFrame::OnAddIngredient)
    EVT_MENU(INGREDIENT_REMOVE_SELECTED, MainFrame::OnRemoveIngredient)
    EVT_MENU(RECIPE_ADD_NEW, MainFrame::OnAddRecipe)
    EVT_MENU(RECIPE_REMOVE_SELECTED, MainFrame::OnRemoveRecipe)
wxEND_EVENT_TABLE()

//*************************************************************************************************

// MainFrame definition

//*************************************************************************************************

MainFrame::MainFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 500), wxSTAY_ON_TOP|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCAPTION|wxCLOSE_BOX|wxCLIP_CHILDREN)
{

    // Menu Bar
    // File menu
    menuFile = new wxMenu;
    menuFile->Append(ABOUT, "&About\tAlt-A");
    menuFile->AppendSeparator();
    menuFile->Append(EXIT, "&Quit\tAlt-Q");


/*
    // Category List Editor menu
    menuCategoryListEditor = new wxMenu;
    menuCategoryListEditor->Append(CATEGORY_ADD_NEW, "Create Category");
    menuCategoryListEditor->Append(CATEGORY_REMOVE_SELECTED, "Remove Selected Category");
     
    // Ingredient List Editor menu
    menuIngredientListEditor = new wxMenu;
    menuIngredientListEditor->Append(INGREDIENT_ADD_NEW, "Create Ingredient");
    menuIngredientListEditor->Append(INGREDIENT_REMOVE_SELECTED, "Remove Selected Ingredient");
     
    
    // Recipe List Editor menu, default start point.
    menuRecipeListEditor = new wxMenu;
    menuRecipeListEditor->Append(RECIPE_ADD_NEW, "Create Recipe");
    menuRecipeListEditor->Append(RECIPE_REMOVE_SELECTED, "Remove Selected Recipe");
    */
    // List menu
    menuList = new wxMenu;
    menuList->Append(RECIPE_LIST_REPORT_DISPLAY, "Display &Recipe List\tAlt-R");
    menuList->Append(RECIPE_ADD_NEW, "Create Recipe");
    menuList->Append(RECIPE_REMOVE_SELECTED, "Remove Selected Recipe");
    menuList->AppendSeparator();
    menuList->Append(INGREDIENT_LIST_REPORT_DISPLAY, "Display &Ingredient List\tAlt-I");
    menuList->Append(INGREDIENT_ADD_NEW, "Create Ingredient");
    menuList->Append(INGREDIENT_REMOVE_SELECTED, "Remove Selected Ingredient");
    menuList->AppendSeparator();
    menuList->Append(CATEGORY_LIST_REPORT_DISPLAY, "Display &Category List\tAlt-C");
    menuList->Append(CATEGORY_ADD_NEW, "Create Category");
    menuList->Append(CATEGORY_REMOVE_SELECTED, "Remove Selected Category");

    // keep recipe list editor menu enabled, disable other options
    menuList->Enable(RECIPE_LIST_REPORT_DISPLAY, false);
    menuList->Enable(RECIPE_ADD_NEW, true);
    menuList->Enable(RECIPE_REMOVE_SELECTED, true);
    menuList->Enable(INGREDIENT_LIST_REPORT_DISPLAY, true);
    menuList->Enable(INGREDIENT_ADD_NEW, false);
    menuList->Enable(INGREDIENT_REMOVE_SELECTED, false);
    menuList->Enable(CATEGORY_LIST_REPORT_DISPLAY, true);
    menuList->Enable(CATEGORY_ADD_NEW, false);
    menuList->Enable(CATEGORY_REMOVE_SELECTED, false);

    // Define menu bar
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuList, "&Lists");
//    menuBar->Append(menuRecipeListEditor, "Recipe List Options");
    SetMenuBar(menuBar);

    panel = new wxPanel(this, wxID_ANY);

    // default startup of list display to 
    listController = new MainListCtrl(panel, MAIN_LIST_CTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxBORDER_THEME | wxLC_SINGLE_SEL);
    listController->LoadLists();
    listController->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);

    wxBoxSizer* const sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(listController, wxSizerFlags(2).Expand().Border(wxALL, 10));
    panel->SetSizer(sizer);

    SetClientSize(panel->GetMaxSize());
}

//*************************************************************************************************

// MainFrame function definitions

//*************************************************************************************************

void MainFrame::SetParent(RecipeApp* p)
{
    parent = p;
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(e))
{
    wxMessageDialog dialog(this, "Recipe Manager System\nStephen Polozoff (c) 2021", "About Recipe Manager");
    dialog.ShowModal();
}

void MainFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    listController->SaveAllLists();
    // release data, prevent memory leaks
    menuList->~wxMenu();
    parent->Exit();
    Destroy();
}

void MainFrame::OnRecipeListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the recipe list.
    listController->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
    
    menuList->Enable(RECIPE_LIST_REPORT_DISPLAY, false);
    menuList->Enable(RECIPE_ADD_NEW, true);
    menuList->Enable(RECIPE_REMOVE_SELECTED, true);
    menuList->Enable(INGREDIENT_LIST_REPORT_DISPLAY, true);
    menuList->Enable(INGREDIENT_ADD_NEW, false);
    menuList->Enable(INGREDIENT_REMOVE_SELECTED, false);
    menuList->Enable(CATEGORY_LIST_REPORT_DISPLAY, true);
    menuList->Enable(CATEGORY_ADD_NEW, false);
    menuList->Enable(CATEGORY_REMOVE_SELECTED, false);
//    menuBar->Remove(2);
//    menuBar->Append(menuRecipeListEditor, "Recipe List Options");
}

void MainFrame::OnIngredientListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the ingredient list.
    listController->ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);

    menuList->Enable(RECIPE_LIST_REPORT_DISPLAY, true);
    menuList->Enable(RECIPE_ADD_NEW, false);
    menuList->Enable(RECIPE_REMOVE_SELECTED, false);
    menuList->Enable(INGREDIENT_LIST_REPORT_DISPLAY, false);
    menuList->Enable(INGREDIENT_ADD_NEW, true);
    menuList->Enable(INGREDIENT_REMOVE_SELECTED, true);
    menuList->Enable(CATEGORY_LIST_REPORT_DISPLAY, true);
    menuList->Enable(CATEGORY_ADD_NEW, false);
    menuList->Enable(CATEGORY_REMOVE_SELECTED, false);
//    menuBar->Remove(2);
//    menuBar->Append(menuIngredientListEditor, "Ingredient List Options");
}

void MainFrame::OnCategoryListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the category list.
    listController->ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);

    menuList->Enable(RECIPE_LIST_REPORT_DISPLAY, true);
    menuList->Enable(RECIPE_ADD_NEW, false);
    menuList->Enable(RECIPE_REMOVE_SELECTED, false);
    menuList->Enable(INGREDIENT_LIST_REPORT_DISPLAY, true);
    menuList->Enable(INGREDIENT_ADD_NEW, false);
    menuList->Enable(INGREDIENT_REMOVE_SELECTED, false);
    menuList->Enable(CATEGORY_LIST_REPORT_DISPLAY, false);
    menuList->Enable(CATEGORY_ADD_NEW, true);
    menuList->Enable(CATEGORY_REMOVE_SELECTED, true);
//    menuBar->Remove(2);
//    menuBar->Append(menuCategoryListEditor, "Category List Options");
}

void MainFrame::OnAddCategory(wxCommandEvent& WXUNUSED(e))
{
    listController->CreateNewCategory();
    
}

void MainFrame::OnRemoveCategory(wxCommandEvent& e)
{
    if (listController->GetSelectedCategoryName() != "")
    {
        // confirmation message.
        int choiceValue = wxNO;
        string cat = listController->GetSelectedCategoryName();
        wxMessageDialog d(NULL, _("You are about to remove a category!\n" + cat + "  will not be removed if there are ingredients categorized as " + cat + "\n\nAre you sure you want to remove " + cat + "?"), _("Remove " + cat), wxYES_NO | wxCENTRE);
        choiceValue = d.ShowModal();
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

void MainFrame::OnAddIngredient(wxCommandEvent& WXUNUSED(e))
{
    listController->CreateNewIngredient();
    
}

void MainFrame::OnRemoveIngredient(wxCommandEvent& e)
{
    if (listController->GetSelectedIngredientName() != "")
    {
        // confirmation message.
        int choiceValue = wxNO;
        string ing = listController->GetSelectedIngredientName();
        wxMessageDialog d(NULL, _("You are about to remove an ingredient!\n" + ing + " will not be removed if there are recipes using the ingredient " + ing + "\n\nAre you sure you want to remove " + ing + "?"), _("Remove " + ing), wxYES_NO | wxCENTRE);
        choiceValue = d.ShowModal();
        switch (choiceValue)
        {
        case wxYES:
        case wxID_YES:
            listController->RemoveIngredient();
        default:
            break;
        }
    }
}

void MainFrame::OnAddRecipe(wxCommandEvent& e)
{
    listController->CreateNewRecipe();
}

void MainFrame::OnRemoveRecipe(wxCommandEvent& e)
{
    if (listController->GetSelectedRecipeName() != "")
    {
        // confirmation message.
        int choiceValue = wxNO;
        string rec = listController->GetSelectedRecipeName();
        wxMessageDialog d(NULL, _("You are about to remove a recipe!\n" + rec + " will not be removed if there are recipes using the ingredient " + rec + "\n\nAre you sure you want to remove " + rec + "?"), _("Remove " + rec), wxYES_NO | wxCENTRE);
        choiceValue = d.ShowModal();
        switch (choiceValue)
        {
        case wxYES:
        case wxID_YES:
            listController->RemoveRecipe();
        default:
            break;
        }
    }
}