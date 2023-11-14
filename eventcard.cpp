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

EventCard::EventCard(CalendarPage *ParentCalendarPage, QWidget *parent)
    : QWidget{parent}
{
    ResID++;
    EventID = ResID;
    PCalendarPage = ParentCalendarPage;

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
    //delete PCalendarPage;
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

int EventCard::IndexCell(QPoint WidgetPosition)
{
    if(PCalendarPage->GetXCoord(WidgetPosition) > -1) return (PCalendarPage->GridLayout->columnCount() - 1) * PCalendarPage->GetYCoord(WidgetPosition) + PCalendarPage->GetXCoord(WidgetPosition);
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
    if(leNumberOfSeats->text().toInt() > 0) bSignUp->setEnabled(true);
    else bSignUp->setEnabled(false);
    qDebug() << "Текст изменися";
}

void EventCard::onDelButtonClicked()
{
    //this->hide();
    this->deleteLater();
    PCalendarPage->DarkButton[IndexCell(geometry().center())]->show();
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

    //qDebug() << "Координата курсора " << event->pos();
    //qDebug() << "Позиция Card " << this->pos();
    //qDebug() << "Размер карточки: " << this->size();
    //qDebug() << "Индекс элемента в сетке: " << PCalendarPage->GridLayout->indexOf(this);
    //qDebug() << "Размер ScrollArea " << PCalendarPage->ScrollArea->size();
    //qDebug() << "Локальная позиция " << event->position();
    //qDebug() << "Позиция сцены " << event->scenePosition();
    //qDebug() << "Глобальная позиция " << event->globalPosition();
    //qDebug() << "Размер основного виджета: " << PCalendarPage->mw->size();
    //qDebug() << "Координата карточки " << geometry().center();
    //qDebug() << IndexCell(geometry().center());
    //qDebug() << "у координата: " << (PCalendarPage->GetXCoord(geometry().center()));
    //qDebug() << "x координата: " << (PCalendarPage->GetYCoord(geometry().center()));
}

void EventCard::SFHovered(QPoint WidgetPosition)
{
    if(PCalendarPage->GetXCoord(WidgetPosition) < 0) {
        PCalendarPage->DarkButton[buffPos]->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
    }
    //Проверяем находится ли виджет в ячейке под индексом i и выделяем его
    else  {
        if(PCalendarPage->DarkButton[IndexCell(WidgetPosition)]->geometry().contains(geometry().center())) {
            PCalendarPage->DarkButton[IndexCell(WidgetPosition)]->setStyleSheet(MyStyleUI::GetDarkButtonHoverStyle());
        }
        //Если предыдущий виджет (под индексом tempPos) не совпадает с нынешним, возвращаем старый цвет и присваиваем буферу новое значение
        if(PCalendarPage->DarkButton[buffPos] != PCalendarPage->DarkButton[IndexCell(WidgetPosition)]) {
            PCalendarPage->DarkButton[buffPos]->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
            buffPos = IndexCell(WidgetPosition);
        }
        if(PCalendarPage->mw->width() < WidgetPosition.x()) PCalendarPage->DarkButton[buffPos]->setStyleSheet(MyStyleUI::GetDarkButtonTransparentStyle());
    }
}

void EventCard::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton)) return;

    QPoint y = event->globalPos();
    QPoint x = y - this->z;
    this->move(x);

    for (int i = 0; i < PCalendarPage->Card.size(); ++i) {
        if(PCalendarPage->Card[i]->getID() == this->getID()) {
            PCalendarPage->GridLayout->removeWidget(PCalendarPage->Card[i]);
            break;
        }
    }

    SFHovered(geometry().center());

    //if(PCalendarPage->DarkButton[IndexCell(geometry().center())]->isHidden()) ;

    //int WidthHeader = PCalendarPage->lDayOfTheWeek[0]->width() + PCalendarPage->GridLayout->horizontalSpacing() + PCalendarPage->ScrollArea->contentsMargins().left();
    //int FieldWidth = PCalendarPage->ScrollArea->width() - WidthHeader;
    //int CellWidth = FieldWidth / (PCalendarPage->GridLayout->columnCount() - 1);
    //qDebug() << "Ширина ScrollArea: " << PCalendarPage->ScrollArea->width();
    //qDebug() << "Ширина заголовочника: " << WidthHeader;
    //qDebug() << "Ширина зоны ячеек: " << FieldWidth;
    //qDebug() << "Ширина ячейки: " << CellWidth;
    //qDebug() << "Координата центра карточки: " << geometry().center().x();
    //qDebug() << "Ширина заголовка: " << WidthHeader; //PCalendarPage->lDayOfTheWeek[0]->width();
    //qDebug() << IndexCell(geometry().center());
    //qDebug() << PCalendarPage->ShadowField[IndexCell(geometry().center())]->isHidden();
    //qDebug() << PCalendarPage->ScrollArea->geometry().width();
    //qDebug() << PCalendarPage->ShadowField[IndexCell(geometry().center())]->geometry().contains(geometry().center());
    //qDebug() << "у координата: " << (PCalendarPage->GetYCoord(geometry().center()));
    //qDebug() << "x координата: " << (PCalendarPage->GetXCoord(geometry().center()));
}

void EventCard::mouseReleaseEvent(QMouseEvent *event)
{
    unsetCursor();
    this-> z = QPoint(); // Конструктор инициализируется 0

    //Проверяем если под карточкой пустой слот вставляем ее в него и деактивируем его
    if(PCalendarPage->DarkButton[IndexCell(geometry().center())]->geometry().contains(geometry().center())
        && PCalendarPage->DarkButton[IndexCell(geometry().center())]->isHidden() == false) {
        PCalendarPage->GridLayout->addWidget(this, PCalendarPage->GetYCoord(geometry().center()), PCalendarPage->GetXCoord(geometry().center()) + 1);
        PCalendarPage->DarkButton[IndexCell(geometry().center())]->hide();
        /*if(GetXCoord(geometry().center()) >= 0)*/ PCalendarPage->DarkButton[PreviousPos]->show();
    }
    //Если карточка не помещена в ячейку, то она возвращается в предыдущую
    else {
        PCalendarPage->GridLayout->addWidget(this, PCalendarPage->GetYCoord(PCalendarPage->DarkButton[PreviousPos]->geometry().center()),
            PCalendarPage->GetXCoord(PCalendarPage->DarkButton[PreviousPos]->geometry().center()) + 1);
        PCalendarPage->DarkButton[PreviousPos]->hide();
    }
}
