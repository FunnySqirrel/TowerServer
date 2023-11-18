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
    static QString GetSideBarButtonStyle(QString iconUrl = NULL);
    static QString GetSideBarButtonActiveStyle(QString iconUrl = NULL);
    static QString GetNameProgStyle();
    static QString GetQlineStyle();
    static QString GetQLabelCardStyle();
    static QString GetQLabelCurrentDatePageStyle();
    static QString GetQLabelPageStyle();
    static QString GetDarkButtonTransparentStyle();
    static QString GetDarkButtonHoverStyle();
    static QString GetButtonBackStyle();
    static QString GetButtonForwardStyle();
    static QString GetlCalendarStyle();
};

#endif // MYSTYLEUI_H
