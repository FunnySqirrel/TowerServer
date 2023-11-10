
#ifndef EVENTCARD_H
#define EVENTCARD_H

#include <QWidget>

class QDialogButtonBox;
class QComboBox;
class QGraphicsDropShadowEffect;
class CalendarPage;
class QHBoxLayout;
class QVBoxLayout;
class QTextEdit;
class QPushButton;
class QLineEdit;
class QLabel;

class EventCard : public QWidget
{
    Q_OBJECT

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual QSize sizeHint() const;

public:
    explicit EventCard(CalendarPage *ParentCalendarPage = nullptr, QWidget *parent = nullptr);
    virtual ~EventCard();
    //QLabel *lNameEvent;
    QLineEdit *leNameEvent;

    QLabel *lTimeEvent;
    QLineEdit *leTimeEvent;

    QLabel *lRoom;
    QLineEdit *leRoom;

    QLabel *lNumberOfSeats;
    QLineEdit *leNumberOfSeats;

    QLabel *lPriceEvent;
    QLineEdit *lePriceEvent;

    QPushButton *bSignUp;
    QTextEdit *teDescription;

    QVBoxLayout *VLayout;
    QHBoxLayout *HLayout[4];

    QPoint DragStartPosition;
    QPoint z;
    static int ResID;          // Статическая переменная, счетчик номеров виджетов
    int getID();               // Функция для возврата локального номера кнопки

private:
    //Переменные
    CalendarPage *PCalendarPage;
    QString Names;
    QPushButton *Del;
    QGraphicsDropShadowEffect *shadow_effect;
    QDialog *Registration;
    QVBoxLayout *VDialogLayout;
    QHBoxLayout *HDialogLayout;
    QLabel *lName;
    QLineEdit *ldName;
    QComboBox *ComBox;
    QDialogButtonBox *DBB;
    QPalette *palette;
    int EventID = 0;           // Локальная переменная, id виджета
    int nCount = 0;
    int buffPos;
    int PreviousPos;

    //Функции (методы)
    inline int IndexCell(QPoint WidgetPosition);
    void SFHovered(QPoint WidgetPosition);

signals:

private slots:
    void on_bSignUpClicked();
    void on_leNumberOfSeatsTextChanged();
    void onDelButtonClicked();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // EVENTCARD_H
