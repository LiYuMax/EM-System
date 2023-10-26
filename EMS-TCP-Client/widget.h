#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QInputDialog>
#include <QTcpSocket>
#include <QPixmap>
#include <QIcon>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QTableView>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum OPTION{
    LOGIN = 0
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void showCheckMsg(QJsonObject checkMsg);
private slots:

    void on_pushButton_clicked();

    void on_loginBtn_clicked();

    void on_addBtn_clicked();

    void on_deleteBtn_clicked();

    void on_checkBtn_clicked();

    void on_modifyBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *socket;
    QWidget *childWidget;
    QWidget *addChildwidget;
    QWidget *deleteChildWidget;
    QLineEdit* userNamaeEdit;
    QLineEdit* passwdEdit;
    QPushButton* loginBtn;
    QLineEdit  *nameEdit;
    QLineEdit *genderEdit;
    QLineEdit *accountEdit;
    QLineEdit *passwordEdit;
    QLineEdit *jobEdit;
    QLineEdit *salaryEdit;
    QGridLayout *addLayout;
    QPushButton *adBtn;
    QLineEdit *deleteAccountEdit;
    QGridLayout *deleteLayout;
    QPushButton *deleteAccountBtn;
    QWidget *checkChildWidget;
    QLineEdit *checkAccountEdit;
    QGridLayout *checkLayout;
    QPushButton *checkAccountBtn;
    QJsonObject userMsg;
    QStandardItemModel *standItemModel;
    QTableView *tableView;
    QStandardItem *nameItem;
    QStandardItem *genderItem;
    QStandardItem *accountItem;
    QStandardItem *passwordItem;
    QStandardItem *jobItem;
    QStandardItem *salaryItem;
    QStandardItem *identityItem;
    QStandardItem *nameDataItem;
    QStandardItem *genderDataItem;
    QStandardItem *accountDataItem;
    QStandardItem *passwordDataItem;
    QStandardItem *jobDataItem;
    QStandardItem *salaryDataItem;
    QStandardItem *identityDataItem;
    QLineEdit *modifyNameEdit;
    QLineEdit *modifyPasswordEdit;
    QGridLayout *modifyLayout;
    QWidget *modifyChildWidget;
    QPushButton *modifyBtn;
    QWidget *modifyRootWidget;
    QPushButton *modifyRootBtn;
    QLineEdit  *modifyRootnameEdit;
    QLineEdit *modifyRootgenderEdit;
//    QLineEdit *modifyRootaccountEdit;
    QLineEdit *modifyRootpasswordEdit;
    QLineEdit *modifyRootjobEdit;
    QLineEdit *modifyRootsalaryEdit;
//    QLineEdit *modifyRootidentityEdit;
    QGridLayout *modifyRootLayout;
    QString checkAccount;
};
#endif // WIDGET_H
