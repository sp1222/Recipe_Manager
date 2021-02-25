#include "RecipeApp.h"

//*************************************************************************************************
// RecipeApp definition

wxIMPLEMENT_APP(RecipeApp);
bool RecipeApp::OnInit()
{
    MainFrame* Main = new MainFrame(_("Recipe Manager App"));
    Main->Show(true);
    SetTopWindow(Main);
    return true;
}


//*************************************************************************************************
// ListCtrl definition


//*************************************************************************************************
// ListCtrl function definitions

void ListCtrl::InsertItemInRecipeListReportDisplay(Recipe& r, int& i)
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

void ListCtrl::InsertItemInIngredientListReportDisplay(Ingredient& n, int& i)
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

void ListCtrl::InsertItemInCategoryListReportDisplay(Category& c, int& i)
{
    wxString str;
    str = wxString(c.getCategory());
    long temp = InsertItem(i, str);
    SetItemData(temp, i);

    str = wxString(to_string(c.getIngredientsUsingCategoryCount()));
    SetItem(temp, 1, str);
}

//*************************************************************************************************
// MainFrame Event Table

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

MainFrame::MainFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 500))
{
    // load lists.
    loadCategoryList(catFile, categories);
    loadIngredientList(ingredFile, ingredients, categories);
    loadRecipeList(recipeFile, recipes, ingredients, mealTypes);

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

    RebuildList(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);

    wxBoxSizer* const sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(listController, wxSizerFlags(2).Expand().Border());
    panel->SetSizer(sizer);

    SetClientSize(panel->GetBestSize());
}


//*************************************************************************************************
// MainFrame function definitions

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
    RebuildList(RECIPE_LIST_REPORT_DISPLAY, wxLC_REPORT);
}

void MainFrame::OnIngredientListReportDisplay(wxCommandEvent& e)
{
    // here we clear the current listController and display the ingredient list.
    RebuildList(INGREDIENT_LIST_REPORT_DISPLAY, wxLC_REPORT);
}

void MainFrame::OnCategoryListReportDisplay(wxCommandEvent& e)
{
    // here we clear the current listController and display the category list.
    RebuildList(CATEGORY_LIST_REPORT_DISPLAY, wxLC_REPORT);
}

void MainFrame::RebuildList(long custFlags, long wxFlags, bool withText)
{
#if 0
    if (!listController || ((flags & wxLC_VIRTUAL) 1 = (listController->GetWindowStyleFlag() & wxLC_VIRTUAL)))
#endif
    {
        wxListCtrl* const old = listController;
        listController = new ListCtrl(panel, LIST_CTRL, wxDefaultPosition, wxDefaultSize, wxFlags | wxBORDER_THEME | wxLC_SINGLE_SEL);

        if (old)
        {
            wxSizer* const sizer = panel->GetSizer();
            sizer->Replace(old, listController);
            delete old;
            sizer->Layout();
        }

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
//        wxMenuBar* const mb = GetMenuBar();
//        if (mb)
//            listController->EnableBellOnNoMatch(mb->IsChecked(LIST_TOGGLE_BELL));
    }
//    GetMenuBar()->Check(LIST_ROW_LINES, false);
}

void MainFrame::BuildRecipeListReportDisplay()
{
    wxListItem col;
    col.SetText("Recipe Name");
    col.SetImage(-1);
    listController->InsertColumn(0, col);

    col.SetText("Meal Type");
    listController->InsertColumn(1, col);

    col.SetText("Servings");
    listController->InsertColumn(2, col);

    // servings, keywords, etc..

    listController->Hide();                 // speeds up the processes of adding items to the list.
    
    // populate the list with the recipe information.
    int i = -1;
    for (auto& recipe : recipes)
    {
        i++;
        listController->InsertItemInRecipeListReportDisplay(recipe, i);
        
    }
    listController->Show();

    listController->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    listController->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    listController->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
}


void MainFrame::BuildIngredientListReportDisplay()
{
    wxListItem col;
    col.SetText("Ingredient Name");
    col.SetImage(-1);
    listController->InsertColumn(0, col);

    col.SetText("Ingredient Type");
    listController->InsertColumn(1, col);

    col.SetText("Recipe Count");
    listController->InsertColumn(2, col);

    listController->Hide();                 // speeds up the processes of adding items to the list.

    // populate the list with the recipe information.
    int i = -1;
    for (auto& ingredient : ingredients)
    {
        i++;
        listController->InsertItemInIngredientListReportDisplay(ingredient, i);

    }
    listController->Show();

    listController->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    listController->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);
    listController->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);

    listController->Show();
}

void MainFrame::BuildCategoryListReportDisplay()
{
    wxListItem col;
    col.SetText("Category");
    col.SetImage(-1);
    listController->InsertColumn(0, col);

    col.SetText("Ingredient Count");
    listController->InsertColumn(1, col);

    listController->Hide();                 // speeds up the processes of adding items to the list.

    wxStopWatch sw;

    // populate the list with the recipe information.
    int i = -1;
    for (auto& category : categories)
    {
        i++;
        listController->InsertItemInCategoryListReportDisplay(category, i);

    }
    listController->Show();

    listController->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);
    listController->SetColumnWidth(1, wxLIST_AUTOSIZE_USEHEADER);

    listController->Show();
}

/*
* 
* Having issues with this debugging..
* 
void MainFrame::OnToggleBell(wxCommandEvent& e)
{
    listController->EnableBellOnNoMatch(e.IsChecked());
}

void MainFrame::OnSetRowLines(wxCommandEvent& e)
{
    listController->EnableAlternateRowColours(e.IsChecked());
    listController->Refresh();
}

void MainFrame::OnUpdateRowLines(wxUpdateUIEvent& e)
{
    e.Enable(listController->HasFlag(wxLC_VIRTUAL));
}
*/