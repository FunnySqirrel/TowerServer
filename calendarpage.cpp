
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
#include <QStackedLayout>
#include <QVBoxLayout>

void CalendarPage::Init()
{
    for (int i = 0; i < 7; i++)
    {
        lDayOfTheWeek[i] = new QLabel(this);                                                                                    //Выделение памяти под лейбл
        if(Date[i] != QDate::currentDate()) lDayOfTheWeek[i]->setStyleSheet(MyStyleUI::GetQLabelPageStyle());
        else lDayOfTheWeek[i]->setStyleSheet(MyStyleUI::GetQLabelCurrentDatePageStyle());
        lDayOfTheWeek[i]->setMinimumSize(140, 80);                                                                             //Присваивание минимального размера виджету
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
            GridLayout->addWidget(DarkButton.last(), i, j + 1);
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
    Card.append(new EventCard(this));
    Card.last()->setMaximumWidth(250);

    //Определяем объект, который вызвал сигнал, И на его месте создаем карточку
    QPushButton *temp = qobject_cast<QPushButton*> (sender());
    GridLayout->addWidget(Card.last(), GetYCoord(temp->geometry().center()), GetXCoord(temp->geometry().center()) + 1);
    DarkButton[IndexCell(temp->geometry().center())]->hide();

    int c = 0;
    for (int i = 1; i < GridLayout->columnCount(); ++i) {
        if(GridLayout->itemAtPosition(GetYCoord(temp->geometry().center()), i)->widget()->isHidden()) c++;
    }
    if (c == GridLayout->columnCount() - 1) {
        //Процедура создает дополнительную колонку ячеек если больше нет свободных ячеек в строке
        int col = GridLayout->columnCount();
        int j = 0;
        for (int i = 1; i < 8; i++) {
            DarkButton.insert(i * (col - 1) + j, new QPushButton(this));
            DarkButton[i * (col - 1) + j]->setMinimumSize(200, 218);
            DarkButton[i * (col - 1) + j]->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
            GridLayout->addWidget(DarkButton[i * (col - 1) + j], i - 1, col, Qt::AlignLeft);
            connect(DarkButton[i * (col - 1) + j], SIGNAL(clicked()), this, SLOT(onDarkButtonClicked()));
            DarkButton[i * (col - 1) + j]->lower();
            ++j;
        }
    }

    //qDebug() << mw->width();
    //DarkButton.clear();
    //qDebug() << DarkButton.size();
    //for (int i = 0; i < 35 + 7; ++i) {
    //    DarkButton.append(new QPushButton(this));
    //    DarkButton.last()->setMinimumSize(200, 218);
    //    DarkButton.last()->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
    //    GridLayout->addWidget(DarkButton.last(), i/6, i%7, Qt::AlignLeft);
    //    connect(DarkButton.last(), SIGNAL(clicked()), this, SLOT(onDarkButtonClicked()));
    //}
    //mw->update();
    //qDebug() << mw->width();

    //for (int i = 0; i < DarkButton.size(); ++i) {
    //if(DarkButton[i] == (QPushButton*) sender()) {
    //qDebug() << "Номер строки: " << i/5;
    //qDebug() << "Номер столбца: " << i%5+1;
    //GridLayout->addWidget(Card.last(), i/5, i%5+1);
    //DarkButton[i]->hide();
    //break;
    //}
    //int count = 0;
    //for (int j = 0; j < GridLayout->columnCount() - 1; ++j) {
    //    if(DarkButton[i/5 + j]->isHidden()) {
    //        count++;
    //        qDebug() << count;
    //    }
    //    if(count + 1 == GridLayout->columnCount() - 1) {
    //        for (int k = 0; k < DarkButton.size(); k += count) {
    //            if(k%5 ==  0) {
    //                DarkButton.insert(k, new QPushButton(this));
    //                DarkButton[k]->setMinimumSize(200, 218);
    //                DarkButton[k]->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
    //                GridLayout->addWidget(DarkButton[k], k/(count + 1), count + 1, Qt::AlignLeft);
    //                connect(DarkButton[k], SIGNAL(clicked()), this, SLOT(onDarkButtonClicked()));
    //            }
    //        }
    //    }
    //}
    //}
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
