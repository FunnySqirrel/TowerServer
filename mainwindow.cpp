#include <QFontDatabase>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mystyleui.h"
//#include "paintcelldelegate.h"
#include "eventcalendar.h"

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
    UserCards = QSqlDatabase::addDatabase("QSQLITE");
    UserCards.setDatabaseName("C:/Tower of Magicians/DataBase/Test.db");



    if (UserCards.open())
    {
        ui->statusbar->showMessage("Вы успешно подключились к базе данных: "); //+ UserCards.databaseName());

        Query = new QSqlQuery(UserCards);
        Query->exec("CREATE TABLE Users("
                    "id INTEGER PRIMARY KEY,"
                    "ФИО TEXT,"
                    "ДатаРождения TEXT,"
                    "Телефон TEXT,"
                    "Почта TEXT,"
                    "Пароль TEXT,"
                    "Карта INTEGER ," //CHECK(typeof(Карта)='integer')
                    "Баллы INTEGER"   //CHECK(typeof(Баллы)='integer')
                    ")");

        UserCardsModel = new QSqlTableModel(this, UserCards);
        UserCardsModel->setTable("Users"); //Указываем имя базы данных
        UserCardsModel->select(); //Запрашиваемм данные из базы
        UserCardsModel->setHeaderData(0, Qt::Horizontal, "ID", Qt::DisplayRole);
        UserCardsModel->setHeaderData(2, Qt::Horizontal, "Дата Рождения", Qt::DisplayRole);

        ui->tableView->setModel(UserCardsModel);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->verticalHeader()->hide();
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        ui->tabWidget->tabBar()->hide(); //Скрыть названия вкладок

        // Функция сортировки
        //ui->tableView->setSortingEnabled(true);

        Calendar = new EventCalendar();
        ui->tabWidget->addTab(Calendar, "Календарь");
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
    UserCardsModel->select();
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
    ui->CloseButton->setIconSize(QSize(20, 20));

    ui->Maximized_NormalButton->setToolTip (tr ("Развернуть"));
    ui->Maximized_NormalButton->setStyleSheet(MyStyleUI::GetMaximized_NormalButtonsStyle());
    ui->Maximized_NormalButton->setIconSize(QSize(20, 20));

    ui->MinimizedButton->setToolTip (tr ("Свернуть"));
    ui->MinimizedButton->setStyleSheet(MyStyleUI::GetMinimizedButtonStyle());
    ui->MinimizedButton->setIconSize(QSize(20, 20));

    ui->DelButton->setToolTip (tr ("Удалить"));
    ui->DelButton->setStyleSheet(MyStyleUI::GetDelButtonStyle());
    ui->DelButton->setIconSize(QSize(30, 30));

    ui->AddButton->setToolTip (tr ("Добавить"));
    ui->AddButton->setStyleSheet(MyStyleUI::GetAddButtonStyle());
    ui->AddButton->setIconSize(QSize(30, 30));

    ui->UsersButton->setStyleSheet(MyStyleUI::GetLeftActiveButtonStyle());
    ui->IventsButton->setStyleSheet(MyStyleUI::GetLeftButtonStyle());

    ui->frame->setStyleSheet(MyStyleUI::GetFrameStyle());
    ui->tableView->setStyleSheet(MyStyleUI::GetTableStyle());
    ui->NameProg->setStyleSheet(MyStyleUI::GetNameProgStyle());
    //ui->tableView->setItemDelegate(new PaintCellDelegate);
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
    ui->tabWidget->setCurrentIndex(0);
}


void MainWindow::on_IventsButton_clicked()
{
    ChangeButtonStatus(2);
    ui->tabWidget->setCurrentIndex(1);
}

