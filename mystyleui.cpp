#include "mystyleui.h"



QString MyStyleUI::GetCloseButtonsStyle()
{
    return "QPushButton"
            "{"
                "border: none;"
                "background: transparent;"
                "icon: url(:/images/Resources/Close.png);"
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
               "icon: url(:/images/Resources/Maximize.png);"
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
               "icon: url(:/images/Resources/Normal.png);"
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
                "icon: url(:/images/Resources/Minimize.png);"
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
           "background-color: #4269A6;"
           //"background-color: rgb(75, 115, 218);"
           "}";
}

QString MyStyleUI::GetDelButtonStyle()
{
    return "QPushButton"
            "{"
                "border: none;"
                "background: transparent;"
                "icon: url(:/images/Resources/Delete.png);"
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
                "icon: url(:/images/Resources/Add.png);"
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
        //background: red;
        "border: 4px outset red;"
        "color: red;"
        "background-color: rgb(64, 64, 64);"
        "border: 5px solid #f6f7fa;"
        "border-radius:0px;"
        "border-color: white;"                              //rgb(64, 64, 64)
        "}"

             "QTableView {"
                     "Color: #5969BC;"                              // цвет текста в таблице
                     "font-family: ARIALUNI;"
                     "font-size: 16px;"
                     "gridline-color: white;"                       //Цвет внутренней рамки
                     "Background-color: #CBDFFF;"           // цвет фона в таблице #CBDFFF;
                     "alternate-background-color: #CBDFFF;"
                     "Selection-color: white;"                      // Цвет текста в выделенной области
                     "Selection-background-color: rgb(77, 77, 77);" //Цвет фона выбранной области
                     //"border: 2px groove gray;"
                     //"border-radius: 0px;"
                //"padding: 2px 4px;"
                        "}"

        "QHeaderView::item {"
        "border: 4px solid white;"
        "}"

        "QHeaderView {"
        "Color: #7C7C7C;"
        "font-family: ARIALUNI;"
        "font-size: 24px;"
        "background-color: #B4D2FF;"
        //"background-color: #BCC4FF;"
        "border: 0px solid rgb(144, 144, 144);"
        "border: 0px solid rgb(191,191,191);"
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

QString MyStyleUI::GetSideBarButtonStyle(QString iconUrl)
{
    return "QPushButton"
           "{"
           "border: none;"
           "border-radius: 12px;"
           "background: transparent;"
           "font-family: ARIALUNI;"
           "font-size: 16px;"
           "line-height: 1.0;"
           "color: rgb(100, 100, 100);"
           + iconUrl
           + "}"

           "QPushButton::hover { "
           "background-color: #e2edff;"
           "}";
}

QString MyStyleUI::GetSideBarButtonActiveStyle(QString iconUrl)
{
    return "QPushButton"
           "{"
           "color: #E2EDFF;"
           "border: none;"
           "border-radius: 12px;"
           "background: transparent;"
           "font-family: ARIALUNI;"
           "font: 16px;"
           + iconUrl
           + "}";
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

QString MyStyleUI::GetQlineStyle()
{
    return "QLineEdit"
           "{"
           "Color: #4269A6;"
           //"font-family: ARIALUNI;"
           //"font-size: 13px;"
           "border: 1px solid rgb(155, 195, 255);"
           "border-radius: 7px;"
           "background-color: rgb(155, 195, 255);"
           "}";
}

QString MyStyleUI::GetQLabelCardStyle()
{
    return "QLabel"
           "{"
           "background-color: rgb(155, 195, 255);"
           "border: 1px solid rgb(155, 195, 255);"
           "border-radius: 7px;"
           "}";
}

QString MyStyleUI::GetQLabelCurrentDatePageStyle()
{
    return "QLabel"
           "{"
           "background-color: #4269A6;"
           //"background-color: #355AA8;"
           "color: #E2EDFF;"
           "}";
}

QString MyStyleUI::GetQLabelPageStyle()
{
    return "QLabel"
           "{"
           "background-color: rgb(203, 223, 255);"
           "color: #4269A6;"
           "}";
}

QString MyStyleUI::GetDarkButtonTransparentStyle()
{
    return "QPushButton"
           "{"
           "background-color: transparent;"
           "}"
           "QPushButton::hover"
           "{"
           "background-color: rgba(225, 225, 225, 125);"
           "border: solid;"
           "border-width: 3px;"
           "border-color: rgb(200, 200, 200);"
           "icon: url(:/images/Resources/ButtonIcon.png)"
           "}"
           "QPushButton::pressed"
           "{"
           "background-color: rgb(225, 225, 225);"
           "}";
}

QString MyStyleUI::GetDarkButtonHoverStyle()
{
    return "QPushButton"
           "{"
           "background-color: rgba(225, 225, 225, 125);"
           "border: none;"
           "}";
}

QString MyStyleUI::GetButtonBackStyle()
{
    return "QPushButton"
           "{"
           "background-color: #4269A6;"
           //"icon: url(:/images/Resources/Arrow.png)"
           "}"
           "QPushButton::hover"
           "{"
           "background-color: #CDD3FF;"
           "}"
           "QPushButton::pressed"
           "{"
           "background-color: #C9EDFF;"
           "}";
}

QString MyStyleUI::GetButtonForwardStyle()
{
    return "QPushButton"
           "{"
           "background-color: #4269A6;"
           //"border: outset;"
           //"border-width: 2px;"
           "icon: url(:/images/Resources/Arrow.png)"
           "}"
           "QPushButton::hover"
           "{"
           "background-color: #CDD3FF;"
           "}"
        "QPushButton::pressed"
        "{"
           "background-color: #C9EDFF;"
           "}";
}

QString MyStyleUI::GetlCalendarStyle()
{
    return "QLabel"
           "{"
           "background-color: #4269A6;"
           "font-family: ARIALUNI;"
           "font-size: 18px;"
           "color: #E2EDFF;"
           "}";
}


