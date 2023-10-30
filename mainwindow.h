
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eventcalendar.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPoint DragStartPosition;
    EventCalendar *Calendar;


private:
    Ui::MainWindow *ui;

private slots:
    //void on_pushButton_clicked();


    // QWidget interface
protected:
    //void StopDragWidget (QMouseEvent *event);
    //virtual void mousePressEvent(QMouseEvent *event) override;
    //virtual void mouseMoveEvent(QMouseEvent *event) override;
    //virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
