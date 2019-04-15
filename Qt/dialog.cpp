#include "dialog.h"
#include "ui_dialog.h"
#include "QSerialPort"
#include "QtSerialPort/QSerialPortInfo"
#include "QDebug"
 #include "QtWidgets"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    avr_port_name = "";
    avr_is_available = false;
    avr = new QSerialPort;

//    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
//    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
//    {
//        qDebug() << "Has vendor ID: " <<  serialPortInfo.hasVendorIdentifier();
//        if(serialPortInfo.hasVendorIdentifier())
//        {
//            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
//        }
//        qDebug() << "Has product ID: " <<  serialPortInfo.hasProductIdentifier();
//        if(serialPortInfo.hasProductIdentifier())
//        {
//            qDebug() << "product ID: " << serialPortInfo.productIdentifier();
//        }
//    }

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
        {
            if(serialPortInfo.vendorIdentifier() == avr_vendor_id && serialPortInfo.productIdentifier() == avr_product_id)
            {
                avr_port_name = serialPortInfo.portName();
                avr_is_available = true;
            }
            if(avr_is_available)
            {
                avr->setPortName(avr_port_name);
                avr->open(QSerialPort::WriteOnly);
                avr->setBaudRate(QSerialPort::Baud9600);
                avr->setDataBits(QSerialPort::Data8);
                avr->setParity(QSerialPort::NoParity);
                avr->setStopBits(QSerialPort::OneStop);
                avr->setFlowControl(QSerialPort::NoFlowControl);
            } else
            {
                QMessageBox::warning(this, "Port Error", "Arduino not found");
            }
        }
    }

}

Dialog::~Dialog()
{
    if(avr->isOpen())
    {
        avr->close();
    }
    delete ui;
}

void Dialog::on_red_slider_valueChanged(int value)
{
    ui->red_value_label->setText(QString("<span style=\" font-size:18pt; font-weight:600; color:#c7c7c7;\">%1</span>").arg(value));
    Dialog::updateRGB(QString("r%1").arg(value));
    qDebug() << value;
}

void Dialog::on_green_slider_valueChanged(int value)
{
    ui->green_value_label->setText(QString("<span style=\" font-size:18pt; font-weight:600; color:#c7c7c7;\">%1</span>").arg(value));
    Dialog::updateRGB(QString("g%1").arg(value));
    qDebug() << value;
}

void Dialog::on_blue_slider_valueChanged(int value)
{
    ui->blue_value_label->setText(QString("<span style=\" font-size:18pt; font-weight:600; color:#c7c7c7;\">%1</span>").arg(value));
    Dialog::updateRGB(QString("b%1").arg(value));
    qDebug() << value;
}

void Dialog::updateRGB(QString command)
{
    if(avr->isWritable())
    {
        avr->write(command.toStdString().c_str());
    } else
    {
        qDebug() << "Couldn't write to serial";
    }

}
