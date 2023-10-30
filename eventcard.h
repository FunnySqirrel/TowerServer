
#ifndef EVENTCARD_H
#define EVENTCARD_H

#include "mystyleui.h"

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>


class EventCard : public QWidget
{
    Q_OBJECT

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual QSize sizeHint() const;

public:
    explicit EventCard(QWidget *parent = nullptr);
    QLabel *lNameEvent;
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
    bool IsMoving = false;
    static int ResID;          // Статическая переменная, счетчик номеров виджетов
    //int getID();               // Функция для возврата локального номера кнопки

private:
    int EventID = 0;          // Локальная переменная, id виджета
    QString Names;
    int nCount = 0;

signals:

private slots:
    void on_bSignUpClicked();
    void on_leNumberOfSeatsTextChanged();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // EVENTCARD_H
