#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_red_slider_valueChanged(int value);
    void on_green_slider_valueChanged(int value);
    void on_blue_slider_valueChanged(int value);
    void updateRGB(QString);

private:
    Ui::Dialog *ui;
    QSerialPort *avr;
    static const quint16 avr_vendor_id = 9025;
    static const quint16 avr_product_id = 67;
    QString avr_port_name;
    bool avr_is_available;
};

#endif // DIALOG_H
