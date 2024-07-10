
#include "table.h"
#include "mystyleui.h"

#include <QLineEdit>

Table::Table(QWidget *parent)
    : QWidget{parent}
{
    VLayout = new QVBoxLayout();
    setLayout(VLayout);
    SetHeader();
    VLayout->addWidget(Header);

}

void Table::SetHeader()
{
    Header = new QWidget();
    HeaderLayout = new QHBoxLayout(Header);
    Header->setLayout(HeaderLayout);
    Header->setContentsMargins(0, 0, 0, 3);
    HeaderLayout->setContentsMargins(0, 0, 0, 0);
    HeaderLayout->setSpacing(2);

    HCell.reserve(8);
    QLabel* ID = new QLabel(Header);
    ID->setText("ID");
    HCell.push_back(ID);

    QLabel* HName = new QLabel(Header);
    HName->setText("Имя");
    HCell.push_back(HName);

    QLabel* HBDate = new QLabel(Header);
    HBDate->setText("Дата рождения");
    HCell.push_back(HBDate);

    QLabel* Email = new QLabel(Header);
    Email->setText("Почта");
    HCell.push_back(Email);

    QLabel* Pass = new QLabel(Header);
    Pass->setText("Пароль");
    HCell.push_back(Pass);

    QLabel* Points = new QLabel(Header);
    Points->setText("Баллы");
    HCell.push_back(Points);

    QLabel* Status = new QLabel(Header);
    Status->setText("Статус");
    HCell.push_back(Status);

    for (auto &&Label : HCell) {
        Label->setStyleSheet(MyStyleUI::GetTableHeaderLabelStyle());
        Label->setAlignment(Qt::AlignCenter);
        HeaderLayout->addWidget(Label);
    };
}

void Table::SetRow()
{
    Row = new QWidget();
    QVBoxLayout* VRowLayout = new QVBoxLayout();
    VRowLayout->setContentsMargins(2, 5, 2, 5);
    VRowLayout->setSpacing(2);
    Row->setLayout(VRowLayout);

    QLineEdit* C1 = new QLineEdit(Row);
    QLineEdit* C2 = new QLineEdit(Row);
    QLineEdit* C3 = new QLineEdit(Row);
    C3->setInputMask("99.99");
    QLineEdit* C4 = new QLineEdit(Row);
    C4->setPlaceholderText("example@mail.ru");
    QLineEdit* C5 = new QLineEdit(Row);
    C5->setEchoMode(QLineEdit::Password);
}

