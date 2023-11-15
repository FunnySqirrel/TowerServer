
#include "eventcalendar.h"
#include "mystyleui.h"

#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>

using namespace std::chrono;

EventCalendar::EventCalendar(QWidget *parent)
    : QWidget{parent}
{
    StackedWidget = new QStackedWidget(this);

    for (int i = 0; i < 5; ++i) {
        Page.append(new CalendarPage(QDate::currentDate().addDays(i * 7), this));
        StackedWidget->addWidget(Page.last());
    }

    VLayout = new QVBoxLayout(this);
    VLayout->setContentsMargins(0, 0, 0, 0);
    VLayout->setSpacing(0);
    HLayout = new QHBoxLayout(this);

    VLayout->addWidget(StackedWidget);
    setLayout(VLayout);
    setContentsMargins(0, 0, 0, 0);

    startTimer(1h);
}

QString EventCalendar::DateToString(int Month)
{
    switch (Month)
    {
    case 1:
        return "Январь";
    case 2:
        return "Февраль";
    case 3:
        return "Март";
    case 4:
        return "Апрель";
    case 5:
        return "Май";
    case 6:
        return "Июнь";
    case 7:
        return "Июль";
    case 8:
        return "Август";
    case 9:
        return "Сентябрь";
    case 10:
        return "Октябрь";
    case 11:
        return "Ноябрь";
    case 12:
        return "Декабрь";
    default: break;
    }
}

//Не протестированно
void EventCalendar::timerEvent(QTimerEvent *event)
{
    for (int i = 0; i < 7; ++i) {
        if(i > 0 && Page[0]->Date[i] == QDate::currentDate()) {
            Page[0]->lDayOfTheWeek[i - 1]->setStyleSheet(MyStyleUI::GetQLabelPageStyle());
            Page[0]->lDayOfTheWeek[i]->setStyleSheet(MyStyleUI::GetQLabelCurrentDatePageStyle());
        }
        else {
            Page[1]->lDayOfTheWeek[0]->setStyleSheet(MyStyleUI::GetQLabelPageStyle());
            StackedWidget->removeWidget(Page[0]);
            Page.removeFirst();
            Page.append(new CalendarPage(QDate::currentDate().addDays(4 * 7), this));
        }

    }
    Interval.addMSecs(-1 * QTime::currentTime().msec());
    startTimer(Interval.msec());
}
