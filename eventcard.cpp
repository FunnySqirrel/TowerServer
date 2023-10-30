#include "eventcard.h"

#include <QApplication>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPalette>
#include <QPen>
#include <QStyleOption>

#define FONTSIZE 0
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

EventCard::EventCard(QWidget *parent)
    : QWidget{parent}
{
    MyStyleUI Style1;

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

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Text,Qt::red);
    leNameEvent = new QLineEdit(this);
    //leNameEvent->setFrame(false);
    leNameEvent->setPlaceholderText("Название мероприятия");
    leNameEvent->setStyleSheet(Style1.GetQlineStyle());
    leNameEvent->setFont(QFont("ARIALUNI", FONTSIZE));
    leNameEvent->setPalette(*palette);
    leNameEvent->setMaximumWidth(this->width() - 10);
    leNameEvent->setAlignment(Qt::AlignHCenter);

    lTimeEvent = new QLabel("Время:", this);
    lTimeEvent->setStyleSheet(Style1.GetQLabelCardStyle());
    lTimeEvent->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    leTimeEvent = new QLineEdit(this);
    leTimeEvent->setFrame(false);
    //leTimeEvent->setInputMask("00:00");
    leTimeEvent->setPlaceholderText("Время мероприятия");
    leTimeEvent->setStyleSheet(Style1.GetQlineStyle());

    lNumberOfSeats = new QLabel("Мест:");
    lNumberOfSeats->setStyleSheet(Style1.GetQLabelCardStyle());
    lNumberOfSeats->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    leNumberOfSeats = new QLineEdit(this);
    leNumberOfSeats->setFrame(false);
    //leNumberOfSeats->setPlaceholderText("Количество мест");
    leNumberOfSeats->setValidator(new QIntValidator(0, 100));
    //leNumberOfSeats->setInputMask("99");
    leNumberOfSeats->setStyleSheet(Style1.GetQlineStyle());
    connect(leNumberOfSeats, SIGNAL(textChanged(QString)), this, SLOT(on_leNumberOfSeatsTextChanged()));

    lRoom = new QLabel("Комната:");
    lRoom->setStyleSheet(Style1.GetQLabelCardStyle());
    lRoom->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    leRoom = new QLineEdit(this);
    leRoom->setFrame(false);
    leRoom->setPlaceholderText("Комната");
    leRoom->setStyleSheet(Style1.GetQlineStyle());

    lPriceEvent = new QLabel("Стоимость:");
    lPriceEvent->setStyleSheet(Style1.GetQLabelCardStyle());
    lPriceEvent->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    lePriceEvent = new QLineEdit(this);
    lePriceEvent->setFrame(false);
    //lePriceEvent->setPlaceholderText("Стоимость");
    lePriceEvent->setStyleSheet(Style1.GetQlineStyle());
    lePriceEvent->setFont(QFont("ARIALUNI", FONTSIZE, BOLD));

    bSignUp = new QPushButton(this);
    bSignUp->setText("Записать");
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

    teDescription = new QTextEdit(this);
    teDescription->setStyleSheet("Color: #5969BC;"
                             "font-family: ARIALUNI;"
                             "font-size: 13px;"
                             "background-color: #CBDFFF;"
                             ); //"alternate-background-color: rgb(255, 255, 255);"
    //QPalette *palette1 = new QPalette();
    //setAutoFillBackground(true);
    //palette1->setColor(QPalette::Base,QColor(155, 195, 255));
    //teDescription->setPalette(*palette1);

    VLayout = new QVBoxLayout(this);
    for (int i = 0; i < 4; ++i) {
        HLayout[i] = new QHBoxLayout(this);
        HLayout[i]->setSpacing(0);
    }
    VLayout->setSpacing(5);

    //VLayout->addLayout(HLayout[1]);
    //HLayout[0]->addWidget(lNameEvent);
    //HLayout[0]->addWidget(leNameEvent);
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

    VLayout->addWidget(bSignUp);
    VLayout->addWidget(teDescription);

    setLayout(VLayout);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(5, 5);
        //Shadow color
    shadow_effect->setColor(QColor(38, 78, 119, 175));
        //Shadow radius
    shadow_effect->setBlurRadius(25);
    setGraphicsEffect(shadow_effect);



    setWindowTitle(tr("Event Card"));
}

void EventCard::on_bSignUpClicked()
{
    QDialog *Registration = new QDialog(this);
    Registration->setWindowModality(Qt::WindowModality::ApplicationModal); //Запрещает взаимодействовать с главным окном пока открыто диалоговое
    //Registration->setMaximumSize(300, 200);
    Registration->setMinimumSize(300, 200);

    QVBoxLayout *VDialogLayout = new QVBoxLayout(Registration);
    QHBoxLayout *HDialogLayout = new QHBoxLayout(Registration);
    QLabel *lName = new QLabel("Введите имя или выберете из списка: ", Registration);
    QLineEdit *ldName = new QLineEdit();
    QComboBox *ComBox = new QComboBox(Registration);
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

    }
    qDebug() << "Координата виджета " << event->pos();
    qDebug() << "Позиция Card " << this->pos();
    //qDebug() << "Клик по виджету: " << geometry().contains(event->pos());

}

void EventCard::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton)) return;
    if ((event->pos() - DragStartPosition).manhattanLength() < QApplication::startDragDistance()) return;

    QPoint y = event->globalPos();
    QPoint x = y - this->z;

    IsMoving = true;
    this->move(x);

    if (IsMoving != true) z = QPoint ();

}

void EventCard::mouseReleaseEvent(QMouseEvent *event)
{
    unsetCursor();
    IsMoving = false;
    this-> z = QPoint(); // Конструктор инициализируется 0

}
