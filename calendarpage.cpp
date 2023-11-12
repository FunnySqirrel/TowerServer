
#include "calendarpage.h"
#include "eventcard.h"
#include "mystyleui.h"

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit> //потом удалить
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QScroller>
#include <QVBoxLayout>

#define ADDBUTTONSIZE QSize(50,50)

void CalendarPage::Init()
{
    for (int i = 0; i < 7; i++)
    {
        lDayOfTheWeek[i] = new QLabel(this);                                                                                    //Выделение памяти под лейбл
        if(Date[i] != QDate::currentDate()) lDayOfTheWeek[i]->setStyleSheet(MyStyleUI::GetQLabelPageStyle());
        else lDayOfTheWeek[i]->setStyleSheet(MyStyleUI::GetQLabelCurrentDatePageStyle());
        lDayOfTheWeek[i]->setMinimumSize(140, 120);                                                                             //Присваивание минимального размера виджету
        lDayOfTheWeek[i]->setFixedWidth(140);                                                                                   //Присваивание максимальной ширины
        QString Format1 = "<html><head/><body><p align=center><span style=" "font-size:16pt; color:#5969bc;>";
        QString Format2 = "</span><br/><span style=" "font-size:10pt; color:#5969bc;>";
        QString Format3 = "</span></p></body></html>";
        lDayOfTheWeek[i]->setText(Format1 + sDayOfTheWeek[i] + Format2 + QLocale::system().toString(Date[i]) + Format3);        //Вставляем дату ввиде текста
        //lDayOfTheWeek[i]->setAlignment(Qt::AlignCenter);                                                                      //Выравнивание текста по центру
        GridLayout->addWidget(lDayOfTheWeek[i], i, 0, Qt::AlignLeft);                                                           //Добавление лейбла в сетку с выравниванием
            //по левой стороне
        for (int j = 0; j < 5; ++j) {
            DarkButton.append(new QPushButton(this));
            DarkButton.last()->setMinimumSize(200, 218);
            //DarkButton[5 * i + j]->setMaximumWidth(200);
            DarkButton.last()->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
            GridLayout->addWidget(DarkButton.last(), i, j + 1, Qt::AlignLeft);
            connect(DarkButton.last(), SIGNAL(clicked()), this, SLOT(onDarkButtonClicked()));
        }
    }
}

CalendarPage::CalendarPage(QDate PgDate, QWidget *parent)
    : QWidget{parent}
{
    setContentsMargins(0, 0, 0, 0);
    SetDate(PgDate);

    ScrollArea = new QScrollArea(this);
    ScrollArea->setWidgetResizable(true);
    //ScrollArea->verticalScrollBar()->setSingleStep(5);

    QVBoxLayout *vb = new QVBoxLayout(this);
    vb->addWidget(ScrollArea);
    vb->setContentsMargins(0, 0, 0, 0);

    GridLayout = new QGridLayout(this);
    GridLayout->setVerticalSpacing(5);
    GridLayout->setHorizontalSpacing(5);
    GridLayout->setContentsMargins(0,0,0,0);

    mw = new QWidget(this);
    mw->setStyleSheet("QWidget"
                      "{"
                      "background-color: rgb(255, 255, 255)"
                      "}");
    mw->setContentsMargins(0, 0, 0, 0);
    QScroller::grabGesture(ScrollArea->viewport(), QScroller::MiddleMouseButtonGesture);

    Init();

    mw->setLayout(GridLayout);
    ScrollArea->setWidget(mw);

    setLayout(vb);
}

/*Функция переводит координаты курсора в координаты сетки
Если курсор заходит на заголовок, то возвращаем -1
Если курсор попадает в остальную часть возвращаем индекс поля подсветки*/
int CalendarPage::GetXCoord(QPoint WidgetPosition)
{
    int WidthHeader = lDayOfTheWeek[0]->width() + GridLayout->horizontalSpacing() + ScrollArea->contentsMargins().left();
    int FieldWidth = mw->width() - WidthHeader;
    int CellWidth = FieldWidth / (GridLayout->columnCount() - 1);
    if(WidthHeader > WidgetPosition.x()) return -1;
    else if(mw->width() - 10 < WidgetPosition.x()) return GridLayout->columnCount() - 2;
    else return ((WidgetPosition.x() - WidthHeader)/ CellWidth);
}

int CalendarPage::GetYCoord(QPoint WidgetPosition)
{
    if(WidgetPosition.y() / DarkButton.last()->height() < GridLayout->rowCount()) return WidgetPosition.y() / DarkButton.last()->height();
    else return GridLayout->rowCount() - 1;
}

int CalendarPage::IndexCell(QPoint WidgetPosition)
{
    if(GetXCoord(WidgetPosition) != -1) return (GridLayout->columnCount() - 1) * GetYCoord(WidgetPosition) + GetXCoord(WidgetPosition);
}

void CalendarPage::onDarkButtonClicked()
{
    Card.append(new EventCard(this, this));
    Card.last()->setMaximumWidth(200);

    //Определяем объект, который вызвал сигнал, И на его месте создаем карточку
    QPushButton *temp = qobject_cast<QPushButton*> (sender());
    GridLayout->addWidget(Card.last(), GetYCoord(temp->geometry().center()), GetXCoord(temp->geometry().center()) + 1);
    DarkButton[IndexCell(temp->geometry().center())];

    //  0  1  2  3  4  ->   0  1  2  3  4  5
    //  5  6  7  8  9  ->   6  7  8  9 10 11
    // 10 11 12 13 14  ->  12 13 14 15 16 17
    // 15 16 17 18 19  ->  18 19 20 21 22 23
    // 20 21 22 23 24  ->  24 25 26 27 28 29
    // 25 26 27 28 29  ->  30 31 32 33 34 35
    // 30 31 32 33 34  ->  36 37 38 39 40 41

    /*Функция создает дополнительную колонку ячеек
    int col = GridLayout->columnCount();
    int j = 0;
    for (int i = 1; i < 8; i++) {
        DarkButton.insert(i * (col - 1) + j, new QPushButton(this));
        DarkButton[i * (col - 1) + j]->setMinimumSize(200, 218);
        DarkButton[i * (col - 1) + j]->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
        GridLayout->addWidget(DarkButton[i * (col - 1) + j], i - 1, col, Qt::AlignLeft);
        connect(DarkButton[i * (col - 1) + j], SIGNAL(clicked()), this, SLOT(onDarkButtonClicked()));
        ++j;
    }*/
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
