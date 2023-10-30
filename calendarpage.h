
#ifndef CALENDARPAGE_H
#define CALENDARPAGE_H

#include "eventcard.h"

#include <QDate>
#include <QScrollArea>
#include <QWidget>


class CalendarPage : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarPage(QDate PgDate, QWidget *parent = nullptr);


    QLabel *lDayOfTheWeek[7];
    QDate Date[7];
    QPushButton *AddButton;
    EventCard *Card;
    QScrollArea *ScrollArea;
    QGridLayout *GridLayout;

signals:

private slots:
    void onAddButtonClicked();

private:
    QString sDayOfTheWeek[7] {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресение"};
    QWidget *ShadowField[7];
    QHBoxLayout *HBox[7];
    QVBoxLayout *mwl;

    void SetDate(QDate PDate);
    void Init(MyStyleUI Style1);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

    // QObject interface
    virtual void timerEvent(QTimerEvent *event) override;
};

#endif // CALENDARPAGE_H
