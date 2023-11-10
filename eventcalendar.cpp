
#include "eventcalendar.h"
#include "mystyleui.h"

#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

using namespace std::chrono;

EventCalendar::EventCalendar(QWidget *parent)
    : QWidget{parent}
{
    ButtonBack = new QPushButton(this);
    ButtonBack->setText("<<<");
    ButtonBack->setEnabled(false);
    ButtonBack->setStyleSheet(MyStyleUI::GetButtonBackStyle());
    ButtonBack->setIconSize(QSize(50, 50));
    ButtonBack->setMaximumHeight(55);

    ButtonForward = new QPushButton(this);
    ButtonForward->setStyleSheet(MyStyleUI::GetButtonForwardStyle());
    ButtonForward->setIconSize(QSize(100, 100));
    ButtonForward->setMaximumHeight(55);

    connect(ButtonBack, SIGNAL(clicked()), this, SLOT(onButtonBackClicked()));
    connect(ButtonForward, SIGNAL(clicked()), this, SLOT(onButtonForwardClicked()));

    StackedWidget = new QStackedWidget(this);

    for (int i = 0; i < 5; ++i) {
        Page.append(new CalendarPage(QDate::currentDate().addDays(i * 7), this));
        StackedWidget->addWidget(Page.last());
    }

    lCalendar = new QLabel(this);
    lCalendarDate(0);
    lCalendar->setAlignment(Qt::AlignCenter);
    lCalendar->setStyleSheet(MyStyleUI::GetlCalendarStyle());

    VLayout = new QVBoxLayout(this);
    VLayout->setContentsMargins(0, 0, 0, 0);
    VLayout->setSpacing(0);
    HLayout = new QHBoxLayout(this);

    VLayout->addLayout(HLayout);
    HLayout->addWidget(ButtonBack);
    HLayout->addWidget(lCalendar);
    HLayout->addWidget(ButtonForward);

    VLayout->addWidget(StackedWidget);
    setLayout(VLayout);
    setContentsMargins(0, 0, 0, 0);

    startTimer(1h);
}

void EventCalendar::onButtonBackClicked()
{
    if(StackedWidget->currentIndex() > 0) {
        StackedWidget->setCurrentIndex(StackedWidget->currentIndex() - 1);
        lCalendarDate(StackedWidget->currentIndex());
        ButtonForward->setEnabled(true);
    }
    else ButtonBack->setEnabled(false);
}

void EventCalendar::onButtonForwardClicked()
{
    if(StackedWidget->currentIndex() < 4) {
        StackedWidget->setCurrentIndex(StackedWidget->currentIndex() + 1);
        lCalendarDate(StackedWidget->currentIndex());
        ButtonBack->setEnabled(true);
    }
    else {
        ButtonForward->setEnabled(false);
    }
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

void EventCalendar::lCalendarDate(int Pg)
{
    if(Page[Pg]->Date[0].month() == Page[Pg]->Date[6].month())
        lCalendar->setText(DateToString(Page[Pg]->Date[0].month()) + Page[Pg]->Date[0].toString(" d") + " - " + Page[Pg]->Date[6].toString("d"));

    else lCalendar->setText(DateToString(Page[Pg]->Date[0].month()) + Page[Pg]->Date[0].toString(" d") + " - " + DateToString(Page[Pg]->Date[6].month()) + Page[Pg]->Date[6].toString(" d"));
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
