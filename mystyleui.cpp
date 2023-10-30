
#include "mystyleui.h"


QString MyStyleUI::GetQlineStyle()
{
return "QLineEdit"
           "{"
           "Color: #5969BC;"
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

QString MyStyleUI::GetQLabelCurrentPageStyle()
{
return "QLabel"
       "{"
       "background-color: #355AA8;"
       "}";
}

QString MyStyleUI::GetQLabelPageStyle()
{
return "QLabel"
       "{"
       "background-color: rgb(203, 223, 255);"
       "}";
}
