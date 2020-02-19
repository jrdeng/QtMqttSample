#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtMqtt/QMqttClient>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void connected();
    void disconnected();
    void messageReceived(const QByteArray &message, const QMqttTopicName &topic = QMqttTopicName());
    void messageSent(qint32 id);

    void on_pushButtonConnect_clicked();

    void on_pushButtonSubscribe_clicked();

    void on_pushButtonPublish_clicked();

private:
    Ui::Widget *ui;
    QMqttClient *client_;
};
#endif // WIDGET_H
