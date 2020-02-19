#include <QDebug>
#include <QMessageBox>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , client_(new QMqttClient(this))
{
    ui->setupUi(this);

    connect(client_, &QMqttClient::connected, this, &Widget::connected);
    connect(client_, &QMqttClient::disconnected, this, &Widget::disconnected);
    connect(client_, &QMqttClient::messageReceived, this, &Widget::messageReceived);
    connect(client_, &QMqttClient::messageSent, this, &Widget::messageSent);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::connected()
{
    qDebug() << __FUNCTION__;

    ui->pushButtonConnect->setText("Disconnect");

    ui->pushButtonPublish->setEnabled(true);
    ui->pushButtonSubscribe->setEnabled(true);
}

void Widget::disconnected()
{
    qDebug() << __FUNCTION__;

    ui->pushButtonConnect->setText("Connect");

    ui->pushButtonPublish->setEnabled(false);
    ui->pushButtonSubscribe->setEnabled(false);
}

void Widget::messageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << __FUNCTION__ << topic.name() << message;
    ui->plainTextEditSubscribePayload->setPlainText(message);
}

void Widget::messageSent(qint32 id)
{
    qDebug() << __FUNCTION__ << id;
}

void Widget::on_pushButtonConnect_clicked()
{
    if (ui->pushButtonConnect->text() == "Connect") {
        // connect
        if (ui->lineEditHost->text().isEmpty() || ui->lineEditPort->text().isEmpty()) {
            QMessageBox::critical(this, tr("Error"), tr("host and port must be set!"));
            return;
        }

        client_->setHostname(ui->lineEditHost->text());
        client_->setPort(ui->lineEditPort->text().toUInt());
        if (!ui->lineEditUser->text().isEmpty() || !ui->lineEditPassword->text().isEmpty()) {
            client_->setUsername(ui->lineEditUser->text());
            client_->setPassword(ui->lineEditPassword->text());
        }

        client_->connectToHost();
    } else {
        // disconnect
        client_->disconnectFromHost();
    }
}

void Widget::on_pushButtonSubscribe_clicked()
{
    if (ui->lineEditSubscribe->text().isEmpty()) {
        QMessageBox::critical(this, tr("Error"), tr("subscribe pattern must be set!"));
        return;
    }

    client_->subscribe(ui->lineEditSubscribe->text());
}

void Widget::on_pushButtonPublish_clicked()
{
    if (ui->lineEditTopic->text().isEmpty()) {
        QMessageBox::critical(this, tr("Error"), tr("publish topic must be set!"));
        return;
    }

    qint32 ret = client_->publish(ui->lineEditTopic->text(), ui->plainTextEditPublishPayload->toPlainText().toUtf8());
    qDebug() << "publish:" << ret;
}
