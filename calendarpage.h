
#ifndef CALENDARPAGE_H
#define CALENDARPAGE_H

#include <QDate>
#include <QWidget>

class MyStyleUI;
class EventCard;
class QFrame;
class QGridLayout;
class QLabel;
class QPushButton;
class QScrollArea;
class QVBoxLayout;

class CalendarPage : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarPage(QDate PgDate, QWidget *parent = nullptr);


    QLabel *lDayOfTheWeek[7];
    QDate Date[7];
    QPushButton *AddButton;
    QVector <EventCard*> Card;
    QScrollArea *ScrollArea;
    QGridLayout *GridLayout;
    QVector <QPushButton*> DarkButton;
    QWidget *mw;

    int GetXCoord(QPoint WidgetPosition);
    int GetYCoord(QPoint WidgetPosition);
    inline int IndexCell(QPoint WidgetPosition);

signals:

private slots:
    void onDarkButtonClicked();

private:
    QString sDayOfTheWeek[7] {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресение"};
    QPoint dragStartPosition;
    int nPosGrid; //Индекс отвечающий за
    int ind;

    void SetDate(QDate PDate);
    void Init();

};

#endif // CALENDARPAGE_H
