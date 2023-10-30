
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDrag>
#include <QMimeData>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Calendar = new EventCalendar();
    //QVBoxLayout *VBox = new QVBoxLayout;
    //VBox->addWidget(Calendar);
    //ui->centralwidget->setLayout(VBox);
    //ui->centralwidget->layout()->de
    ui->centralwidget->layout()->addWidget(Calendar);

    //ui->gridLayout->addWidget(Card, 0, 1);
    //ui->gridLayout->addWidget(Card2, 2, 2);
    //ui->centralwidget->layout()->addWidget(Card);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::StopDragWidget(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton && Calendar->Page1->Card->IsMoving == true)
//    {
//
//    }
//
//}
//
//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton) DragStartPosition = event->pos();
//
//    qDebug() << "Координата основного окна " << event->pos();
//    //qDebug() << "Позиция Card " << Card->pos();
//    qDebug() << "Клик по виджету: " << Calendar->Page1->Card->geometry().contains(event->pos());
//}
//
//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//
//    if (event->button() == Qt::LeftButton && Calendar->Page1->Card->IsMoving == true)             //Card->geometry().contains(event->pos())
//    {
//        if (Calendar->Page1->Card->pos().y() + Calendar->Page1->Card->geometry().height() > this->geometry().height())
//        {
//            Calendar->Page1->Card->IsMoving = false;
//        }
//    }
//}
//
//void MainWindow::mouseReleaseEvent(QMouseEvent *event)
//{
//    //if(event->pos().rx() > geometry()) ui->centralwidget->layout()->addWidget(Card);
//}
