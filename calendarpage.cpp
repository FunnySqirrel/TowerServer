
#include "calendarpage.h"

#define ADDBUTTONSIZE QSize(50,50)

void CalendarPage::Init(MyStyleUI Style1)
{
    for (int i = 0; i < 7; i++)
    {
        lDayOfTheWeek[i] = new QLabel(this);
        if(Date[i] != QDate::currentDate()) lDayOfTheWeek[i]->setStyleSheet(Style1.GetQLabelPageStyle()); //
        else lDayOfTheWeek[i]->setStyleSheet(Style1.GetQLabelCurrentPageStyle());
        lDayOfTheWeek[i]->setMinimumSize(140, 120);
        lDayOfTheWeek[i]->setMaximumWidth(140);
        lDayOfTheWeek[i]->setText(sDayOfTheWeek[i] + "\n" + QLocale::system().toString(Date[i]));
        lDayOfTheWeek[i]->setAlignment(Qt::AlignCenter);
        ShadowField[i] = new QWidget(this);
        HBox[i] = new QHBoxLayout(this);
        HBox[i]->addWidget(lDayOfTheWeek[i]);
        ShadowField[i]->setLayout(HBox[i]);
        mwl->addWidget(ShadowField[i]);
        //GridLayout->addWidget(lDayOfTheWeek[i], i, 0, Qt::AlignLeft);
    }
}

CalendarPage::CalendarPage(QDate PgDate, QWidget *parent)
    : QWidget{parent}
{
    MyStyleUI Style1;

    SetDate(PgDate);

    ScrollArea = new QScrollArea(this);
    QVBoxLayout *vb = new QVBoxLayout(this);
    vb->addWidget(ScrollArea);

    //GridLayout = new QGridLayout(this);
    //GridLayout->setVerticalSpacing(3);

    QWidget *mw = new QWidget(this);
    QVBoxLayout *mwl = new QVBoxLayout(this);

    Init(Style1);

    mw->setLayout(mwl);

    //mw->setLayout(GridLayout);
    ScrollArea->setWidget(mw);
    ScrollArea->setWidgetResizable(true);

    setLayout(vb);

    AddButton = new QPushButton("+", this);
    AddButton->setStyleSheet("QPushButton"
                             "{"
                             "background-color: blue;"
                             "border-style: outset;"
                             "border-width: 1px;"
                             "border-radius: 25px;"
                             "font-size: 50px;"
                             "text-align: bottom;"
                             "border-color: black;"
                             "}");
    AddButton->setMinimumSize(50,50);
    AddButton->setMaximumSize(50,50);
    AddButton->move(geometry().bottomRight()); // - QPoint(100, 100)

    connect(AddButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
}

void CalendarPage::onAddButtonClicked()
{
    Card = new EventCard(this);
    Card->setMaximumWidth(200);
    //QDate cDate = cDate.currentDate();
    //int Count = 0;
    //for (int i = 0; i < GridLayout->columnCount(); ++i) {
    //    //if(GridLayout->itemAtPosition(cDate.dayOfWeek() - 1, i) == nullptr) GridLayout->addWidget(Card, (cDate.dayOfWeek() - 1), i, 1, 10, Qt::AlignLeft);
    //    //else ++Count;

    //    //if(Count == GridLayout->columnCount()) GridLayout->addWidget(Card, (cDate.dayOfWeek() - 1), GridLayout->columnCount() + 1);
    //}
    ScrollArea->ensureWidgetVisible(Card);
    //qDebug() << "Количество столбцов: " << GridLayout->columnCount();

}

void CalendarPage::SetDate(QDate PDate)
{
    QDate tempDate = PDate;
    switch (PDate.dayOfWeek()) {
    case 1:
        for (int i = 0; i < 7; ++i) {
            Date[i] = tempDate.addDays(i);
        }
        break;
    case 2:
        tempDate = tempDate.addDays(-1);
        for (int i = 0; i < 7; ++i) {
            Date[i] = tempDate.addDays(i);
        }
        break;
    case 3:
        tempDate = tempDate.addDays(-2);
        for (int i = 0; i < 7; ++i) {
            Date[i] = tempDate.addDays(i);
        }
        break;
    case 4:
        tempDate = tempDate.addDays(-3);
        for (int i = 0; i < 7; ++i) {
            Date[i] = tempDate.addDays(i);
        }
        break;
    case 5:
        tempDate = tempDate.addDays(-4);
        for (int i = 0; i < 7; ++i) {
            Date[i] = tempDate.addDays(i);
        }
        break;
    case 6:
        tempDate = tempDate.addDays(-5);
        for (int i = 0; i < 7; ++i) {
            Date[i] = tempDate.addDays(i);
        }
        break;
    case 7:
        tempDate = tempDate.addDays(-6);
        for (int i = 0; i < 7; ++i) {
            Date[i] = tempDate.addDays(i);
        }
        break;
    default:
        break;
    }
}

void CalendarPage::resizeEvent(QResizeEvent *event)
{
    AddButton->move(geometry().bottomRight() - QPoint(75, 75));
}


void CalendarPage::timerEvent(QTimerEvent *event)
{
}
