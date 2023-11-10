
#ifndef EVENTCALENDAR_H
#define EVENTCALENDAR_H

#include "calendarpage.h"
#include "eventcard.h"
#include "calendarpage.h"

class QStackedWidget;
class QLabel;

class EventCalendar : public QWidget
{
    Q_OBJECT
public:
    explicit EventCalendar(QWidget *parent = nullptr);
    QLabel *lCalendar;
    QPushButton *ButtonBack;
    QPushButton *ButtonForward;
    QList <CalendarPage*> Page;
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
    QTime Interval/* = (23, 59, 59, 999)*/;


    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // EVENTCALENDAR_H
