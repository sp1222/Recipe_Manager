#include "RecipeApp.h"

using namespace std;

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif
//*************************************************************************************************

// RecipeApp definition

//*************************************************************************************************

wxIMPLEMENT_APP(RecipeApp);
bool RecipeApp::OnInit()
{
    ListMgrFrame* Main = new ListMgrFrame(_("Recipe Manager App"));
    Main->SetParent(this);
    Main->Show(true);
    SetTopWindow(Main);
    return true;
}


//*************************************************************************************************

// AddCategoryFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(AddCategoryFrame, wxFrame)
EVT_MENU(UPDATE, AddCategoryFrame::OnUpdate)
EVT_CLOSE(AddCategoryFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// AddCategoryFrame definition

//*************************************************************************************************

AddCategoryFrame::AddCategoryFrame() : wxFrame(NULL, wxID_ANY, wxString("New Category"), wxDefaultPosition, wxSize(400, 200), wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "Update");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "Options");
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

// set parent to MainListCtrl object for updating list with new Cateogry object
void AddCategoryFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}

void AddCategoryFrame::SetFieldsToBlank()
{
    nameText->SetValue("");
}

// updates the category list with the newly created category
void AddCategoryFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string val = string(nameText->GetValue());
    parent->AddNewCategory(val);
    // either destroy this frame or reset the fields.
    SetFieldsToBlank();
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

class ListMgrFrame; // forward
CategoryFrame::CategoryFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 200), wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "Update");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);


    namePanel = new wxPanel(mainPanel, wxID_ANY);
    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Category Name:"), wxDefaultPosition, wxSize(200, 20));
    nameText = new wxTextCtrl(namePanel, CATEGORY_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    ingredientCountPanel = new wxPanel(mainPanel, wxID_ANY);
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

// assign currentCategory object with reference to category being edited
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

// save changes and rebuild the list view in ListMgrFrame after an update to a category is made
void CategoryFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string val = string(nameText->GetValue());
    if (currentCategory->setName(val))
    {
        parent->SaveCategories();
        parent->SaveIngredients();
        parent->ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);   // does this makes sense here?
        wxMessageDialog d(this, "Category has been renamed " + currentCategory->getName(), "Success");
        d.ShowModal();
    }
    else
    {
        wxMessageDialog d(this, "Unable to change the name of " + currentCategory->getName() + " Category.\nField cannot be empty", "Failure");
        d.ShowModal();
    }
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
EVT_MENU(UPDATE, AddIngredientFrame::OnUpdate)
EVT_CLOSE(AddIngredientFrame::OnExit)
wxEND_EVENT_TABLE()

// NOTE, COMBINE AddIngredientFrame WITH IngredientFrame CLASS.


//*************************************************************************************************

// AddIngredientFrame definition

//*************************************************************************************************

AddIngredientFrame::AddIngredientFrame() : wxFrame(NULL, wxID_ANY, wxString("New Ingredient"), wxDefaultPosition, wxSize(400, 300), wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "Update");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);

    namePanel = new wxPanel(mainPanel, wxID_ANY);
    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Ingredient Name:"), wxDefaultPosition, wxSize(100, 20));
    nameText = new wxTextCtrl(namePanel, INGREDIENT_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    descriptionPanel = new wxPanel(mainPanel, wxID_ANY);
    descriptionLabel = new wxStaticText(descriptionPanel, LABEL, wxString("Description:"), wxDefaultPosition, wxSize(100, 20));
    descriptionText = new wxTextCtrl(descriptionPanel, INGREDIENT_DESCRIPTION_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 40), wxTE_MULTILINE);

    wxBoxSizer* const descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    descriptionSizer->Add(descriptionLabel, wxSizerFlags().Expand().Border(wxALL));
    descriptionSizer->Add(descriptionText, wxSizerFlags().Expand().Border(wxALL));
    descriptionPanel->SetSizer(descriptionSizer);

    categoryPanel = new wxPanel(mainPanel, wxID_ANY);
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
}

void AddIngredientFrame::SetCategoryComboBox(list<string> nms)
{
    for (auto& c : nms)
        categoryComboBox->Append(wxString(c));
    categoryComboBox->SetValue("NONE");
}

void AddIngredientFrame::SetFieldsToBlank()
{
    nameText->SetValue("");
    descriptionText->SetValue("");
    categoryComboBox->SetValue("NONE");
}

// add a new ingredient to the ingredient list
void AddIngredientFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string nm = string(nameText->GetValue());
    string ds = string(descriptionText->GetValue());
    string ct = string(categoryComboBox->GetStringSelection());
    parent->AddNewIngredient(nm, ds, ct);
    // either destroy this frame, or reset to add another ingredient..
    SetFieldsToBlank();
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

IngredientFrame::IngredientFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 300), wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "Update");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "Options");
    SetMenuBar(menuBar);

    mainPanel = new wxScrolledWindow(this, wxID_ANY);


    namePanel = new wxPanel(mainPanel, wxID_ANY);
    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Ingredient Name:"), wxDefaultPosition, wxSize(200, 20));
    nameText = new wxTextCtrl(namePanel, INGREDIENT_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    descriptionPanel = new wxPanel(mainPanel, wxID_ANY);
    descriptionLabel = new wxStaticText(descriptionPanel, LABEL, wxString("Ingredients Description:"), wxDefaultPosition, wxSize(200, 20));
    descriptionText = new wxTextCtrl(descriptionPanel, INGREDIENT_DESCRIPTION_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxTE_MULTILINE);

    wxBoxSizer* const descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    descriptionSizer->Add(descriptionLabel, wxSizerFlags().Expand().Border(wxALL));
    descriptionSizer->Add(descriptionText, wxSizerFlags().Expand().Border(wxALL));
    descriptionPanel->SetSizer(descriptionSizer);

    categoryPanel = new wxPanel(mainPanel, wxID_ANY);
    categoryLabel = new wxStaticText(categoryPanel, LABEL, wxString("Ingredient Category:"), wxDefaultPosition, wxSize(200, 20));
    categoryComboBox = new wxComboBox(categoryPanel, INGREDIENT_CATEGORY_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20), wxArrayString(), wxCB_READONLY);
    currentCategoryLabel = new wxStaticText(categoryPanel, LABEL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* const categorySizer = new wxBoxSizer(wxHORIZONTAL);
    categorySizer->Add(categoryLabel, wxSizerFlags().Expand().Border(wxALL));
    categorySizer->Add(currentCategoryLabel, wxSizerFlags().Expand().Border(wxALL));
    categorySizer->Add(categoryComboBox, wxSizerFlags().Expand().Border(wxALL));
    categoryPanel->SetSizer(categorySizer);

    recipeUsingIngredientCountPanel = new wxPanel(mainPanel, wxID_ANY);
    recipeUsingIngredientCountLabel = new wxStaticText(recipeUsingIngredientCountPanel, LABEL, wxString("Recipes Usage Count:"), wxDefaultPosition, wxSize(200, 20));
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

void IngredientFrame::SetIngredient(Ingredient& i)
{
    currentIngredient = &i;
    RebuildTextFields();
}

void IngredientFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}

void IngredientFrame::PassCategoryList(list<Category>& cat) // does it make more sense to pass a list of strings instead?
{
    catList = &cat;
    SetCategoryComboBox();
}

void IngredientFrame::SetCategoryComboBox()
{
    for (auto& c : *catList)
        categoryComboBox->Append(wxString(c.getName()));
    categoryComboBox->SetValue("NONE");
}

void IngredientFrame::RebuildTextFields()
{
//    nameText->SetValue(currentIngredient->getName());
//    descriptionText->SetValue(currentIngredient->getDescription());
    currentCategoryLabel->SetLabel(currentIngredient->getCategoryStr());
    currentRecipeUsingIngredientCountLabel->SetLabel(to_string(currentIngredient->getRecipesUsingIngredientCount()));
}

// ADD MESSAGES HERE
void IngredientFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string ds = string(descriptionText->GetValue());
    currentIngredient->setDescription(ds);
    string ct = string(categoryComboBox->GetStringSelection());
    currentIngredient->setCategory(getCategoryInList(ct, *catList));
    string nm = string(nameText->GetValue());
    if (currentIngredient->setName(nm))
    {
        parent->ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
        RebuildTextFields();
        parent->SaveIngredients();
        parent->SaveRecipes();
    }
    else
    {
        wxMessageDialog d(this, "Unable to change the name of " + currentIngredient->getName() + " Ingredient.\nField cannot be empty", "Failure");
        d.ShowModal();
    }
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
EVT_MENU(UPDATE, IngredientInRecipeFrame::OnUpdate)
EVT_CLOSE(IngredientInRecipeFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// IngredientInRecipeFrame definition

//*************************************************************************************************


IngredientInRecipeFrame::IngredientInRecipeFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 300), wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "Update");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);


    namePanel = new wxPanel(mainPanel, wxID_ANY);
    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Ingredient:"), wxDefaultPosition, wxSize(100, 20));
    nameText = new wxStaticText(namePanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 20));
    nameComboBox = new wxComboBox(namePanel, INGREDIENT_IN_RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameComboBox, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);


    quantityPanel = new wxPanel(mainPanel, wxID_ANY);
    quantityLabel = new wxStaticText(quantityPanel, LABEL, wxString("Quantity:"), wxDefaultPosition, wxSize(100, 20));
    quantityText = new wxTextCtrl(quantityPanel, INGREDIENT_IN_RECIPE_QUANTITY_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const quantitySizer = new wxBoxSizer(wxHORIZONTAL);
    quantitySizer->Add(quantityLabel, wxSizerFlags().Expand().Border(wxALL));
    quantitySizer->Add(quantityText, wxSizerFlags().Expand().Border(wxALL));
    quantityPanel->SetSizer(quantitySizer);


    unitPanel = new wxPanel(mainPanel, wxID_ANY);
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

void IngredientInRecipeFrame::SetIngredientInRecipe(IngredientInRecipe& ir)
{
    currentIngredientInRecipe = &ir;
}

void IngredientInRecipeFrame::PassIngredientList_SetComboBoxes(list<Ingredient>& iList)
{
    ingredList = &iList;
    SetIngredientComboBox();
    SetUnitComboBox();
}

void IngredientInRecipeFrame::SetIngredientComboBox()
{
    for (auto& i : *ingredList)
        nameComboBox->Append(wxString(i.getName()));
}

void IngredientInRecipeFrame::SetUnitComboBox()
{
    GetUnitStringList(unitList);
    for (list<string>::const_iterator i = unitList.begin(); i != unitList.end(); ++i)
        unitsComboBox->Append(wxString(i->c_str()));
}

void IngredientInRecipeFrame::RebuildTextFields()
{
    nameText->SetLabel(currentIngredientInRecipe->getIngredientName());
//    quantityText->SetValue(to_string(currentIngredientInRecipe->getIngredientQuantity()));
    unitsText->SetLabel(currentIngredientInRecipe->getIngredientUnitStr());
}

void IngredientInRecipeFrame::SetFieldsToBlank()
{
    nameComboBox->SetValue(nameText->GetLabelText());
    unitsComboBox->SetValue("NONE");
}

void IngredientInRecipeFrame::SetParents(IngredientsInRecipeListCtrl* p)
{
    parent = p;
}

void IngredientInRecipeFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string nm = string(nameComboBox->GetStringSelection());
    currentIngredientInRecipe->setIngredient(nm, *ingredList);
    string u = string(unitsComboBox->GetStringSelection());
    currentIngredientInRecipe->setIngredientUnit(u);
    string temp = string(quantityText->GetValue());
    float q = 0;
    if (!temp.empty() && isFloat(temp))
        q = stof(temp);
    currentIngredientInRecipe->setIngredientQuantity(q);
    parent->UpdateIngredientInRecipe();
    RebuildTextFields();
    SetFieldsToBlank();
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
    // is it worth passing reference to Recipe object to IngredientsInRecipeListCtrl to get to  list<IngredientInRecipe>?
    for (auto& ir : *ingredients)
    {
        if (ir.getIngredientName() == name)
        {
            selectedIngredient = &ir;
            break;
        }
    }
}

void IngredientsInRecipeListCtrl::UpdateIngredientInRecipe()
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
    ingredientInRecipeFrame->SetParents(this);
    ingredientInRecipeFrame->SetIngredientInRecipe(*selectedIngredient);
    ingredientInRecipeFrame->PassIngredientList_SetComboBoxes(*ingredList);
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
EVT_MENU(UPDATE, AddIngredientToRecipeFrame::OnUpdate)
EVT_CLOSE(AddIngredientToRecipeFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// AddIngredientToRecipeFrame definition

//*************************************************************************************************


AddIngredientToRecipeFrame::AddIngredientToRecipeFrame() : wxFrame(NULL, wxID_ANY, wxString("Add Ingredient"), wxDefaultPosition, wxSize(600, 400), wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "Add Ingredient");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "Options");
    SetMenuBar(menuBar);

    mainPanel = new wxPanel(this, wxID_ANY);


    namePanel = new wxPanel(mainPanel, wxID_ANY);
    nameLabel = new wxStaticText(namePanel, wxID_ANY, wxString("Ingredient: "), wxDefaultPosition, wxSize(100, 20));
    nameComboBox = new wxComboBox(namePanel, INGREDIENT_IN_RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameComboBox, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    quantityPanel = new wxPanel(mainPanel, wxID_ANY);
    quantityLabel = new wxStaticText(quantityPanel, wxID_ANY, wxString("Quantity: "), wxDefaultPosition, wxSize(100, 20));
    quantityText = new wxTextCtrl(quantityPanel, INGREDIENT_IN_RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));

    wxBoxSizer* const quantitySizer = new wxBoxSizer(wxHORIZONTAL);
    quantitySizer->Add(quantityLabel, wxSizerFlags().Expand().Border(wxALL));
    quantitySizer->Add(quantityText, wxSizerFlags().Expand().Border(wxALL));
    quantityPanel->SetSizer(quantitySizer);

    unitsPanel = new wxPanel(mainPanel, wxID_ANY);
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

void AddIngredientToRecipeFrame::PassIngredientList(list<Ingredient>& iList)
{
    ingredList = &iList;
    SetIngredientComboBox();
}

void AddIngredientToRecipeFrame::SetIngredientComboBox()
{
    for (auto& i : *ingredList)
        nameComboBox->Append(wxString(i.getName()));
}

void AddIngredientToRecipeFrame::SetUnitComboBox()
{
    GetUnitStringList(unitList);
    for (list<string>::const_iterator i = unitList.begin(); i != unitList.end(); ++i)
        unitsComboBox->Append(wxString(i->c_str()));
}

void AddIngredientToRecipeFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string n = string(nameComboBox->GetStringSelection());
    string temp = string(quantityText->GetValue());
    float q = 0;
    if (!temp.empty() && isFloat(temp))
        q = stof(temp);
    string u = string(unitsComboBox->GetStringSelection());

    if (!n.empty() && q > 0 && !u.empty())
        parent->AddIngredientToRecipe(n, q, u);

    /*else  // not sure why this is not working..
    {
        if (n.empty())
            wxMessageDialog d(this, "An ingredient must be chosen before adding to the recipe!", "Ingredient Selection Error");
        if (q <= 0)
            wxMessageDialog d(this, "Quantity value must be greater than zero!", "Quantity Value Error");
        if (u.empty())
            wxMessageDialog d(this, "A unit must be chosen before adding to the recipe!", "Unit Selection Error");
    }*/
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
EVT_MENU(UPDATE, RecipeFrame::OnUpdate)
EVT_MENU(RECIPE_ADD_INGREDIENT, RecipeFrame::OnAddIngredient)
EVT_MENU(RECIPE_REMOVE_INGREDIENT, RecipeFrame::OnRemoveIngredient)
EVT_CLOSE(RecipeFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// RecipeFrame definition

//*************************************************************************************************

RecipeFrame::RecipeFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 900), wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    // Menu Bar
    // File menu
    menuOptions = new wxMenu;
    menuOptions->Append(UPDATE, "Update");
    menuOptions->AppendSeparator();
    menuOptions->Append(RECIPE_ADD_INGREDIENT, "Add Ingredient");
    menuOptions->Append(RECIPE_REMOVE_INGREDIENT, "Remove Ingredient");
    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "Options");
    SetMenuBar(menuBar);


    mainPanel = new wxScrolledWindow(this, wxID_ANY);


    namePanel = new wxPanel(mainPanel, wxID_ANY);
    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Recipe Name:"), wxDefaultPosition, wxSize(120, 20));
    nameText = new wxTextCtrl(namePanel, RECIPE_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 20));

    wxBoxSizer* const nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    cuisinerecipetypePanel = new wxPanel(mainPanel, wxID_ANY);
    cuisineLabel = new wxStaticText(cuisinerecipetypePanel, LABEL, wxString("Cuisine Type:"), wxDefaultPosition, wxSize(120, 20));
    cuisineText = new wxTextCtrl(cuisinerecipetypePanel, RECIPE_CUISINE_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));
    recipetypeLabel = new wxStaticText(cuisinerecipetypePanel, LABEL, wxString("Recipe Type:"), wxDefaultPosition, wxSize(100, 20));
    recipetypeText = new wxTextCtrl(cuisinerecipetypePanel, RECIPE_RECIPETYPE_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));
//    recipetypeText = new wxStaticText(recipetypePanel, RECIPE_recipetype_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20));
//    recipetypeComboBox = new wxComboBox(recipetypePanel, RECIPE_recipetype_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);


    wxBoxSizer* const cuisinerecipetypeSizer = new wxBoxSizer(wxHORIZONTAL);
    cuisinerecipetypeSizer->Add(cuisineLabel, wxSizerFlags().Expand().Border(wxALL));
    cuisinerecipetypeSizer->Add(cuisineText, wxSizerFlags().Expand().Border(wxALL));
    cuisinerecipetypeSizer->Add(recipetypeLabel, wxSizerFlags().Expand().Border(wxALL));
    cuisinerecipetypeSizer->Add(recipetypeText, wxSizerFlags().Expand().Border(wxALL));
    cuisinerecipetypePanel->SetSizer(cuisinerecipetypeSizer);


    servingsPanel = new wxPanel(mainPanel, wxID_ANY);
    servingsLabel = new wxStaticText(servingsPanel, LABEL, wxString("Number of Servings:"), wxDefaultPosition, wxSize(120, 20));
    servingsText = new wxTextCtrl(servingsPanel, RECIPE_SERVINGS_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* servingsSizer = new wxBoxSizer(wxHORIZONTAL);
    servingsSizer->Add(servingsLabel, wxSizerFlags().Expand().Border(wxALL));
    servingsSizer->Add(servingsText, wxSizerFlags().Expand().Border(wxALL));
    servingsPanel->SetSizer(servingsSizer);


    yieldPanel = new wxPanel(mainPanel, wxID_ANY);
    yieldLabel = new wxStaticText(yieldPanel, LABEL, wxString("Yields:"), wxDefaultPosition, wxSize(120, 20));
    yieldText = new wxTextCtrl(yieldPanel, RECIPE_YIELD_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));
    yieldUnitCurrent = new wxStaticText(yieldPanel, LABEL, wxEmptyString, wxDefaultPosition, wxSize(100, 20));
    yieldUnitComboBox = new wxComboBox(yieldPanel, RECIPE_YIELD_UNIT_COMBO_BOX, wxEmptyString, wxDefaultPosition, wxSize(200, 20), wxArrayString(), wxCB_READONLY);

    wxBoxSizer* yieldsSizer = new wxBoxSizer(wxHORIZONTAL);
    yieldsSizer->Add(yieldLabel, wxSizerFlags().Expand().Border(wxALL));
    yieldsSizer->Add(yieldText, wxSizerFlags().Expand().Border(wxALL));
    yieldsSizer->Add(yieldUnitCurrent, wxSizerFlags().Expand().Border(wxALL));
    yieldsSizer->Add(yieldUnitComboBox, wxSizerFlags().Expand().Border(wxALL));
    yieldPanel->SetSizer(yieldsSizer);

    descriptionPanel = new wxPanel(mainPanel, wxID_ANY);
    descriptionLabel = new wxStaticText(descriptionPanel, LABEL, wxString("Description:"), wxDefaultPosition, wxSize(120, 20));
    descriptionText = new wxTextCtrl(descriptionPanel, RECIPE_DESCRIPTION_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 100), wxTE_MULTILINE);

    wxBoxSizer* const descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    descriptionSizer->Add(descriptionLabel, wxSizerFlags().Expand().Border(wxALL));
    descriptionSizer->Add(descriptionText, wxSizerFlags().Expand().Border(wxALL));
    descriptionPanel->SetSizer(descriptionSizer);


    directionPanel = new wxPanel(mainPanel, wxID_ANY);
    directionLabel = new wxStaticText(directionPanel, LABEL, wxString("Directions:"), wxDefaultPosition, wxSize(120, 20));
    directionText = new wxTextCtrl(directionPanel, RECIPE_DIRECTIONS_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 300), wxTE_MULTILINE);

    wxBoxSizer* const directionSizer = new wxBoxSizer(wxHORIZONTAL);
    directionSizer->Add(directionLabel, wxSizerFlags().Expand().Border(wxALL));
    directionSizer->Add(directionText, wxSizerFlags().Expand().Border(wxALL));
    directionPanel->SetSizer(directionSizer);

    ingredientsPanel = new wxPanel(mainPanel, wxID_ANY);
    ingredientsLabel = new wxStaticText(ingredientsPanel, LABEL, wxString("Ingredients:"), wxDefaultPosition, wxSize(120, 20));
    listIngredientsInRecipe = new IngredientsInRecipeListCtrl(ingredientsPanel, RECIPE_INGREDIENTS_LIST_CTRL, wxDefaultPosition, wxSize(600, 200), wxLC_REPORT | wxBORDER_THEME | wxLC_SINGLE_SEL);


    wxBoxSizer* const ingredientsSizer = new wxBoxSizer(wxHORIZONTAL);
    ingredientsSizer->Add(ingredientsLabel, wxSizerFlags().Expand().Border(wxALL));
    ingredientsSizer->Add(listIngredientsInRecipe, wxSizerFlags().Expand().Border(wxALL));
    ingredientsPanel->SetSizer(ingredientsSizer);

    wxBoxSizer* const mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(cuisinerecipetypePanel, wxSizerFlags().Expand().Border(wxALL, 10));
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


void RecipeFrame::SetRecipe()
{
    isnew = true;
    newRecipe = Recipe();
    currentRecipe = &newRecipe;
//    typeList = &tList;
    //    for (auto& t : *typeList)
    //        recipetypeComboBox->Append(wxString(t.first));
//    ingredList = &iList;
//    list<string> unitList;
//    GetUnitStringList(unitList);
//    for (list<string>::const_iterator i = unitList.begin(); i != unitList.end(); ++i)
//        yieldUnitComboBox->Append(wxString(i->c_str()));
//    listIngredientsInRecipe->SetParent(this);
//    listIngredientsInRecipe->SetIngredientsInRecipeList(currentRecipe->getAllIngredientsInRecipe());
//    listIngredientsInRecipe->SetIngredientList(*ingredList);
//    listIngredientsInRecipe->ResetListView(wxLC_REPORT);
}

void RecipeFrame::SetRecipe(Recipe& r)
{
    currentRecipe = &r;
}

void RecipeFrame::PassTypeList(list<pair<string, int>>& tList)
{
    typeList = &tList;
}

void RecipeFrame::PassIngredientList(list<Ingredient>& iList)
{
    ingredList = &iList;

}

void RecipeFrame::SetUnitComboBox()
{
    list<string> unitList;
    GetUnitStringList(unitList);
    for (list<string>::const_iterator i = unitList.begin(); i != unitList.end(); ++i)
        yieldUnitComboBox->Append(wxString(i->c_str()));
    yieldUnitComboBox->SetValue("NONE");
}

void RecipeFrame::SetIngredientsInRecipeListCtrl()
{
    listIngredientsInRecipe->SetParent(this);
    listIngredientsInRecipe->SetIngredientsInRecipeList(currentRecipe->getAllIngredientsInRecipe());
    listIngredientsInRecipe->SetIngredientList(*ingredList);
    listIngredientsInRecipe->ResetListView(wxLC_REPORT);
}

void RecipeFrame::RebuildTextFields()
{
    nameText->SetValue(currentRecipe->getName());
    cuisineText->SetValue(currentRecipe->getCuisine());
    recipetypeText->SetValue(currentRecipe->getRecipeType());
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
    parent->SaveRecipes();
}

void RecipeFrame::AddIngredientToRecipe(string& name, float& qty, string& unit)
{
    if (currentRecipe->addIngredientInRecipe(name, qty, unit, *ingredList))
    {
        parent->SaveRecipes();
        listIngredientsInRecipe->ResetListView(wxLC_REPORT);
    }
}

void RecipeFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string nm = string(nameText->GetValue());
    currentRecipe->setName(nm);
    string cu = string(cuisineText->GetValue());
    currentRecipe->setCuisine(cu);
    string mt = string(recipetypeText->GetValue());
    currentRecipe->setRecipeType(mt, *typeList);
//    string mt = string(recipetypeComboBox->GetStringSelection());
    string temp = string(servingsText->GetValue());
    int sc = 0;
    if(!temp.empty() && stringIsDigit(temp))
        sc = stoi(temp);
    currentRecipe->setServingCount(sc);
    temp = string(yieldText->GetValue());
    int yld = 0;
    if (!temp.empty() && stringIsDigit(temp))
        yld = stoi(temp);
    currentRecipe->setYield(yld);
    string yldu = string(yieldUnitComboBox->GetStringSelection());
    currentRecipe->setYieldUnit(yldu);
    string ds = string(descriptionText->GetValue());
    currentRecipe->setDescription(ds);
    string dr = string(directionText->GetValue());
    currentRecipe->setDirection(dr);
    list<IngredientInRecipe> lst;
    currentRecipe->getAllIngredientsInRecipe(lst);
    if (isnew)
    {
        parent->AddNewRecipe(nm, cu, ds, dr, sc, yld, yldu, mt, lst);
        isnew = false;
        this->SetTitle(nm);
    }

    RebuildTextFields();
}

void RecipeFrame::OnAddIngredient(wxCommandEvent& WXUNUSED(e))
{
    addIngredientToRecipe = new AddIngredientToRecipeFrame();
    addIngredientToRecipe->SetParent(this);
    addIngredientToRecipe->PassIngredientList(*ingredList);
    addIngredientToRecipe->SetUnitComboBox();
    addIngredientToRecipe->Show(true);
}

void RecipeFrame::OnRemoveIngredient(wxCommandEvent& WXUNUSED(e))
{
    string i = listIngredientsInRecipe->GetSelectedIngredient();
    currentRecipe->removeIngredientFromRecipe(i);
    listIngredientsInRecipe->ResetListView();
    parent->SaveRecipes();
}

void RecipeFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    // destroy dependents here!
    menuOptions->~wxMenu();
    Destroy();
}


//*************************************************************************************************

// MealFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(MealFrame, wxFrame)
    EVT_MENU(MEAL_ADD_RECIPE, MealFrame::OnAddRecipe)
    EVT_MENU(MEAL_UPDATE, MealFrame::OnUpdate)
    EVT_CLOSE(MealFrame::OnExit)
wxEND_EVENT_TABLE()


//*************************************************************************************************

// MealFrame definition

//*************************************************************************************************

MealFrame::MealFrame(const wxDateTime& dt) : wxFrame(NULL, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(800, 700), wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{

    menuOptions = new wxMenu;
    menuOptions->Append(MEAL_UPDATE, "Update");
    menuOptions->AppendSeparator();
    menuOptions->Append(MEAL_ADD_RECIPE, "Add Recipe");

    menuBar = new wxMenuBar;

    menuBar->Append(menuOptions, "Options");
    SetMenuBar(menuBar);


    mainPanel = new wxPanel(this, LABEL);

    namePanel = new wxPanel(mainPanel, LABEL);
    nameLabel = new wxStaticText(namePanel, LABEL, wxString("Meal Name: "), wxDefaultPosition, wxSize(120, 20));
    nameText = new wxTextCtrl(namePanel, MEAL_NAME_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 20));

    wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(nameLabel, wxSizerFlags().Expand().Border(wxALL));
    nameSizer->Add(nameText, wxSizerFlags().Expand().Border(wxALL));
    namePanel->SetSizer(nameSizer);

    scheduledPanel = new wxPanel(mainPanel, LABEL);
    dateLabel = new wxStaticText(scheduledPanel, LABEL, wxString("Date: "), wxDefaultPosition, wxSize(120, 20));
    datePicker = new wxDatePickerCtrl(scheduledPanel, MEAL_DATE_PICKER, dt, wxDefaultPosition, wxSize(150, 20));
    timeLabel = new wxStaticText(scheduledPanel, LABEL, wxString("Time: "), wxDefaultPosition, wxSize(100, 20));
    timePicker = new wxTimePickerCtrl(scheduledPanel, MEAL_TIME_PICKER, dt, wxDefaultPosition, wxSize(100, 20));

    wxBoxSizer* scheduledSizer = new wxBoxSizer(wxHORIZONTAL);
    scheduledSizer->Add(dateLabel, wxSizerFlags().Expand().Border(wxALL));
    scheduledSizer->Add(datePicker, wxSizerFlags().Expand().Border(wxALL));
    scheduledSizer->Add(timeLabel, wxSizerFlags().Expand().Border(wxALL));
    scheduledSizer->Add(timePicker, wxSizerFlags().Expand().Border(wxALL));
    scheduledPanel->SetSizer(scheduledSizer);

    numberOfServingsIsArchivedPanel = new wxPanel(mainPanel, LABEL);
    numberOfServingsLabel = new wxStaticText(numberOfServingsIsArchivedPanel, LABEL, wxString("Number of Servings:"), wxDefaultPosition, wxSize(120, 20));
    numberOfServingsText = new wxTextCtrl(numberOfServingsIsArchivedPanel, MEAL_NO_OF_SERVINGS, wxEmptyString, wxDefaultPosition, wxSize(50, 20));
    isArchivedLabel = new wxStaticText(numberOfServingsIsArchivedPanel, LABEL, wxString("Is Archived:"), wxDefaultPosition, wxSize(120, 20));
    isArchivedText = new wxTextCtrl(numberOfServingsIsArchivedPanel, LABEL, wxEmptyString, wxDefaultPosition, wxSize(70, 20), wxTE_READONLY);

    wxBoxSizer* NoSIsArchivedSizer = new wxBoxSizer(wxHORIZONTAL);
    NoSIsArchivedSizer->Add(numberOfServingsLabel, wxSizerFlags().Expand().Border(wxALL));
    NoSIsArchivedSizer->Add(numberOfServingsText, wxSizerFlags().Expand().Border(wxALL));
    NoSIsArchivedSizer->Add(isArchivedLabel, wxSizerFlags().Expand().Border(wxALL));
    NoSIsArchivedSizer->Add(isArchivedText, wxSizerFlags().Expand().Border(wxALL));
    numberOfServingsIsArchivedPanel->SetSizer(NoSIsArchivedSizer);

    descriptionPanel = new wxPanel(mainPanel, LABEL);
    descriptionLabel = new wxStaticText(descriptionPanel, LABEL, wxString("Description: "), wxDefaultPosition, wxSize(120, 20));
    descriptionText = new wxTextCtrl(descriptionPanel, MEAL_DESCRIPTION_TEXT_CTRL, wxEmptyString, wxDefaultPosition, wxSize(600, 120), wxTE_MULTILINE);

    wxBoxSizer* descriptionSizer = new wxBoxSizer(wxHORIZONTAL);
    descriptionSizer->Add(descriptionLabel, wxSizerFlags().Expand().Border(wxALL));
    descriptionSizer->Add(descriptionText, wxSizerFlags().Expand().Border(wxALL));
    descriptionPanel->SetSizer(descriptionSizer);

    recipesListCtrlPanel = new wxPanel(mainPanel, LABEL);
    recipesListLabel = new wxStaticText(recipesListCtrlPanel, LABEL, wxString("Recipes:"), wxDefaultPosition, wxSize(120, 20));
    recipesListCtrl = new wxListCtrl(recipesListCtrlPanel, MEAL_RECIPE_LIST_CTRL, wxDefaultPosition, wxSize(600, 200));

    wxBoxSizer* recipeListCtrlSizer = new wxBoxSizer(wxHORIZONTAL);
    recipeListCtrlSizer->Add(recipesListLabel, wxSizerFlags().Expand().Border(wxALL));
    recipeListCtrlSizer->Add(recipesListCtrl, wxSizerFlags().Expand().Border(wxALL));
    recipesListCtrlPanel->SetSizer(recipeListCtrlSizer);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(namePanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(scheduledPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(numberOfServingsIsArchivedPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(descriptionPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(recipesListCtrlPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);

    SetClientSize(mainPanel->GetMaxSize());
}

//*************************************************************************************************

// MealFrame function definition

//*************************************************************************************************


void MealFrame::SetParent(MealPlannerFrame* p)
{
    parent = p;
}

void MealFrame::SetMeal(Meal& currentMeal)
{
    this->currentMeal = &currentMeal;    
    SetFrameTitle(this->currentMeal->getScheduled().FormatDate(), this->currentMeal->getName(), this->currentMeal->getID());

}

void MealFrame::SetMeal()
{
    this->SetTitle("New Meal");
    isnew = true;
    newMeal = Meal();
    currentMeal = &newMeal;
}

void MealFrame::SetFrameTitle(wxString date, wxString nm, unsigned short id)
{
    this->SetTitle(date + "  ::  " + nm + "  ::  Meal# " + wxString(to_string(id)));
}

void MealFrame::PassRecipes(list<Recipe>* lst)
{
    recipes = lst;
}

void MealFrame::ResetTextFields()
{
    nameText->SetValue(currentMeal->getName());
    datePicker->SetValue(currentMeal->getScheduled());
    timePicker->SetValue(currentMeal->getScheduled());
    descriptionText->SetValue(currentMeal->getDescription());
    numberOfServingsText->SetValue(to_string(currentMeal->getNumberOfServings()));
    isArchivedText->SetValue(wxString(to_string(currentMeal->isMealArchived())));
}

void MealFrame::RebuildList()
{
    // rebuild the list of recipes associated with this meal object.
}

void MealFrame::OnAddRecipe(wxCommandEvent& WXUNUSED(e))
{

}

void MealFrame::OnUpdate(wxCommandEvent& WXUNUSED(e))
{
    string nm = string(nameText->GetValue());
    currentMeal->setName(nm);

    // Add check to see if date is a valid date.
    // Or set the bounds of available date and time from wxDateTime::Now() and forward.
    wxDateTime dtp = datePicker->GetValue();
    wxDateTime tmp = timePicker->GetValue();
    tmp.SetYear(dtp.GetYear());
    tmp.SetMonth(dtp.GetMonth());
    tmp.SetDay(dtp.GetDay());

    bool moveMeal = false;  // determines if meal should be moved in list<Meals> in parent due to time change.
    if (!tmp.IsEqualTo(currentMeal->getScheduled()))
        moveMeal = true;

    currentMeal->setScheduled(tmp);
    string ds = string(descriptionText->GetValue());
    currentMeal->setDescription(ds);
    int ns = atoi(numberOfServingsText->GetValue());
    currentMeal->setNumberOfServings(ns);
    bool ia;
    (string(isArchivedText->GetValue()) == "True" ? ia = true : ia = false);
    currentMeal->setIsArchived(ia);
    list<Recipe> rec;
//    currentMeal->getRecipeListInMeal(rec);
    if (isnew == true)
    {
        parent->AddMealToList(nm, ds, tmp, ns, ia, rec);
        ResetTextFields();
        isnew = false;
    }
    else    // move to appropriate place in list if needed.
    {
        if (moveMeal)
            parent->MoveMealInList(currentMeal->getID());
    }
    SetFrameTitle(currentMeal->getScheduled().FormatDate(), currentMeal->getName(), currentMeal->getID());
    parent->MealUpdated();
}

void MealFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    Destroy();
}

//*************************************************************************************************

// MealPlannerFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(MealPlannerFrame, wxFrame)
EVT_MENU(MEAL_PLANNER_ADD_MEAL, MealPlannerFrame::OnAddMeal)
EVT_MENU(MEAL_PLANNER_EDIT_MEAL, MealPlannerFrame::OnEditMeal)
EVT_LIST_ITEM_ACTIVATED(MEAL_PLANNER_CALENDAR_DAY, MealPlannerFrame::OnActivated)
EVT_LIST_ITEM_SELECTED(MEAL_PLANNER_CALENDAR_DAY, MealPlannerFrame::OnSelected)
EVT_CALENDAR_SEL_CHANGED(CALENDAR_SIDE_PANEL, MealPlannerFrame::OnChangeDate)
EVT_CLOSE(MealPlannerFrame::OnExit)
wxEND_EVENT_TABLE()

//*************************************************************************************************

// MealPlannerFrame definition

//*************************************************************************************************

MealPlannerFrame::MealPlannerFrame() : wxFrame(NULL, wxID_ANY, wxString("Meal Planner"), wxDefaultPosition, wxSize(1250, 1000), wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
    menuOptions = new wxMenu;
    menuOptions->Append(MEAL_PLANNER_ADD_MEAL, "Add New Meal");
    menuOptions->Append(MEAL_PLANNER_EDIT_MEAL, "Edit Selected Meal");

    menuView = new wxMenu;
    menuView->Append(MEAL_PLANNER_CALENDAR_MONTHLY_VIEW, "Monthly View");
    menuView->Append(MEAL_PLANNER_CALENDAR_WEEKLY_VIEW, "Weekly View");
    menuView->Append(MEAL_PLANNER_CALENDAR_DAILY_VIEW, "Daily View");

    // make calendar monthly view unselectable since it starts by default.
    menuView->Enable(MEAL_PLANNER_CALENDAR_MONTHLY_VIEW, false);

    menuBar = new wxMenuBar;
    menuBar->Append(menuOptions, "Options");
    menuBar->Append(menuView, "View");
    SetMenuBar(menuBar);

    selectedDate = wxDateTime::Today();   // set selectedDate to current date which = wxDefaultDateTime.

    mainPanel = new wxPanel(this, wxID_ANY);
    leftPanel = new wxPanel(mainPanel, wxID_ANY);
    rightPanel = new wxPanel(mainPanel, wxID_ANY);

    // setup the left side calendar display.
    sideCalendar = new wxCalendarCtrl(leftPanel, CALENDAR_SIDE_PANEL, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize);
//    sideCalendar->SetDateRange();
    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
    leftSizer->Add(sideCalendar);
    leftPanel->SetSizer(leftSizer);

    // setup the header of the right side display, starting with today's date
    headerPanel = new wxPanel(rightPanel, wxID_ANY);
    headerLabel = new wxTextCtrl(headerPanel, wxID_ANY, wxString(selectedDate.GetWeekDayName(selectedDate.GetWeekDay())) + wxString(",  ") + selectedDate.GetEnglishMonthName(selectedDate.GetCurrentMonth()) + wxString("  " + to_string(selectedDate.GetDay())) + wxString(",  " + to_string(selectedDate.GetCurrentYear())), wxDefaultPosition, wxSize(840, 30), wxTE_READONLY | wxTE_CENTRE);
    
    wxBoxSizer* headerSizer = new wxBoxSizer(wxVERTICAL);
    headerSizer->Add(headerLabel);
    headerPanel->SetSizer(headerSizer);

    // setup the right side list box display for today's date.
    calendarDisplayPanel = new wxPanel(rightPanel, wxID_ANY);
    calendarTableDaily = new wxListCtrl(calendarDisplayPanel, MEAL_PLANNER_CALENDAR_DAY, wxDefaultPosition, wxSize(840, 750), wxLC_REPORT);
    InitializeCalendarTableDaily();
    ToggleMenuToCalendarDailyOptions();

    wxBoxSizer* calDisSizer = new wxBoxSizer(wxVERTICAL);
    calDisSizer->Add(calendarTableDaily);
    calendarDisplayPanel->SetSizer(calDisSizer);

    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
    rightSizer->Add(headerPanel);
    rightSizer->Add(calendarDisplayPanel);
    rightPanel->SetSizer(rightSizer);


    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(leftPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainSizer->Add(rightPanel, wxSizerFlags().Expand().Border(wxALL, 10));
    mainPanel->SetSizer(mainSizer);


    currentView = MEAL_PLANNER_CALENDAR_DAILY_VIEW;
//    RebuildCalendarView();
    
}

//*************************************************************************************************

// MealPlannerFrame function definition

//*************************************************************************************************

void MealPlannerFrame::SetParent(MainListCtrl* p)
{
    parent = p;
}

void MealPlannerFrame::SetMealList(list<Meal>* lst)
{
    meals = lst;
}

void MealPlannerFrame::SetRecipeList(std::list<Recipe>* lst)
{
    recipeList = lst;
}

void MealPlannerFrame::SetupSideCalendar()
{
    // calendar object off to the side to handle some calendar events.
    sideCalendar = new wxCalendarCtrl(leftPanel, CALENDAR_SIDE_PANEL, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize);

    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
    leftSizer->Add(sideCalendar);
    leftPanel->SetSizer(leftSizer);
}

void MealPlannerFrame::SetupDailyHeader()
{
    // we want Month day, year
    headerPanel = new wxPanel(rightPanel, wxID_ANY);
    headerLabel = new wxTextCtrl(headerPanel, wxID_ANY, wxString(selectedDate.GetWeekDayName(selectedDate.GetWeekDay())) + wxString(",  " + selectedDate.GetEnglishMonthName(selectedDate.GetMonth())) + wxString("  " + to_string(selectedDate.GetDay())) + wxString(",  " + to_string(selectedDate.GetYear())), wxDefaultPosition, wxSize(840, 30), wxTE_READONLY | wxTE_CENTRE);
}

void MealPlannerFrame::SetupDailyView()
{
    calendarDisplayPanel = new wxPanel(rightPanel, wxID_ANY);
    calendarTableDaily = new wxListCtrl(calendarDisplayPanel, MEAL_PLANNER_CALENDAR_DAY, wxDefaultPosition, wxSize(840, 750), wxLC_REPORT);
}

/*
void MealPlannerFrame::SetupWeekDayHeader()
{
    // set month display panel 
    monthPanel = new wxPanel(rightPanel, wxID_ANY);
    monthLabel = new wxTextCtrl(monthPanel, wxID_ANY, selectedDate.GetEnglishMonthName(selectedDate.GetCurrentMonth()) + wxString("  " + to_string(selectedDate.GetCurrentYear())), wxDefaultPosition, wxSize(840, 30), wxTE_READONLY | wxTE_CENTRE);

    // set weekly header panel.
    calendarWeekDayHeaderPanel = new wxPanel(rightPanel, wxID_ANY);
    wxBoxSizer* calendarWeeklyHeaderSizer = new wxBoxSizer(wxHORIZONTAL);
    sundayLabel = new wxTextCtrl(calendarWeekDayHeaderPanel, wxID_ANY, wxString("Sunday"), wxDefaultPosition, wxSize(120, 30), wxTE_READONLY | wxTE_CENTRE);
    mondayLabel = new wxTextCtrl(calendarWeekDayHeaderPanel, wxID_ANY, wxString("Monday"), wxDefaultPosition, wxSize(120, 30), wxTE_READONLY | wxTE_CENTRE);
    tuesdayLabel = new wxTextCtrl(calendarWeekDayHeaderPanel, wxID_ANY, wxString("Tuesday"), wxDefaultPosition, wxSize(120, 30), wxTE_READONLY | wxTE_CENTRE);
    wednesdayLabel = new wxTextCtrl(calendarWeekDayHeaderPanel, wxID_ANY, wxString("Wednesday"), wxDefaultPosition, wxSize(120, 30), wxTE_READONLY | wxTE_CENTRE);
    thursdayLabel = new wxTextCtrl(calendarWeekDayHeaderPanel, wxID_ANY, wxString("Thursday"), wxDefaultPosition, wxSize(120, 30), wxTE_READONLY | wxTE_CENTRE);
    fridayLabel = new wxTextCtrl(calendarWeekDayHeaderPanel, wxID_ANY, wxString("Friday"), wxDefaultPosition, wxSize(120, 30), wxTE_READONLY | wxTE_CENTRE);
    saturdayLabel = new wxTextCtrl(calendarWeekDayHeaderPanel, wxID_ANY, wxString("Saturday"), wxDefaultPosition, wxSize(120, 30), wxTE_READONLY | wxTE_CENTRE);
    calendarWeeklyHeaderSizer->Add(sundayLabel);
    calendarWeeklyHeaderSizer->Add(mondayLabel);
    calendarWeeklyHeaderSizer->Add(tuesdayLabel);
    calendarWeeklyHeaderSizer->Add(wednesdayLabel);
    calendarWeeklyHeaderSizer->Add(thursdayLabel);
    calendarWeeklyHeaderSizer->Add(fridayLabel);
    calendarWeeklyHeaderSizer->Add(saturdayLabel);
    calendarWeekDayHeaderPanel->SetSizer(calendarWeeklyHeaderSizer);

}*/

/*
void MealPlannerFrame::SetupMonthlyGrid()
{

    // 5 by 7 grid of list controllers with day of the month as column labels.
    // thought, make calendarMonthlyDisplayPanel a wxScrolledWindow ??  does not seem feasible at this point in time..
    calendarMonthlyDisplayPanel = new wxPanel(rightPanel, wxID_ANY);
    wxBoxSizer* calMonDisPanSizer = new wxBoxSizer(wxVERTICAL);

    for (int y = 0; y < 5; y++)
    {
        vector<wxListBox*> vectorY;
        for (int x = 0; x < 7; x++)
        {
            wxListBox* dayInMonth = new wxListBox(calendarMonthlyDisplayPanel, wxID_ANY, wxPoint((x - 1) * 120, (y - 1) * 120), wxSize(120, 150), wxArrayString(), wxLB_SINGLE | wxLB_NEEDED_SB);
            vectorY.push_back(dayInMonth);
        }
        calendarTableMonthly.push_back(vectorY);
    }

}*/

void MealPlannerFrame::ToggleMenuToCalendarDailyOptions()
{
    menuView->Enable(MEAL_PLANNER_CALENDAR_MONTHLY_VIEW, true);
    menuView->Enable(MEAL_PLANNER_CALENDAR_WEEKLY_VIEW, true);
    menuView->Enable(MEAL_PLANNER_CALENDAR_DAILY_VIEW, false);
}

void MealPlannerFrame::RebuildCalendarView()
{
    switch (currentView)
    {
    case MEAL_PLANNER_CALENDAR_DAILY_VIEW:
        BuildDailyCalendarView();
        break;

    case MEAL_PLANNER_CALENDAR_MONTHLY_VIEW:
        break;

    default:
        BuildDailyCalendarView();
        break;
    }
}

void MealPlannerFrame::InitializeCalendarTableDaily()
{

    wxListItem col;
    col.SetText("Meal Time");
    col.SetImage(-1);
    calendarTableDaily->InsertColumn(0, col);
    col.SetText("Meal ID");
    calendarTableDaily->InsertColumn(1, col);
    col.SetText("Meal Name");
    calendarTableDaily->InsertColumn(2, col);
    col.SetText("Servings");
    calendarTableDaily->InsertColumn(3, col);
}


void MealPlannerFrame::InsertItemsInDailyListDisplay(Meal& m, int& i)
{
    wxString str;
    str = wxString(m.getScheduled().FormatTime());
    long temp = calendarTableDaily->InsertItem(i, str);
    calendarTableDaily->SetItemData(temp, i);

    str = wxString(to_string(m.getID()));
    calendarTableDaily->SetItem(temp, 1, str);

    str = wxString(m.getName());
    calendarTableDaily->SetItem(temp, 2, str);

    str = wxString(to_string(m.getNumberOfServings()));
    calendarTableDaily->SetItem(temp, 3, str);
}

void MealPlannerFrame::BuildDailyCalendarView()
{
    // first, change the monthLabel to current month using selectedDate object, then display
    // second, setup calendarWeekDayHeaderPanel for Sunday through Saturday, then display
    // third, setup grid for for month view with saved meal objects.
//    rightPanel->SetSizer(NULL);
//    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
//    rightSizer->Add(headerPanel);
//    rightSizer->Add(calendarTableDaily);
//    rightPanel->SetSizer(rightSizer);

    headerLabel->SetValue(wxString(selectedDate.GetWeekDayName(selectedDate.GetWeekDay())) 
        + wxString(",  " + selectedDate.GetEnglishMonthName(selectedDate.GetMonth()))          
        + wxString("  " + to_string(selectedDate.GetDay())) 
        + wxString(",  " + to_string(selectedDate.GetYear())));

    calendarTableDaily->Hide();
    calendarTableDaily->DeleteAllItems();
    // populate the list with the meal information.
    int i = -1;

    for (auto& meal : *meals)
    {
        if (meal.getScheduled().GetDateOnly() == selectedDate.GetDateOnly())
        {
            i++;
            InsertItemsInDailyListDisplay(meal, i);
        }
    }

    calendarTableDaily->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    calendarTableDaily->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    calendarTableDaily->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);

    calendarTableDaily->Show();


}

/*
void MealPlannerFrame::BuildMonthlyCalendarView()
{
    // first, change the monthLabel to current month using selectedDate object, then display
    // second, setup calendarWeekDayHeaderPanel for Sunday through Saturday, then display
    // third, setup grid for for month view with saved meal objects.
    rightPanel->SetSizer(NULL);
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
    rightSizer->Add(monthPanel);
    rightSizer->Add(calendarWeekDayHeaderPanel);
    rightSizer->Add(calendarMonthlyDisplayPanel);
    rightPanel->SetSizer(rightSizer);

    // since we are toggling to monthly view from another view, enable/disable appropriate items in menuView.
    menuView->Enable(MEAL_PLANNER_CALENDAR_MONTHLY_VIEW, false);
    menuView->Enable(MEAL_PLANNER_CALENDAR_WEEKLY_VIEW, true);
    menuView->Enable(MEAL_PLANNER_CALENDAR_DAILY_VIEW, true);
}*/

void MealPlannerFrame::MealUpdated()
{
    parent->SaveMeals();
    RebuildCalendarView();
}

void MealPlannerFrame::AddMealToList(string& nm, string& ds, wxDateTime& sch, int& noSer, bool& isArc, list<Recipe>& reclist)
{
    unsigned short newID = getHighestID(*meals) + 1;
    if (addMeal(newID, nm, ds, sch, noSer, isArc, reclist, *meals))
    {
        selectedDate.SetYear(sch.GetYear());
        selectedDate.SetMonth(sch.GetMonth());
        selectedDate.SetDay(sch.GetDay());
        mealFrame->SetMeal(getMealInList(newID, *meals));
        
    }
}


void MealPlannerFrame::MoveMealInList(unsigned short id)
{
    moveMeal(id, *meals);
}


void MealPlannerFrame::OnChangeDate(wxCalendarEvent& WXUNUSED(e))
{   
    wxDateTime temp = sideCalendar->GetDate();
    selectedDate.SetYear(temp.GetYear());
    selectedDate.SetMonth(temp.GetMonth());
    selectedDate.SetDay(temp.GetDay());
    selectedMeal = Meal();
    RebuildCalendarView();
}

void MealPlannerFrame::OnAddMeal(wxCommandEvent& WXUNUSED(e))
{
    mealFrame = new MealFrame(selectedDate);
    mealFrame->SetParent(this);
    mealFrame->SetMeal();
    mealFrame->PassRecipes(recipeList);
    mealFrame->Show();
}

void MealPlannerFrame::OnEditMeal(wxCommandEvent& WXUNUSED(e))
{
    mealFrame = new MealFrame(selectedDate);
    mealFrame->SetParent(this);
    mealFrame->SetMeal(selectedMeal);
    mealFrame->ResetTextFields();
    mealFrame->PassRecipes(recipeList);
    mealFrame->Show();
}


void MealPlannerFrame::OnActivated(wxListEvent& e)
{
    wxListItem info;
    info.m_itemId = e.m_itemIndex;  // getting the index of the selected item.
    info.m_col = 0;                 // get the first column information, or the name of the recipe/ingredient/category
                                    // designed to be unduplicated values and to not be reliant on indexing when lists are sorted.

    info.m_mask = wxLIST_MASK_TEXT;
    if (calendarTableDaily->GetItem(info))
    {
        unsigned short id = (unsigned short)strtoul(string(info.m_text).c_str(), nullptr, 0);
        selectedMeal = getMealInList(id, *meals);
    }

    mealFrame = new MealFrame(selectedDate);
    mealFrame->SetParent(this);
    mealFrame->SetMeal(selectedMeal);
    mealFrame->ResetTextFields();
    mealFrame->PassRecipes(recipeList);
    mealFrame->Show();
}


void MealPlannerFrame::OnSelected(wxListEvent& e)
{
    wxListItem info;
    info.m_itemId = e.m_itemIndex;  // getting the index of the selected item.
    info.m_col = 1;                 // get the second column information, or the id of the meal                                    
    info.m_mask = wxLIST_MASK_TEXT;
    if (calendarTableDaily->GetItem(info))
    {
        unsigned short id = (unsigned short)strtoul(string(info.m_text).c_str(), nullptr, 0);
        selectedMeal = getMealInList(id, *meals);
    }
    else
        wxFAIL_MSG("wxListCtrl::GetItem() failed");
}

void MealPlannerFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
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

// Done in ListMgrFrame object.


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

    str = wxString(r.getRecipeType());
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

void MainListCtrl::SetParent(ListMgrFrame* p)
{
    parent = p;
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

void MainListCtrl::SaveMeals()
{
    saveMealList(mealFile, meals);
}

// Loads the list of user created categories, ingredients, and recipes from csv files
void MainListCtrl::LoadLists()
{
    // load lists.
    loadCategoryList(categoryFile, categories);
    loadIngredientList(ingredFile, ingredients, categories);
    loadRecipeList(recipeFile, recipes, ingredients, recipetypes);
    loadMealList(mealFile, meals, recipes);
}

void MainListCtrl::AddNewCategory(string& name)
{
    if (addCategory(name, categories))
    {
        SaveCategories();
        ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
        parent->MessageSuccess("New Cateogry " + name + " has been created!");
    }
    else
        parent->MessageFailure("Unable to create new Category!  verify all fields are filled out appropriately!");
}

void MainListCtrl::AddNewIngredient(string& name, string& desc, string& cat)
{
    if (addIngredient(name, desc, getCategoryInList(cat, categories), ingredients))
    {
        SaveIngredients();
        ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
        parent->MessageSuccess("New Ingredient " + name + " has been created!");
    }
    else
        parent->MessageFailure("Unable to create new Ingredient!  verify all fields are filled out appropriately!");
}

void MainListCtrl::AddNewRecipe(string& name, string& cuisine, string& description, string& direction, int& servingCount, int& yield, string& yieldUnit, string& recipetype, list<IngredientInRecipe>& ingredients)
{
    if (addRecipe(name, cuisine, description, direction, servingCount, yield, yieldUnit, recipetype, recipetypes, recipes))
    {
        SaveRecipes();
        ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
        recipeFrame->SetRecipe(getRecipeInList(name, recipes));
        parent->MessageSuccess("New Recipe " + name + " has been created!");
    }
    else
        parent->MessageFailure("Unable to create new Recipe!  verify all fields are filled out appropriately!");
}

void MainListCtrl::RemoveCategory()
{
    string cat = selectedCategory->getName();
    if (removeCategory(cat, categories))
    {
        SaveRecipes();
        ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

void MainListCtrl::RemoveIngredient()
{
    string ing = selectedIngredient->getName();
    if (removeIngredient(ing, ingredients))
    {
        SaveIngredients();
        ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

void MainListCtrl::RemoveRecipe()
{
    string rec = selectedRecipe->getName();
    if (removeRecipe(rec, recipes))
    {
        SaveRecipes();
        ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
    }
}

void MainListCtrl::CreateNewCategory()
{
    addCategoryFrame = new AddCategoryFrame();
    addCategoryFrame->SetParent(this);
    addCategoryFrame->Show();
}

void MainListCtrl::CreateNewIngredient()
{
    addIngredientFrame = new AddIngredientFrame();
    addIngredientFrame->SetParent(this);
    list<string> names;
    for (auto& c : categories)
        names.push_back(c.getName());
    addIngredientFrame->SetCategoryComboBox(names);
    addIngredientFrame->Show();
}

void MainListCtrl::CreateNewRecipe()
{
    recipeFrame = new RecipeFrame("Create New Recipe");
    recipeFrame->SetRecipe();
    recipeFrame->SetParent(this);
    recipeFrame->PassTypeList(recipetypes);
    recipeFrame->PassIngredientList(ingredients);
    recipeFrame->SetIngredientsInRecipeListCtrl();
    recipeFrame->SetUnitComboBox();
    recipeFrame->Show(true);
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
void MainListCtrl::ResetListView(long custFlags, long wxFlags, bool withText)
{

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

    col.SetText("Recipe Type");
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

void MainListCtrl::OpenPlanner()
{
    mealPlannerFrame = new MealPlannerFrame();
    mealPlannerFrame->SetParent(this);
    mealPlannerFrame->SetMealList(&meals);
    mealPlannerFrame->SetRecipeList(&recipes);
    mealPlannerFrame->RebuildCalendarView();
    mealPlannerFrame->Show();
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
        recipeFrame->SetRecipe(*selectedRecipe);
        recipeFrame->SetParent(this);
        recipeFrame->PassTypeList(recipetypes);
        recipeFrame->PassIngredientList(ingredients);
        recipeFrame->SetIngredientsInRecipeListCtrl();
        recipeFrame->SetUnitComboBox();
        recipeFrame->RebuildTextFields();
        recipeFrame->Show(true);

        break;
    case INGREDIENT_LIST_REPORT_DISPLAY:
        // here we open an ingredient Frame, make it the primary window, and populate fields with the ingredient information we have clicked on.

        ingredientFrame = new IngredientFrame(selectedIngredient->getName());
        ingredientFrame->SetIngredient(*selectedIngredient);
        ingredientFrame->SetParent(this);
        ingredientFrame->PassCategoryList(categories);
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
        d.ShowModal();
        break;
    }
}


//*************************************************************************************************

// ListMgrFrame Event Table

//*************************************************************************************************

wxBEGIN_EVENT_TABLE(ListMgrFrame, wxFrame)
EVT_MENU(ABOUT, ListMgrFrame::OnAbout)
EVT_CLOSE(ListMgrFrame::OnExit)

EVT_MENU(RECIPE_LIST_REPORT_DISPLAY, ListMgrFrame::OnRecipeListReportDisplay)
EVT_MENU(INGREDIENT_LIST_REPORT_DISPLAY, ListMgrFrame::OnIngredientListReportDisplay)
EVT_MENU(CATEGORY_LIST_REPORT_DISPLAY, ListMgrFrame::OnCategoryListReportDisplay)


EVT_MENU(CATEGORY_ADD_NEW, ListMgrFrame::OnAddCategory)
EVT_MENU(CATEGORY_REMOVE_SELECTED, ListMgrFrame::OnRemoveCategory)
EVT_MENU(INGREDIENT_ADD_NEW, ListMgrFrame::OnAddIngredient)
EVT_MENU(INGREDIENT_REMOVE_SELECTED, ListMgrFrame::OnRemoveIngredient)
EVT_MENU(RECIPE_ADD_NEW, ListMgrFrame::OnAddRecipe)
EVT_MENU(RECIPE_REMOVE_SELECTED, ListMgrFrame::OnRemoveRecipe)

EVT_MENU(MEAL_PLANNER_DISPLAY, ListMgrFrame::OnOpenPlanner)
wxEND_EVENT_TABLE()

//*************************************************************************************************

// ListMgrFrame definition

//*************************************************************************************************

ListMgrFrame::ListMgrFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 500), wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCAPTION|wxCLOSE_BOX|wxCLIP_CHILDREN)
{

    // File menu
    menuFile = new wxMenu;
    menuFile->Append(ABOUT, "About");
    menuFile->AppendSeparator();


    // List menu
    menuList = new wxMenu;
    menuList->Append(RECIPE_LIST_REPORT_DISPLAY, "Display Recipe List");
    menuList->Append(RECIPE_ADD_NEW, "Create Recipe");
    menuList->Append(RECIPE_REMOVE_SELECTED, "Remove Selected Recipe");
    menuList->AppendSeparator();
    menuList->Append(INGREDIENT_LIST_REPORT_DISPLAY, "Display Ingredient List");
    menuList->Append(INGREDIENT_ADD_NEW, "Create Ingredient");
    menuList->Append(INGREDIENT_REMOVE_SELECTED, "Remove Selected Ingredient");
    menuList->AppendSeparator();
    menuList->Append(CATEGORY_LIST_REPORT_DISPLAY, "Display Category List");
    menuList->Append(CATEGORY_ADD_NEW, "Create Category");
    menuList->Append(CATEGORY_REMOVE_SELECTED, "Remove Selected Category");

    // recipe list editor menu enabled, disable other options
    SetRecipeListOptions();
   

    // Define Menu Planner
    menuCalendar = new wxMenu;
    menuCalendar->Append(MEAL_PLANNER_DISPLAY, "Open Planner");


    // Menu Bar
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "File");
    menuBar->Append(menuList, "Lists");
    menuBar->Append(menuCalendar, "Meal Planner");
    SetMenuBar(menuBar);

    panel = new wxPanel(this, wxID_ANY);

    // default startup of list display to 
    listController = new MainListCtrl(panel, MAIN_LIST_CTRL, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxBORDER_THEME | wxLC_SINGLE_SEL);
    listController->SetParent(this);
    listController->LoadLists();
    listController->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);

    wxBoxSizer* const sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(listController, wxSizerFlags(2).Expand().Border(wxALL, 10));
    panel->SetSizer(sizer);

    SetClientSize(panel->GetMaxSize());
}

//*************************************************************************************************

// ListMgrFrame function definitions

//*************************************************************************************************

void ListMgrFrame::SetParent(RecipeApp* p)
{
    parent = p;
}

void ListMgrFrame::SetRecipeListOptions()
{

    menuList->Enable(RECIPE_LIST_REPORT_DISPLAY, false);
    menuList->Enable(RECIPE_ADD_NEW, true);
    menuList->Enable(RECIPE_REMOVE_SELECTED, true);
    menuList->Enable(INGREDIENT_LIST_REPORT_DISPLAY, true);
    menuList->Enable(INGREDIENT_ADD_NEW, false);
    menuList->Enable(INGREDIENT_REMOVE_SELECTED, false);
    menuList->Enable(CATEGORY_LIST_REPORT_DISPLAY, true);
    menuList->Enable(CATEGORY_ADD_NEW, false);
    menuList->Enable(CATEGORY_REMOVE_SELECTED, false);
}

void ListMgrFrame::SetIngredientListOptions()
{

    menuList->Enable(RECIPE_LIST_REPORT_DISPLAY, true);
    menuList->Enable(RECIPE_ADD_NEW, false);
    menuList->Enable(RECIPE_REMOVE_SELECTED, false);
    menuList->Enable(INGREDIENT_LIST_REPORT_DISPLAY, false);
    menuList->Enable(INGREDIENT_ADD_NEW, true);
    menuList->Enable(INGREDIENT_REMOVE_SELECTED, true);
    menuList->Enable(CATEGORY_LIST_REPORT_DISPLAY, true);
    menuList->Enable(CATEGORY_ADD_NEW, false);
    menuList->Enable(CATEGORY_REMOVE_SELECTED, false);
}

void ListMgrFrame::SetCategoryListOptions()
{

    menuList->Enable(RECIPE_LIST_REPORT_DISPLAY, true);
    menuList->Enable(RECIPE_ADD_NEW, false);
    menuList->Enable(RECIPE_REMOVE_SELECTED, false);
    menuList->Enable(INGREDIENT_LIST_REPORT_DISPLAY, true);
    menuList->Enable(INGREDIENT_ADD_NEW, false);
    menuList->Enable(INGREDIENT_REMOVE_SELECTED, false);
    menuList->Enable(CATEGORY_LIST_REPORT_DISPLAY, false);
    menuList->Enable(CATEGORY_ADD_NEW, true);
    menuList->Enable(CATEGORY_REMOVE_SELECTED, true);
}

void ListMgrFrame::OnAbout(wxCommandEvent& WXUNUSED(e))
{
    wxMessageDialog dialog(this, "Recipe Manager System\nsp1222 (c) 2021", "About Recipe Manager");
    dialog.ShowModal();
}

void ListMgrFrame::OnExit(wxCloseEvent& WXUNUSED(e))
{
    listController->SaveAllLists();
    // release data, prevent memory leaks
    menuList->~wxMenu();
    parent->Exit();
    Destroy();
}

void ListMgrFrame::OnRecipeListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the recipe list.
    listController->ResetListView(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
    SetRecipeListOptions();
}

void ListMgrFrame::OnIngredientListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the ingredient list.
    listController->ResetListView(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
    SetIngredientListOptions();
}

void ListMgrFrame::OnCategoryListReportDisplay(wxCommandEvent& WXUNUSED(e))
{
    // here we clear the current listController and display the category list.
    listController->ResetListView(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
    SetCategoryListOptions();
}

void ListMgrFrame::OnAddCategory(wxCommandEvent& WXUNUSED(e))
{
    listController->CreateNewCategory();    
}

void ListMgrFrame::OnRemoveCategory(wxCommandEvent& e)
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

void ListMgrFrame::OnAddIngredient(wxCommandEvent& WXUNUSED(e))
{
    listController->CreateNewIngredient();
    
}

void ListMgrFrame::OnRemoveIngredient(wxCommandEvent& e)
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

void ListMgrFrame::OnAddRecipe(wxCommandEvent& e)
{
    listController->CreateNewRecipe();
}

void ListMgrFrame::OnRemoveRecipe(wxCommandEvent& e)
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

void ListMgrFrame::OnOpenPlanner(wxCommandEvent& WXUNUSED(e))
{
    listController->OpenPlanner();
}

void ListMgrFrame::MessageSuccess(string msg)
{
    wxMessageDialog d(nullptr, msg, "Success");
    d.ShowModal();
}

void ListMgrFrame::MessageFailure(string msg)
{
    wxMessageDialog d(nullptr, msg, "Failure");
    d.ShowModal();
}