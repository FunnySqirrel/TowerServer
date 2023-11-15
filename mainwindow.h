#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
//#include <QTableView>

#include "server.h"

QT_BEGIN_NAMESPACE

class EventCalendar;
class QLabel;
class QPropertyAnimation;
class QPushButton;
class QSqlTableModel;
class QSqlQuery;

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddButton_clicked(); //СЛОТ-обработчик нажатия кнопки добавления
    void on_DelButton_clicked(); //СЛОТ-обработчик нажатия кнопки удаления
    void on_tableView_clicked(const QModelIndex &index);
    void on_CloseButton_clicked(); //СЛОТ-обработчик нажатия кнопки закрытия приложения
    void on_MinimizedButton_clicked(); //СЛОТ-обработчик нажатия кнопки сворачивания приложения
    void on_Maximized_NormalButton_clicked(); //СЛОТ-обработчик нажатия кнопки разворачивания на полный экран приложения
    void on_UsersButton_clicked();
    void on_EventsButton_clicked();
    void onButtonBackClicked();
    void onButtonForwardClicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase UserCards;
    QSqlTableModel *UserCardsModel;
    QSqlQuery *Query;
    EventCalendar *Calendar;
    static Server* m_pServer;
    QPropertyAnimation *SideBarAnim;
    QPropertyAnimation *SideBarUsersButtonAnim;
    QPropertyAnimation *SideBarEventsButtonAnim;
    QPushButton *ButtonBack;
    QPushButton *ButtonForward;
    QLabel *lCalendar;
    int CurrentRow;
    bool mMoving;
    QPoint z;

    //Функции
    void SetInterfaceStyle();
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void ChangeButtonStatus(int Num);
    void fSideBarAnim(int duration, int startValue, int endValue);
    void lCalendarDate(int Pg);

public:
    void updateUsers();
    // QObject interface
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

};
#endif // MAINWINDOW_H
