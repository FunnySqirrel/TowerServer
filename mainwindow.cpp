#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMouseEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mystyleui.h"
#include "dbmanager.h"
#include "eventcalendar.h"

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
        UserCardsModel->setHeaderData(1, Qt::Horizontal, "Обращение", Qt::DisplayRole);
        UserCardsModel->setHeaderData(2, Qt::Horizontal, "День рождения", Qt::DisplayRole);
        UserCardsModel->setHeaderData(3, Qt::Horizontal, "Логин", Qt::DisplayRole);
        UserCardsModel->setHeaderData(4, Qt::Horizontal, "Пароль", Qt::DisplayRole);
        UserCardsModel->setHeaderData(5, Qt::Horizontal, "Баланс", Qt::DisplayRole);
        UserCardsModel->setHeaderData(6, Qt::Horizontal, "Активен ли", Qt::DisplayRole);

        ui->tableView->setModel(UserCardsModel);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->verticalHeader()->hide();
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setColumnHidden(0,true);         //Скрываем ID, чтобы избежать их редактирования

        ui->tabWidget->tabBar()->hide(); //Скрыть названия вкладок

        //Функция сортировки
        ui->tableView->setSortingEnabled(true);
    }

    else ui->statusbar->showMessage("При подключении к базе данных произошла ошибка: " + UserCards.lastError().databaseText());
    MyServer::pServer->serverInit();

    DBManager::setOwner(this);
    Calendar = new EventCalendar();
    ui->tabWidget->addTab(Calendar, "Календарь");
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

QVariant MainWindow::StringInterpolator(const QString &start, const QString &end, qreal progress)
{
    if(progress < 1.0)
        return start;
    else
        return end;
}

//Реализация собственного пользовательского интерфейса
void MainWindow::fSideBarAnim(int duration, int startValue, int endValue)
{
    SideBarAnim = new QPropertyAnimation(ui->Sidebar, "minimumWidth", ui->Sidebar);
    SideBarUsersButtonAnim = new QPropertyAnimation(ui->UsersButton, "maximumWidth", ui->UsersButton);
    SideBarEventsButtonAnim = new QPropertyAnimation(ui->EventsButton, "maximumWidth", ui->EventsButton);
    SideBarAnim->setDuration(duration);
    SideBarAnim->setStartValue(startValue);
    SideBarAnim->setEndValue(endValue);
    if(endValue > ui->UsersButton->minimumWidth()) {
        SideBarUsersButtonAnim->setEndValue(endValue);
        SideBarEventsButtonAnim->setEndValue(endValue);
    }
    else {
        SideBarUsersButtonAnim->setEndValue(ui->UsersButton->minimumWidth());
        SideBarEventsButtonAnim->setEndValue(ui->EventsButton->minimumWidth());
    }
    SideBarUsersButtonAnim->setDuration(duration);
    SideBarEventsButtonAnim->setDuration(duration);
    SideBarAnim->start(QAbstractAnimation::DeleteWhenStopped);
    SideBarUsersButtonAnim->start(QAbstractAnimation::DeleteWhenStopped);
    SideBarEventsButtonAnim->start(QAbstractAnimation::DeleteWhenStopped);

}

void MainWindow::SetInterfaceStyle()
{
    //Кнопка закрытия приложения
    ui->CloseButton->setToolTip (tr ("Закрыть"));
    ui->CloseButton->setStyleSheet(MyStyleUI::GetCloseButtonsStyle());
    ui->CloseButton->setIconSize(QSize(20, 20));

    //Кнопка "развернуть на полный экран"
    ui->Maximized_NormalButton->setToolTip (tr ("Развернуть"));
    ui->Maximized_NormalButton->setStyleSheet(MyStyleUI::GetMaximized_NormalButtonsStyle());
    ui->Maximized_NormalButton->setIconSize(QSize(20, 20));

    //Кнопка сворачивания окна
    ui->MinimizedButton->setToolTip (tr ("Свернуть"));
    ui->MinimizedButton->setStyleSheet(MyStyleUI::GetMinimizedButtonStyle());
    ui->MinimizedButton->setIconSize(QSize(20, 20));

    //Кнопка удаления пользователя из базы данных
    ui->DelButton->setToolTip (tr ("Удалить"));
    ui->DelButton->setStyleSheet(MyStyleUI::GetDelButtonStyle());
    ui->DelButton->setIconSize(QSize(30, 30));

    //Кнопка добавления пользователя в базу данных
    ui->AddButton->setToolTip (tr ("Добавить"));
    ui->AddButton->setStyleSheet(MyStyleUI::GetAddButtonStyle());
    ui->AddButton->setIconSize(QSize(30, 30));

    //Блок кнопок на сайдбаре
    ui->UsersButton->setStyleSheet(MyStyleUI::GetSideBarButtonActiveStyle("icon: url(:/images/Resources/UsersActive.png)"));
    ui->UsersButton->setMinimumSize(55, 55);
    ui->UsersButton->setMaximumSize(55, 55);
    ui->UsersButton->setIconSize(QSize(50, 50));
    ui->EventsButton->setStyleSheet(MyStyleUI::GetSideBarButtonStyle("icon: url(:/images/Resources/Events.png)"));
    ui->EventsButton->setMinimumSize(55, 55);
    ui->EventsButton->setMaximumSize(55, 55);
    ui->EventsButton->setIconSize(QSize(50, 50));

    //Sidebar
    ui->Sidebar->setMinimumWidth(ui->EventsButton->minimumWidth());

    ui->frame->setStyleSheet(MyStyleUI::GetFrameStyle());
    ui->tableView->setStyleSheet(MyStyleUI::GetTableStyle());
    ui->NameProg->setStyleSheet(MyStyleUI::GetNameProgStyle());
    ui->Sidebar->installEventFilter(this);

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
        ui->UsersButton->setStyleSheet(MyStyleUI::GetSideBarButtonActiveStyle("icon: url(:/images/Resources/UsersActive.png)"));
        ui->EventsButton->setStyleSheet(MyStyleUI::GetSideBarButtonStyle("icon: url(:/images/Resources/Events.png)"));
    }
    else
    {
        ui->UsersButton->setStyleSheet(MyStyleUI::GetSideBarButtonStyle("icon: url(:/images/Resources/Users.png)"));
        ui->EventsButton->setStyleSheet(MyStyleUI::GetSideBarButtonActiveStyle("icon: url(:/images/Resources/EventsActive.png)"));
    }
}

void MainWindow::updateUsers()
{
    UserCardsModel->select();
}

void MainWindow::on_UsersButton_clicked()
{
    ChangeButtonStatus(1);
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_EventsButton_clicked()
{
    ChangeButtonStatus(2);
    ui->tabWidget->setCurrentIndex(1);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->Sidebar && event->type() == QEvent::Enter) {
        fSideBarAnim(250, 55, 220);
        ui->UsersButton->setText("Пользователи карт");
        ui->EventsButton->setText("Мероприятия");
        return true;
    }
    else if(watched == ui->Sidebar && event->type() == QEvent::Leave) {
        fSideBarAnim(250, 220, 55);
        ui->UsersButton->setText(NULL);
        ui->EventsButton->setText(NULL);
        return true;
    }
    else return false;
    return eventFilter(watched, event);
}
