
#ifndef TABLE_H
#define TABLE_H


#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Table : public QWidget
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = nullptr);

    void SetHeader();
    void SetRow();
    void Column();
    void AddNewColumn();
    void AddNewRow();



private:
    QVBoxLayout* VLayout{nullptr};

    QWidget* Header;
    QList <QLabel*> HCell;
    QHBoxLayout* HeaderLayout;
    QFrame* Status;
    QWidget* Row;

signals:

};

#endif // TABLE_H
