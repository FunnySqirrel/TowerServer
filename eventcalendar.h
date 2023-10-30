
#ifndef EVENTCALENDAR_H
#define EVENTCALENDAR_H


#include "calendarpage.h"
#include "eventcard.h"
#include "calendarpage.h"


#include <QScrollArea>
#include <QStackedWidget>


class QLabel;

class EventCalendar : public QWidget
{
    Q_OBJECT
public:
    explicit EventCalendar(QWidget *parent = nullptr);
    QLabel *lCalendar;
    QPushButton *ButtonBack;
    QPushButton *ButtonForward;
    CalendarPage *Page[5];
    QStackedWidget *StackedWidget;
    QVBoxLayout *VLayout;
    QHBoxLayout *HLayout;

signals:

private slots:
    void onButtonBackClicked();
    void onButtonForwardClicked();

private:
    QString DateToString (int Month);
    void lCalendarDate (int Pg);

};

#endif // EVENTCALENDAR_H
