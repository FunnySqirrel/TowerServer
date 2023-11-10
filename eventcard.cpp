#include "eventcard.h"
#include "calendarpage.h"
#include "mystyleui.h"

#include <QApplication>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>
#include <QPen>
#include <QPushButton>
#include <QStyleOption>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QScrollArea>

#define FONTSIZE 10
#define BOLD QFont::Bold


void EventCard::paintEvent(QPaintEvent *event)
{
    //QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing, true);

    //Рисуем сам виджет
    //painter.setBrush(QColor("#CBDFFF"));                                      //"#CBDFFF"
    // Рисуем рамку вокруг виджета
    //painter.setPen(QPen(QColor("#00f"), 4));
    //painter.drawRect(0,0,this->rect().width(),this->rect().height());
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//Рекомендуемый размер виджета
QSize EventCard::sizeHint() const
{
    return QSize(166, 145);
}

EventCard::EventCard(CalendarPage *pcp, QWidget *parent)
    : QWidget{parent}
{
    ResID++;
    EventID = ResID;
    ParentCalendarPage = pcp;

    setStyleSheet("EventCard"
                  "{"
                  "background-color: #CBDFFF;"
                  "border-width: 1px;"
                  "border-style: solid;"
                  "border-color: #CBDFFF;"
                  "}"
                  "EventCard::hover"
                  "{"
                  "border-width: 2px;"
                  "border-style: outset;"
                  "border-color: red;"
                  "}");
    //Устанавливаем фиксированное значение размера виджета
    //this->setFixedWidth(165);
    //this->setFixedHeight(145);

    //lNameEvent = new QLabel(this);
    //lNameEvent->setText("Название:");
    //lNameEvent->setStyleSheet(Style1.GetQLabelCardStyle());
    //lNameEvent->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    palette = new QPalette();
    palette->setColor(QPalette::Text,Qt::red);
    leNameEvent = new QLineEdit(this);
    //leNameEvent->setFrame(false);
    leNameEvent->setPlaceholderText("Название");
    leNameEvent->setStyleSheet(MyStyleUI::GetQlineStyle());
    leNameEvent->setFont(QFont("ARIALUNI", FONTSIZE));
    leNameEvent->setPalette(*palette);
    leNameEvent->setMaximumWidth(width() * 0.75);
    leNameEvent->setAlignment(Qt::AlignHCenter);

    lTimeEvent = new QLabel("Время:", this);
    lTimeEvent->setStyleSheet(MyStyleUI::GetQLabelCardStyle());
    lTimeEvent->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    leTimeEvent = new QLineEdit(this);
    leTimeEvent->setFrame(false);
    //leTimeEvent->setInputMask("00:00");
    leTimeEvent->setPlaceholderText("Время мероприятия");
    leTimeEvent->setStyleSheet(MyStyleUI::GetQlineStyle());

    lNumberOfSeats = new QLabel("Мест:");
    lNumberOfSeats->setStyleSheet(MyStyleUI::GetQLabelCardStyle());
    lNumberOfSeats->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    leNumberOfSeats = new QLineEdit(this);
    leNumberOfSeats->setFrame(false);
    //leNumberOfSeats->setPlaceholderText("Количество мест");
    leNumberOfSeats->setValidator(new QIntValidator(0, 100));
    //leNumberOfSeats->setInputMask("99");
    leNumberOfSeats->setStyleSheet(MyStyleUI::GetQlineStyle());
    connect(leNumberOfSeats, SIGNAL(textChanged(QString)), this, SLOT(on_leNumberOfSeatsTextChanged()));

    lRoom = new QLabel("Комната:");
    lRoom->setStyleSheet(MyStyleUI::GetQLabelCardStyle());
    lRoom->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    leRoom = new QLineEdit(this);
    leRoom->setFrame(false);
    leRoom->setPlaceholderText("Комната");
    leRoom->setStyleSheet(MyStyleUI::GetQlineStyle());

    lPriceEvent = new QLabel("Стоимость:");
    lPriceEvent->setStyleSheet(MyStyleUI::GetQLabelCardStyle());
    lPriceEvent->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    lePriceEvent = new QLineEdit(this);
    lePriceEvent->setFrame(false);
    //lePriceEvent->setPlaceholderText("Стоимость");
    lePriceEvent->setStyleSheet(MyStyleUI::GetQlineStyle());
    lePriceEvent->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    bSignUp = new QPushButton(this);
    bSignUp->setText("Записать");
    //bSignUp->setMaximumWidth(width() - 10);
    bSignUp->setEnabled(false);
    bSignUp->setStyleSheet("QPushButton"
                          "{"
                          "font-family: ARIALUNI;"
                          "font-size: 13px;"
                          "border-width: 5px;"
                          "border-style: outset;"
                          "border-color: rgb(17, 150, 0);"
                          "border-radius: 10px;"
                          "background-color: rgb(75, 250, 50);"
                          "}"
                          "QPushButton::hover"
                          "{"
                          "border-width: 5px;"
                          "border-style: outset;"
                          "border-color: rgb(85, 255, 0);"
                          "background-color: rgb(75, 250, 50);"
                          "}"
                          "QPushButton::pressed"
                          "{"
                          "border-width: 5px;"
                          "border-style: inset;"
                          "border-color: rgb(67, 200, 0);"
                          "background-color:rgb(75, 250, 50);"
                          "}");
    connect(bSignUp, SIGNAL(clicked()), this, SLOT(on_bSignUpClicked()));

    Del = new QPushButton(this);
    Del->setStyleSheet(MyStyleUI::GetDelButtonStyle());
    Del->setMaximumSize(20, 20);
    connect(Del, SIGNAL(clicked()), this, SLOT(onDelButtonClicked()));

    teDescription = new QTextEdit(this);
    teDescription->setStyleSheet("Color: #5969BC;"
                             "font-family: ARIALUNI;"
                             "font-size: 13px;"
                                 //"background-color: #CDD3FF;"
                                 "border: solid;"
                                 "border-width: 1px;"
                                 "border-color: #4269A6;"
                             "background-color: #CBDFFF;"
                             ); //"alternate-background-color: rgb(255, 255, 255);"

    VLayout = new QVBoxLayout(this);
    for (int i = 0; i < 4; ++i) {
        HLayout[i] = new QHBoxLayout(this);
        HLayout[i]->setSpacing(0);
        //HLayout[i]->setContentsMargins(10, 0, 10, 0);
    }
    VLayout->setSpacing(5);
    VLayout->setContentsMargins(5, 5, 5, 5);

    VLayout->addLayout(HLayout[0]);
    //HLayout[0]->setSpacing(0);
    //HLayout[0]->setContentsMargins(0, 5, 5, 0);
    //HLayout[0]->addWidget(leNameEvent/*, Qt::AlignCenter*/);
    //HLayout[0]->addWidget(Del/*, Qt::AlignRight*/);
    HLayout[0]->addWidget(Del, 0, Qt::AlignRight);
    VLayout->addWidget(leNameEvent, 0, Qt::AlignCenter);

    VLayout->addLayout(HLayout[1]);
    HLayout[1]->addWidget(lTimeEvent);
    HLayout[1]->addWidget(leTimeEvent);

    VLayout->addLayout(HLayout[2]);
    HLayout[2]->addWidget(lRoom);
    HLayout[2]->addWidget(leRoom);

    VLayout->addLayout(HLayout[3]);
    HLayout[3]->addWidget(lNumberOfSeats);
    HLayout[3]->addWidget(leNumberOfSeats);
    HLayout[3]->addWidget(lPriceEvent);
    HLayout[3]->addWidget(lePriceEvent);

    VLayout->addWidget(bSignUp, Qt::AlignCenter);
    VLayout->addWidget(teDescription);

    setLayout(VLayout);

    shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(5, 5);
        //Shadow color
    shadow_effect->setColor(QColor(38, 78, 119, 175));
        //Shadow radius
    shadow_effect->setBlurRadius(25);
    setGraphicsEffect(shadow_effect);



    setWindowTitle(tr("Event Card"));
}

EventCard::~EventCard()
{
    //delete palette;
    //delete lNameEvent;
    //delete leNameEvent;
    //delete lTimeEvent;
    //delete leTimeEvent;
    //delete lRoom;
    //delete leRoom;
    //delete lNumberOfSeats;
    //delete leNumberOfSeats;
    //delete lPriceEvent;
    //delete lePriceEvent;
    //delete bSignUp;
    //delete teDescription;
    //delete VLayout;
    //delete HLayout[4];
    //delete Del;
    //delete shadow_effect;
    //delete ParentCalendarPage;
    //if(Registration != nullptr) {
    //delete Registration;
    //delete VDialogLayout;
    //delete HDialogLayout;
    //delete lName;
    //delete ldName;
    //delete ComBox;
    //delete DBB;
    //}
}

int EventCard::getID()
{
    return EventID;
}

/*Функция переводит координаты курсора в координаты сетки
Если курсор заходит на заголовок, то возвращаем -1
Если курсор попадает в остальную часть возвращаем индекс поля подсветки*/
int EventCard::GetXCoord(QPoint WidgetPosition)
{
    int WidthHeader = ParentCalendarPage->lDayOfTheWeek[0]->width() + ParentCalendarPage->GridLayout->horizontalSpacing() + ParentCalendarPage->ScrollArea->contentsMargins().left();
    int FieldWidth = ParentCalendarPage->mw->width() - WidthHeader;
    int CellWidth = FieldWidth / (ParentCalendarPage->GridLayout->columnCount() - 1);
    if(WidthHeader > WidgetPosition.x()) return -1;
    else if(ParentCalendarPage->mw->width() - 10 < WidgetPosition.x()) return ParentCalendarPage->GridLayout->columnCount() - 2;
    else return ((WidgetPosition.x() - WidthHeader)/ CellWidth);
}

int EventCard::GetYCoord(QPoint WidgetPosition)
{
    if(WidgetPosition.y() / height() < ParentCalendarPage->GridLayout->rowCount()) return WidgetPosition.y() / height();
    else return ParentCalendarPage->GridLayout->rowCount() - 1;
}

int EventCard::IndexCell(QPoint WidgetPosition)
{
    if(GetXCoord(WidgetPosition) != -1) return 5 * GetYCoord(WidgetPosition) + GetXCoord(WidgetPosition);
}

void EventCard::on_bSignUpClicked()
{
    Registration = new QDialog(this);
    Registration->setWindowModality(Qt::WindowModality::ApplicationModal); //Запрещает взаимодействовать с главным окном пока открыто диалоговое
    //Registration->setMaximumSize(300, 200);
    Registration->setMinimumSize(300, 200);

    VDialogLayout = new QVBoxLayout(Registration);
    HDialogLayout = new QHBoxLayout(Registration);
    lName = new QLabel("Введите имя или выберете из списка: ", Registration);
    ldName = new QLineEdit(Registration);
    ComBox = new QComboBox(Registration);
    ComBox->setLineEdit(ldName);

    QDialogButtonBox *DBB = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, Registration);
    DBB->button(QDialogButtonBox::Save)->setText("Сохранить");
    DBB->button(QDialogButtonBox::Cancel)->setText("Отменить");

    connect(DBB, SIGNAL(accepted()), Registration, SLOT(accept()));
    connect(DBB, SIGNAL(rejected()), Registration, SLOT(reject()));

    //Тест
    ComBox->addItems(QStringList()<<NULL<<"Миша"<<"Женя"<<"Саша");


    VDialogLayout->addLayout(HDialogLayout);
    HDialogLayout->addWidget(lName);
    HDialogLayout->addWidget(ComBox);
    VDialogLayout->addWidget(DBB);
    Registration->setLayout(VDialogLayout);
    Registration->show();

    if (Registration->exec() == QDialog::Accepted) {
        ++nCount;
        if(nCount > 1) Names += ", " + ComBox->currentText();
        else Names += ComBox->currentText();
        lNumberOfSeats->setToolTip(Names);
        leNumberOfSeats->setToolTip(Names);
        leNumberOfSeats->setText(QString::number(leNumberOfSeats->text().toInt() - 1));

    }
    else {

    }

}

void EventCard::on_leNumberOfSeatsTextChanged()
{
    //bool ok;
    if(leNumberOfSeats->text().toInt() > 0) bSignUp->setEnabled(true);
    else bSignUp->setEnabled(false);
    qDebug() << "Текст изменися";
}

void EventCard::onDelButtonClicked()
{
    //this->hide();
    this->deleteLater();
    ParentCalendarPage->DarkButton[IndexCell(geometry().center())]->show();
}

int EventCard::ResID = 0;


void EventCard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        DragStartPosition = event->pos();
        setCursor(Qt::ClosedHandCursor);

        QPoint y = event->globalPos();         // Положение мыши относительно левого верхнего угла рабочего стола, глобальное положение мыши
        QPoint x = this->geometry().topLeft(); // Положение левого верхнего угла окна относительно верхнего угла рабочего стола, положение окна
        this-> z =  y-x;                       // фиксированное значение, без изменений

        PreviousPos = IndexCell(geometry().center());
        buffPos = IndexCell(geometry().center());
    }

    //qDebug() << "Координата виджета " << event->pos();
    //qDebug() << "Позиция Card " << this->pos();
    //qDebug() << "Размер карточки: " << this->size();
    //qDebug() << "Индекс элемента в сетке: " << ParentCalendarPage->GridLayout->indexOf(this);
    //qDebug() << ParentCalendarPage->ScrollArea->size();
    //qDebug() << "Локальная позиция " << event->position();
    //qDebug() << "Позиция сцены " << event->scenePosition();
    //qDebug() << "Глобальная позиция " << event->globalPosition();
    //qDebug() << "Размер основного виджета: " << ParentCalendarPage->mw->height();
    //qDebug() << PreviousPos;
    qDebug() << "у координата: " << (GetXCoord(ParentCalendarPage->DarkButton[PreviousPos]->geometry().center()));
    qDebug() << "x координата: " << (GetYCoord(ParentCalendarPage->DarkButton[PreviousPos]->geometry().center()));
}

void EventCard::SFHovered(QPoint WidgetPosition)
{
    if(GetXCoord(WidgetPosition) < 0) {
        ParentCalendarPage->DarkButton[buffPos]->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
        //qDebug() << ParentCalendarPage->ShadowField[IndexCell(geometry().center())]->isHidden();
    }
    //Проверяем находится ли виджет в ячейке под индексом i и выделяем его
    else  {
        if(ParentCalendarPage->DarkButton[IndexCell(WidgetPosition)]->geometry().contains(this->geometry().center())) {
            ParentCalendarPage->DarkButton[IndexCell(WidgetPosition)]->setStyleSheet(MyStyleUI::GetDarkButtonHoverStyle());
            //qDebug() << ParentCalendarPage->ShadowField[IndexCell(geometry().center())]->isHidden();
        }
        //Если предыдущий виджет (под индексом tempPos) не совпадает с нынешним, возвращаем старый цвет и присваиваем буферу новое значение
        if(ParentCalendarPage->DarkButton[buffPos] != ParentCalendarPage->DarkButton[IndexCell(WidgetPosition)]) {
            ParentCalendarPage->DarkButton[buffPos]->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
            buffPos = IndexCell(WidgetPosition);
            //qDebug() << ParentCalendarPage->ShadowField[IndexCell(geometry().center())]->isHidden();
        }
        if(ParentCalendarPage->mw->width() < WidgetPosition.x()) ParentCalendarPage->DarkButton[buffPos]->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
    }
}

void EventCard::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton)) return;

    QPoint y = event->globalPos();
    QPoint x = y - this->z;
    this->move(x);

    for (int i = 0; i < ParentCalendarPage->Card.size(); ++i) {
        if(ParentCalendarPage->Card[i]->getID() == this->getID()) {
            ParentCalendarPage->GridLayout->removeWidget(ParentCalendarPage->Card[i]);
            break;
        }
    }

    SFHovered(geometry().center());

    //int WidthHeader = ParentCalendarPage->lDayOfTheWeek[0]->width() + ParentCalendarPage->GridLayout->horizontalSpacing() + ParentCalendarPage->ScrollArea->contentsMargins().left();
    //int FieldWidth = ParentCalendarPage->ScrollArea->width() - WidthHeader;
    //int CellWidth = FieldWidth / (ParentCalendarPage->GridLayout->columnCount() - 1);
    //qDebug() << "Ширина ScrollArea: " << ParentCalendarPage->ScrollArea->width();
    //qDebug() << "Ширина заголовочника: " << WidthHeader;
    //qDebug() << "Ширина зоны ячеек: " << FieldWidth;
    //qDebug() << "Ширина ячейки: " << CellWidth;
    //qDebug() << "Координата центра карточки: " << geometry().center().x();
    //qDebug() << "Ширина заголовка: " << WidthHeader; //ParentCalendarPage->lDayOfTheWeek[0]->width();
    //qDebug() << IndexCell(geometry().center());
    //qDebug() << ParentCalendarPage->ShadowField[IndexCell(geometry().center())]->isHidden();
    //qDebug() << ParentCalendarPage->ScrollArea->geometry().width();
    //qDebug() << GetXCoord(geometry().center());
    //qDebug() << ParentCalendarPage->ShadowField[IndexCell(geometry().center())]->geometry().contains(geometry().center());
}

void EventCard::mouseReleaseEvent(QMouseEvent *event)
{
    unsetCursor();
    this-> z = QPoint(); // Конструктор инициализируется 0

    //Проверяем если под карточкой пустой слот вставляем ее в него и деактивируем его
    if(ParentCalendarPage->DarkButton[IndexCell(geometry().center())]->geometry().contains(geometry().center())
        && ParentCalendarPage->DarkButton[IndexCell(geometry().center())]->isHidden() == false) {
        ParentCalendarPage->GridLayout->addWidget(this, GetYCoord(geometry().center()), GetXCoord(geometry().center()) + 1);
        ParentCalendarPage->DarkButton[IndexCell(geometry().center())]->hide();
        /*if(GetXCoord(geometry().center()) >= 0)*/ ParentCalendarPage->DarkButton[PreviousPos]->show();
    }
    //Если карточка не помещена в ячейку, то она возвращается в предыдущую
    else {
        ParentCalendarPage->GridLayout->addWidget(this, GetYCoord(ParentCalendarPage->DarkButton[PreviousPos]->geometry().center()),
            GetXCoord(ParentCalendarPage->DarkButton[PreviousPos]->geometry().center()) + 1);
        ParentCalendarPage->DarkButton[PreviousPos]->hide();
    }
}
