#include <QFontDatabase>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mystyleui.h"
#include "dbmanager.h"
//#include "paintcelldelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetInterfaceStyle();

    //Добавляем шрифт в базу шрифтов для того чтобы приложение после переноса на другой пк не требовало путь к шрифту
    //int id = QFontDatabase::addApplicationFont(":Resources/Fonts/ARIALUNI.TTF");
    //QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    //QDebug() << family;

    //Создаем базу данных по заданному пути

    if (DBManager::connect_to_database())
    {
        ui->statusbar->showMessage("Вы успешно подключились к базе данных: "); //+ UserCards.databaseName());

        UserCardsModel = new QSqlTableModel(this, UserCards);
        UserCardsModel->setTable(USER_TABLE); //Указываем имя базы данных
        UserCardsModel->select(); //Запрашиваемм данные из базы
        UserCardsModel->setHeaderData(0, Qt::Horizontal, "ID", Qt::DisplayRole);
        UserCardsModel->setHeaderData(1, Qt::Horizontal, "ФИО", Qt::DisplayRole);
        UserCardsModel->setHeaderData(2, Qt::Horizontal, "Дата рождения", Qt::DisplayRole);
        UserCardsModel->setHeaderData(3, Qt::Horizontal, "E-MAIL", Qt::DisplayRole);
        UserCardsModel->setHeaderData(4, Qt::Horizontal, "Телефон", Qt::DisplayRole);
        UserCardsModel->setHeaderData(5, Qt::Horizontal, "Логин", Qt::DisplayRole);
        UserCardsModel->setHeaderData(6, Qt::Horizontal, "Пароль", Qt::DisplayRole);
        UserCardsModel->setHeaderData(7, Qt::Horizontal, "Баланс", Qt::DisplayRole);
        UserCardsModel->setHeaderData(8, Qt::Horizontal, "Активен ли", Qt::DisplayRole);

        ui->tableView->setModel(UserCardsModel);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->verticalHeader()->hide();
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setColumnHidden(0,true);         //Скрываем ID, чтобы избежать их редактирования

        ui->tabWidget->tabBar()->hide(); //Скрыть названия вкладок

        // Функция сортировки
        //ui->tableView->setSortingEnabled(true);
    }
    else ui->statusbar->showMessage("При подключении к базе данных произошла ошибка: " + UserCards.lastError().databaseText());
}

MainWindow::~MainWindow()
{
    UserCards.close();
    delete ui;
}

//Добавление строчки(пользователя)
void MainWindow::on_AddButton_clicked()
{
    UserCardsModel->insertRow(UserCardsModel->rowCount());
}

//Удаление пользователя
void MainWindow::on_DelButton_clicked()
{
    UserCardsModel->removeRow(CurrentRow);
    UserCardsModel->select(); //Обновление данных
}

//Выбор пользователя, которого нужно удалить
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    CurrentRow = index.row();
}

//Реализация кнопки закрытия приложения
void MainWindow::on_CloseButton_clicked()
{
    close();
}

//Реализация кнопки сворачивания приложения
void MainWindow::on_MinimizedButton_clicked()
{
    showMinimized();
}

//Реализация кнопки развернуть на полный экран
void MainWindow::on_Maximized_NormalButton_clicked()
{
    isMaximized() ? showNormal() : showMaximized();
    isMaximized() ? ui->Maximized_NormalButton->setStyleSheet(MyStyleUI::GetMaximized_NormalActiveButtonsStyle()) : ui->Maximized_NormalButton->setStyleSheet(MyStyleUI::GetMaximized_NormalButtonsStyle());
    isMaximized() ? ui->Maximized_NormalButton->setToolTip (tr ("Свернуть в окно")) : ui->Maximized_NormalButton->setToolTip (tr ("Развернуть"));
}

//Реализация собственного пользовательского интерфейса
void MainWindow::SetInterfaceStyle()
{
    ui->CloseButton->setToolTip (tr ("Закрыть"));
    ui->CloseButton->setStyleSheet(MyStyleUI::GetCloseButtonsStyle());

    ui->Maximized_NormalButton->setToolTip (tr ("Развернуть"));
    ui->Maximized_NormalButton->setStyleSheet(MyStyleUI::GetMaximized_NormalButtonsStyle());

    ui->MinimizedButton->setToolTip (tr ("Свернуть"));
    ui->MinimizedButton->setStyleSheet(MyStyleUI::GetMinimizedButtonStyle());

    ui->DelButton->setToolTip (tr ("Удалить"));
    ui->DelButton->setStyleSheet(MyStyleUI::GetDelButtonStyle());

    ui->AddButton->setToolTip (tr ("Добавить"));
    ui->AddButton->setStyleSheet(MyStyleUI::GetAddButtonStyle());

    ui->UsersButton->setStyleSheet(MyStyleUI::GetLeftActiveButtonStyle());
    ui->IventsButton->setStyleSheet(MyStyleUI::GetLeftButtonStyle());

    ui->frame->setStyleSheet(MyStyleUI::GetFrameStyle());
    ui->tableView->setStyleSheet(MyStyleUI::GetTableStyle());
    ui->NameProg->setStyleSheet(MyStyleUI::GetNameProgStyle());
    //ui->tableView->setItemDelegate(new PaintCellDelegate);

    // Получить размер главного окна
    int width = this->width();
    int height = this->height();

    ui->tableView->resize(width,height); // Настройте размер окна tableView, чтобы он соответствовал основному окну (Не работает)
}

//Реализация перемещения окна
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    QWidget::mouseMoveEvent(event);

        QPoint y = event->globalPos();

        QPoint x = y - this->z;

        this->move(x);

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    QPoint y = event->globalPos(); // Положение мыши относительно левого верхнего угла рабочего стола, глобальное положение мыши

    QPoint x = this->geometry().topLeft(); // Положение левого верхнего угла окна относительно верхнего угла рабочего стола, положение окна

    this-> z = y-x; // фиксированное значение, без изменений
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    this-> z = QPoint (); // Конструктор инициализируется 0
}

void MainWindow::ChangeButtonStatus(int Num)
{
    if (Num == 1)
    {
        ui->UsersButton->setStyleSheet(MyStyleUI::GetLeftActiveButtonStyle());
        ui->IventsButton->setStyleSheet(MyStyleUI::GetLeftButtonStyle());
    }
    else
    {
        ui->UsersButton->setStyleSheet(MyStyleUI::GetLeftButtonStyle());
        ui->IventsButton->setStyleSheet(MyStyleUI::GetLeftActiveButtonStyle());
    }
}

void MainWindow::on_UsersButton_clicked()
{
    ChangeButtonStatus(1);
}


void MainWindow::on_IventsButton_clicked()
{
    ChangeButtonStatus(2);
}

