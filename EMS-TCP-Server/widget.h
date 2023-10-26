#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTcpSocket>
#include <QPixmap>
#include <QIcon>
#include <QPushButton>
#include <QTcpServer>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QLineEdit>
#include <QGridLayout>
#include <QPixmap>
#include <QIcon>
#include <QLabel>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    void loginSignal(QTcpSocket* socket,QString account, QString password);

    void addSignal(QTcpSocket* socket,QString name,QString gender,QString account,QString password,QString
                   job,QString salary);

    void deleteSignal(QTcpSocket *socket, QString account);

    void modifySignal(QTcpSocket *socket,QJsonObject jsonObject);

    void checkSignal(QTcpSocket *socket, QString account);
private slots:
    void on_startBtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void login(QTcpSocket* socket,QString account, QString password);

    void add(QTcpSocket* socket,QString name,QString gender,QString account,QString password,QString
                                                                                                            job,QString salary);
    void Delete(QTcpSocket *socket, QString account);

    void Modify(QTcpSocket *socket,QJsonObject jsonObject);

    void Check(QTcpSocket *socket, QString account);
private:
    Ui::Widget *ui;
    QTcpServer *Server;
    QSqlDatabase *db;
    QLineEdit *accountEdit;
    QLineEdit *passwdEdit;
    QLineEdit *jobEdit;
    QLineEdit *salaryEdit;
    QLineEdit *nameEdit;
    QLineEdit *genderEdit;
    QPushButton *RootloginBtn;
    QPushButton *CommonloginBtn;
    QWidget *childWidget;
    QGridLayout* childlayout;
    QLabel *accountLabel;
    QLabel *passwordLabel;
};
#endif // WIDGET_H
