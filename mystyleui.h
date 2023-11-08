#ifndef MYSTYLEUI_H
#define MYSTYLEUI_H

#include <QString>
#include <QWindow>


class MyStyleUI
{
public:
    static QString GetCloseButtonsStyle();
    static QString GetMaximized_NormalButtonsStyle();
    static QString GetMaximized_NormalActiveButtonsStyle();
    static QString GetMinimizedButtonStyle();
    static QString GetFrameStyle();
    static QString GetDelButtonStyle();
    static QString GetAddButtonStyle();
    static QString GetTableStyle();
    static QString GetLeftButtonStyle();
    static QString GetLeftActiveButtonStyle();
    static QString GetNameProgStyle();
    static QString GetQlineStyle();
    static QString GetQLabelCardStyle();
    static QString GetQLabelCurrentPageStyle();
    static QString GetQLabelPageStyle();
    static QString GetDarkButtonTransparentStyle();
    static QString GetDarkButtonHoverStyle();
    static QString GetButtonBackStyle();
    static QString GetButtonForwardStyle();
};

#endif // MYSTYLEUI_H
