#include "mystyleui.h"



QString MyStyleUI::GetCloseButtonsStyle()
{
    return "QPushButton"
            "{"
                "border: none;"
                "background: transparent;"
                "background-image: url(Resources/Close.png);"
                "background-repeat:no-repeat;"
                "background-position: center center;"
            "}"

            "QPushButton::hover"
            "{"
                "background-color: rgb(200, 50, 50);"
            "}"

            "QPushButton::pressed"
            "{"
                "background-color: rgb(230, 50, 50);"
            "}";
}

QString MyStyleUI::GetMaximized_NormalButtonsStyle()
{
    return "QPushButton"
           "{"
               "border: none;"
               "background: transparent;"
               "background-image: url(Resources/Maximize.png);"
               "background-repeat:no-repeat;"
               "background-position: center center;"
           "}"

           "QPushButton::hover"
           "{"
               "background-color: rgb(85, 129, 243);"
           "}"

           "QPushButton::pressed"
           "{"
               "background-color: rgb(90, 136, 255);"
           "}";
}

QString MyStyleUI::GetMaximized_NormalActiveButtonsStyle()
{
    return "QPushButton"
           "{"
               "border: none;"
               "background: transparent;"
               "background-image: url(Resources/Normal.png);"
               "background-repeat:no-repeat;"
               "background-position: center center;"
           "}"

           "QPushButton::hover"
           "{"
               "background-color: rgb(85, 129, 243);"
           "}"

           "QPushButton::pressed"
           "{"
               "background-color: rgb(90, 136, 255);"
           "}";
}

QString MyStyleUI::GetMinimizedButtonStyle()
{
    return "QPushButton"
            "{"
                "border: none;"
                "background: transparent;"
                "background-image: url(Resources/Minimize.png);"
                "background-repeat:no-repeat;"
                "background-position: center center;"
            "}"

            "QPushButton::hover"
            "{"
                "background-color: rgb(85, 129, 243);"
            "}"

            "QPushButton::pressed"
            "{"
                "background-color: rgb(90, 136, 255);"
           "}";
}

QString MyStyleUI::GetFrameStyle()
{
    return "QFrame"
            "{"
            "background-color: rgb(75, 115, 218);"
           "}";
}

QString MyStyleUI::GetDelButtonStyle()
{
    return "QPushButton"
            "{"
                "border: none;"
                "background: transparent;"
                "background-image: url(Resources/Delete.png);"
                "background-repeat:no-repeat;"
                "background-position: center center;"
            "}"

            "QPushButton::hover"
            "{"
                "background-color: rgb(85, 129, 243);"
            "}"

            "QPushButton::pressed"
            "{"
                "background-color: rgb(90, 136, 255);"
           "}";
}

QString MyStyleUI::GetAddButtonStyle()
{
    return "QPushButton"
            "{"
                "border: none;"
                "background: transparent;"
                "background-image: url(Resources/Add.png);"
                "background-repeat:no-repeat;"
                "background-position: center center;"
            "}"

            "QPushButton::hover"
            "{"
                "background-color: rgb(85, 129, 243);"
            "}"

            "QPushButton::pressed"
            "{"
                "background-color: rgb(90, 136, 255);"
           "}";
}

QString MyStyleUI::GetTableStyle()
{
    return  /*QTableView Top left style */
            "QTableView QTableCornerButton::section {"
               /*  background: red;
                border: 2px outset red;*/
                "color: red;"
                "background-color: rgb(64, 64, 64);"
                "border: 5px solid #f6f7fa;"
                "border-radius:0px;"
                "border-color: rgb(64, 64, 64);"
             "}"

             "QTableView {"
                     "Color: #5969BC;"                              // цвет текста в таблице
                     "font-family: ARIALUNI;"
                     "font-size: 16px;"
                     "Gridline-color: black;"                       //Цвет внутренней рамки
                     "Background-color: white;"           // цвет фона в таблице #CBDFFF;
                "alternate-background-color: white;"
                     "Selection-color: white;"                      // Цвет текста в выделенной области
                     "Selection-background-color: rgb(77, 77, 77);" //Цвет фона выбранной области
                //"border: 2px groove gray;"
                //"border-radius: 0px;"
                //"padding: 2px 4px;"
            "}"

            "QHeaderView {"
                "Color: #7C7C7C;"
                "font-family: ARIALUNI;"
                "font-size: 24px;"
                "background-color: #BCC4FF;"
                "border: 0px solid rgb(144, 144, 144);"
                "border:0px solid rgb(191,191,191);"
                "border-left-color: rgba(255, 255, 255, 0);"
                "border-top-color: rgba(255, 255, 255, 0);"
                "border-radius:0px;"
                "min-height:29px;"
            "}"

            "QHeaderView::section {"
                "color: #7C7C7C;;"
                "background-color: #BCC4FF;"
                "border: none;" //1px solid #AAAAAA;
                "border-radius:0px;"
                //"border-color: #AAAAAA;"
            "}";
}

QString MyStyleUI::GetLeftButtonStyle()
{
    return "QPushButton"
            "{"
                //"background-color: rgb(75, 75, 75);"
                "border: none;"
                "border-radius: 12px;"
                "background: transparent;"
                "font-family: ARIALUNI;"
                "font-size: 16px;"
                "line-height: 1.0;"
                "color: rgb(200, 200, 200);"
            "}"

            "QPushButton::hover { "
            "text-decoration: underline;"
            "}";
}

QString MyStyleUI::GetLeftActiveButtonStyle()
{
    return "QPushButton"
            "{"
                //"background-color: rgb(75, 75, 75);"
                "color: rgb(200, 200, 200);"
                "border: none;"
                "border-radius: 12px;"
                "background: transparent;"
                "font-family: ARIALUNI;"
                "font: bold 16px;"
                "text-transform: uppercase;"
                "text-decoration: underline;"
           "}";
}

QString MyStyleUI::GetNameProgStyle()
{
    return "QLabel"
            "{"
                "color: rgb(200, 200, 200);"
                "background: transparent;"
                "font-family: ARIALUNI;"
                "font-size: 20px;"
            "}";
}


