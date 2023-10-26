#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Client");
    this->setFixedSize(350,250);
    this->setWindowIcon(QIcon(":/Jerry.png"));
    socket = new QTcpSocket;
    ui->pushButton->setFixedSize(70,30);
    ui->addBtn->setFixedSize(70,30);
    ui->deleteBtn->setFixedSize(70,30);
    ui->checkBtn->setFixedSize(70,30);
    ui->modifyBtn->setFixedSize(70,30);
    ui->pushButton->setText("连接");
    ui->addBtn->setText("添加");
    ui->deleteBtn->setText("删除");
    ui->modifyBtn->setText("修改");
    ui->checkBtn->setText("查询");
    ui->addBtn->setEnabled(false);
    ui->deleteBtn->setEnabled(false);
    ui->modifyBtn->setEnabled(false);
    ui->checkBtn->setEnabled(false);
    ui->cancelBtn->setEnabled(false);
    //连接服务器子窗口
    childWidget = new QWidget;
    childWidget->setWindowTitle("连接服务器");
    childWidget->setFixedSize(350,350);
    //添加用户子窗口
    addChildwidget = new QWidget;
    adBtn = new QPushButton;
    nameEdit = new QLineEdit;
    genderEdit = new QLineEdit;
    accountEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    jobEdit = new QLineEdit;
    salaryEdit = new QLineEdit;
    addLayout = new QGridLayout;
    adBtn->setText("确定添加");
    nameEdit->setPlaceholderText("姓名");
    genderEdit->setPlaceholderText("性别");
    accountEdit->setPlaceholderText("账号");
    passwordEdit->setPlaceholderText("密码");
    jobEdit->setPlaceholderText("职务");
    salaryEdit->setPlaceholderText("工资");
    addLayout->addWidget(nameEdit,0,1,1,2);
    addLayout->addWidget(genderEdit,1,1,1,2);
    addLayout->addWidget(accountEdit,2,1,1,2);
    addLayout->addWidget(passwordEdit,3,1,1,2);
    addLayout->addWidget(jobEdit,4,1,1,2);
    addLayout->addWidget(salaryEdit,5,1,1,2);
    addLayout->setHorizontalSpacing(10);
    addLayout->setVerticalSpacing(10);
    addLayout->setContentsMargins(20,20,20,20);
    addLayout->addWidget(adBtn,6,1,1,2);
    addChildwidget->setLayout(addLayout);
    //删除用户子窗口
    deleteChildWidget = new QWidget;
    deleteAccountEdit = new QLineEdit;
    deleteLayout = new QGridLayout;
    deleteAccountBtn = new QPushButton;
    deleteChildWidget->setWindowTitle("删除员工");
    deleteAccountBtn->setText("确定删除");
    deleteAccountEdit->setPlaceholderText("请输入想要删除的账号");
    deleteLayout->addWidget(deleteAccountEdit,0,1,1,2);
    deleteLayout->addWidget(deleteAccountBtn,1,1,1,2);
    deleteChildWidget->setLayout(deleteLayout);
    //root用户修改子窗口
    modifyRootWidget = new QWidget;
    modifyRootBtn = new QPushButton;
    modifyRootnameEdit = new QLineEdit;
    modifyRootgenderEdit = new QLineEdit;
    modifyRootpasswordEdit = new QLineEdit;
    modifyRootjobEdit = new QLineEdit;
    modifyRootsalaryEdit = new QLineEdit;
    modifyRootLayout = new QGridLayout;
    modifyRootBtn->setText("确定修改");
    modifyRootnameEdit->setPlaceholderText("姓名");
    modifyRootgenderEdit->setPlaceholderText("性别");
    modifyRootpasswordEdit->setPlaceholderText("密码");
    modifyRootjobEdit->setPlaceholderText("职务");
    modifyRootsalaryEdit->setPlaceholderText("工资");
    modifyRootLayout->addWidget(modifyRootnameEdit,0,1,1,2);
    modifyRootLayout->addWidget(modifyRootgenderEdit,1,1,1,2);
    modifyRootLayout->addWidget(modifyRootpasswordEdit,2,1,1,2);
    modifyRootLayout->addWidget(modifyRootjobEdit,3,1,1,2);
    modifyRootLayout->addWidget(modifyRootsalaryEdit,4,1,1,2);
    modifyRootLayout->addWidget(modifyRootBtn,5,1,1,2);
    modifyRootLayout->setHorizontalSpacing(10);
    modifyRootLayout->setVerticalSpacing(10);
    modifyRootLayout->setContentsMargins(20,20,20,20);
    modifyRootWidget->setLayout(modifyRootLayout);
    //普通用户修改子窗口
    modifyNameEdit = new QLineEdit;
    modifyPasswordEdit = new QLineEdit;
    modifyLayout = new QGridLayout;
    modifyChildWidget = new QWidget;
    modifyBtn = new QPushButton;
    modifyBtn->setText("确定修改");
    modifyNameEdit->setPlaceholderText("输入想要修改的姓名");
    modifyPasswordEdit->setPlaceholderText("输入想要修改的密码");
    modifyLayout->addWidget(modifyNameEdit,0,1,1,2);
    modifyLayout->addWidget(modifyPasswordEdit,1,1,1,2);
    modifyLayout->addWidget(modifyBtn,2,1,1,2);
    modifyChildWidget->setLayout(modifyLayout);
    //root用户查询子窗口
    checkChildWidget = new QWidget;
    checkAccountEdit = new QLineEdit;
    checkLayout = new QGridLayout;
    checkAccountBtn = new QPushButton;
    checkChildWidget->setWindowTitle("查询");
    checkAccountBtn->setText("查询");
    checkAccountEdit->setPlaceholderText("请输入想要查询的账号");
    checkLayout->addWidget(checkAccountEdit,0,1,1,2);
    checkLayout->addWidget(checkAccountBtn,1,1,1,2);
    checkChildWidget->setLayout(checkLayout);
    //初始化查询结果表格
    //item无法通过deletelater释放
    standItemModel = new QStandardItemModel(7,2);
    tableView = new QTableView;
    nameItem = new QStandardItem("姓名");
    genderItem = new QStandardItem("性别");
    accountItem = new QStandardItem("账号");
    passwordItem = new QStandardItem("密码");
    jobItem = new QStandardItem("职务");
    salaryItem = new QStandardItem("工资");
    identityItem = new QStandardItem("权限");
    nameDataItem = new QStandardItem;
    genderDataItem = new QStandardItem;
    accountDataItem = new QStandardItem;
    passwordDataItem = new QStandardItem;
    jobDataItem = new QStandardItem;
    salaryDataItem = new QStandardItem;
    identityDataItem = new QStandardItem;
    standItemModel->setItem(0,0,nameItem);
     standItemModel->setItem(1,0,genderItem);
     standItemModel->setItem(2,0,accountItem);
    standItemModel->setItem(3,0,passwordItem);
     standItemModel->setItem(4,0,jobItem);
     standItemModel->setItem(5,0,salaryItem);
     standItemModel->setItem(6,0,identityItem);
     //检测连接服务器是否成功
     connect(socket,&QTcpSocket::connected,this,[=](){qDebug()<<"成功连接服务器";});
    //发送添加请求
     connect(adBtn,&QPushButton::clicked,this,[=]()
     {
         if(nameEdit->text().isEmpty() || genderEdit->text().isEmpty() || accountEdit->text().isEmpty()
             || passwdEdit->text().isEmpty() || jobEdit->text().isEmpty() || salaryEdit->text().isEmpty())
         {
             QMessageBox::information(addChildwidget,"提示","添加内容不能为空",QMessageBox::Ok);
             return;
         }
        QJsonObject jsonObject;
        jsonObject.insert("option",1);
        jsonObject.insert("name",nameEdit->text());
        jsonObject.insert("gender",genderEdit->text());
        jsonObject.insert("account",accountEdit->text());
        jsonObject.insert("password",passwdEdit->text());
        jsonObject.insert("job",jobEdit->text());
        jsonObject.insert("salary",salaryEdit->text());
        QJsonDocument jsonDocument(jsonObject);
        socket->write(jsonDocument.toJson());
     });
     //发送删除请求
     connect(deleteAccountBtn,&QPushButton::clicked,this,[=]()
     {
         if(deleteAccountEdit->text().isEmpty())
         {
             QMessageBox::information(deleteChildWidget,"提示","账号不能为空",QMessageBox::Ok);
             return;
         }
        QJsonObject jsonObject;
        jsonObject.insert("option",2);
        jsonObject.insert("account",deleteAccountEdit->text());
        QJsonDocument jsonDocument(jsonObject);
        socket->write(jsonDocument.toJson());
    });
    //root用户发送修改请求
    connect(modifyRootBtn,&QPushButton::clicked,this,[=]()
    {
       QJsonObject jsonObject;
       if(modifyRootnameEdit->text().isEmpty() || modifyRootgenderEdit->text().isEmpty() ||
          modifyRootpasswordEdit->text().isEmpty() || modifyRootjobEdit->text().isEmpty() ||
          modifyRootsalaryEdit->text().isEmpty() )
       {
           QMessageBox::information(modifyRootWidget,"提示","修改内容不能为空",QMessageBox::Ok);
           return;
       }
       jsonObject.insert("option",3);
       jsonObject.insert("request","modify");
       jsonObject.insert("name",modifyRootnameEdit->text());
       jsonObject.insert("gender",modifyRootgenderEdit->text());
       jsonObject.insert("account",checkAccount);
       jsonObject.insert("password",modifyRootpasswordEdit->text());
       jsonObject.insert("job",modifyRootjobEdit->text());
       jsonObject.insert("salary",modifyRootsalaryEdit->text());
       jsonObject.insert("identity","root");
       socket->write(QJsonDocument(jsonObject).toJson());
       modifyRootWidget->close();
    });
    //common用户发送修改请求
    connect(modifyBtn,&QPushButton::clicked,this,[=]()
    {
        if(modifyNameEdit->text().isEmpty() || modifyPasswordEdit->text().isEmpty())
        {
            QMessageBox::information(modifyChildWidget,"提示","修改内容不能为空",QMessageBox::Ok);
            return;
        }
       QJsonObject jsonObject;
       jsonObject.insert("option",3);
       jsonObject.insert("account",userMsg.value("account").toString());
       jsonObject.insert("identity",userMsg.value("identity").toString());
       jsonObject.insert("name",modifyNameEdit->text());
       jsonObject.insert("password",modifyPasswordEdit->text());
       socket->write(QJsonDocument(jsonObject).toJson());
    });
    //root用户发送查询请求
    connect(checkAccountBtn,&QPushButton::clicked,this,[=]()
    {
        QJsonObject jsonObject;
        jsonObject.insert("option",4);
        jsonObject.insert("account",checkAccountEdit->text());
        QJsonDocument jsonDocument(jsonObject);
        socket->write(jsonDocument.toJson());
    });
    //处理返回信息
    connect(socket,&QTcpSocket::readyRead,this,[=]()
    {
        QByteArray data = socket->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonDocument.object();
        int option = jsonObject.value("option").toInt();
        switch(option)
        {
            case 0://处理登录回信
                if(jsonObject.value("result").toString() == "success")
                {
                    userMsg = jsonObject;
                    ui->loginBtn->setEnabled(false);
                    ui->cancelBtn->setEnabled(true);
                    if(userMsg.value("identity").toString() == QString("root"))//root用户
                    {
                        ui->addBtn->setEnabled(true);
                        ui->deleteBtn->setEnabled(true);
                        ui->modifyBtn->setEnabled(true);
                        ui->checkBtn->setEnabled(true);
                    }else if(userMsg.value("identity").toString() == QString("common"))//普通用户
                    {
                        ui->modifyBtn->setEnabled(true);
                        ui->checkBtn->setEnabled(true);
                    }
                }else if(jsonObject.value("result").toString() == "fail")
                {
                    qDebug()<<"登录失败";
                    return;
                }
                break;
             case 1://处理添加回信
                if(jsonObject.value("result").toString() == QString("添加成功"))
                {
                    QMessageBox::information(addChildwidget,"提示","添加成功",QMessageBox::Ok);
                    addChildwidget->close();
                }else
                {
                    QMessageBox::information(addChildwidget,"提示","添加失败",QMessageBox::Ok);
                    addChildwidget->close();
                }
                break;
             case 2://处理删除回信
                if(jsonObject.value("result").toBool() == true)
                {
                    QMessageBox::information(deleteChildWidget,"提示","删除成功",QMessageBox::Ok);
                    deleteChildWidget->close();
                }else if(jsonObject.value("result").toBool() == false)
                {
                    QMessageBox::information(deleteChildWidget,"提示","删除失败",QMessageBox::Ok);
                    deleteChildWidget->close();
                }
                break;
             case 3://处理修改回信
                if(userMsg.value("identity").toString() == "common")
                {
                    if(jsonObject.value("result").toBool() == true)
                    {
                        QMessageBox::information(nullptr,"提示","修改成功",QMessageBox::Ok);
                    }else
                    {
                        QMessageBox::information(nullptr,"提示","修改失败",QMessageBox::Ok);
                    }
                }else if(userMsg.value("identity").toString() == "root")
                {
                    if(jsonObject.value("request").toString() == "message")
                    {
                        if(jsonObject.value("result").toBool() == true)
                        {
                            modifyRootnameEdit->setText(jsonObject.value("name").toString());
                            modifyRootgenderEdit->setText(jsonObject.value("gender").toString());
                            modifyRootpasswordEdit->setText(jsonObject.value("password").toString());
                            modifyRootjobEdit->setText(jsonObject.value("job").toString());
                            modifyRootsalaryEdit->setText(jsonObject.value("salary").toString());
                            modifyRootWidget->show();
                        }else if(jsonObject.value("result").toBool() == false)
                        {
                            qDebug()<<"false-message";
                        }
                    }else if(jsonObject.value("request").toString() == "modify")
                    {
                        if(jsonObject.value("result").toBool() == true)
                        {
                            QMessageBox::information(nullptr,"提示","修改成功",QMessageBox::Ok);
                        }else if(jsonObject.value("result").toBool() == false)
                        {
                            QMessageBox::information(nullptr,"提示","修改失败",QMessageBox::Ok);
                        }
                    }
                }
                break;
             case 4://处理root用户查询回信
                if(jsonObject.value("result").toBool() == true)
                {
                    showCheckMsg(jsonObject);
                    QMessageBox::information(deleteChildWidget,"提示","查询成功",QMessageBox::Ok);
                    checkChildWidget->close();
                }else if(jsonObject.value("result").toBool() == false)
                {
                    QMessageBox::information(deleteChildWidget,"提示","查询失败",QMessageBox::Ok);
                    checkChildWidget->close();
                }
                break;
        }
    });

}

Widget::~Widget()
{
    delete ui;
    socket->deleteLater();
    childWidget->deleteLater();
    addChildwidget->deleteLater();
    nameEdit->deleteLater();
    genderEdit->deleteLater();
    accountEdit->deleteLater();
    passwordEdit->deleteLater();
    jobEdit->deleteLater();
    salaryEdit->deleteLater();
    addLayout->deleteLater();
    adBtn->deleteLater();
    deleteChildWidget->deleteLater();
    deleteAccountEdit->deleteLater();
    deleteLayout->deleteLater();
    checkAccountBtn->deleteLater();
    checkAccountEdit->deleteLater();
    checkChildWidget->deleteLater();
    checkLayout->deleteLater();
    standItemModel->deleteLater();
    tableView->deleteLater();
    modifyNameEdit->deleteLater();
    modifyPasswordEdit->deleteLater();
    modifyLayout->deleteLater();
    modifyChildWidget->deleteLater();
    modifyBtn->deleteLater();
    modifyRootBtn->deleteLater();
    modifyRootWidget->deleteLater();
    modifyRootnameEdit->deleteLater();
    modifyRootgenderEdit->deleteLater();
    modifyRootpasswordEdit->deleteLater();
    modifyRootjobEdit->deleteLater();
    modifyRootsalaryEdit->deleteLater();
    modifyRootLayout->deleteLater();
    delete nameDataItem;
    delete genderDataItem;
    delete accountDataItem;
    delete passwordDataItem;
    delete jobDataItem;
    delete salaryDataItem;
    delete identityDataItem;
}

void Widget::showCheckMsg(QJsonObject checkMsg)
{
    nameDataItem->setText(checkMsg.value("name").toString());
    genderDataItem->setText(checkMsg.value("gender").toString());
    accountDataItem->setText(checkMsg.value("account").toString());
    passwordDataItem->setText(checkMsg.value("password").toString());
    jobDataItem->setText(checkMsg.value("job").toString());
    salaryDataItem->setText(checkMsg.value("salary").toString());
    identityDataItem->setText(checkMsg.value("identity").toString());
    standItemModel->setItem(0,1,nameDataItem);
    standItemModel->setItem(1,1,genderDataItem);
    standItemModel->setItem(2,1,accountDataItem);
    standItemModel->setItem(3,1,passwordDataItem);
    standItemModel->setItem(4,1,jobDataItem);
    standItemModel->setItem(5,1,salaryDataItem);
    standItemModel->setItem(6,1,identityDataItem);
    tableView->setModel(standItemModel);
    tableView->show();
}




//连接服务器
void Widget::on_pushButton_clicked()
{
    QLabel* imageLabel = new QLabel;
    userNamaeEdit = new QLineEdit;
    passwdEdit = new QLineEdit;
    QCheckBox* rememberCheckBox = new QCheckBox;
    QCheckBox* autoLoginCheckBox = new QCheckBox;
    QPushButton* registerBtn = new QPushButton;
    QPushButton* forgetBtn = new QPushButton;
    loginBtn = new QPushButton;
    connect(loginBtn,&QPushButton::clicked,this,[=]()
    {
                QString ip = userNamaeEdit->text();
                unsigned short port = passwdEdit->text().toUShort();
                socket->connectToHost(QHostAddress(ip),port);
                qDebug()<<"ip="<<ip<<"port="<<port;
                if(socket->waitForConnected())
                {
                    QAbstractSocket::SocketState  currentState = socket->state();
                     if(currentState == QAbstractSocket::ConnectedState)
                     {
                        QMessageBox::information(childWidget,"提示","连接成功",QMessageBox::Ok);
                         childWidget->close();
                     }else
                    {
                         QMessageBox::information(childWidget,"提示","连接失败",QMessageBox::Ok);
                        return;
                     }
                }

            });
    imageLabel->setFixedSize(90,90);
    imageLabel->setPixmap(QPixmap(":/Tom.png"));
    imageLabel->setScaledContents(true);
    userNamaeEdit->setPlaceholderText("ip地址");
    passwdEdit->setPlaceholderText("端口号port");
    userNamaeEdit->setText("127.0.0.1");
    passwdEdit->setText("8888");
    rememberCheckBox->setText("记住密码");
    autoLoginCheckBox->setText("自动登录");
    registerBtn->setText("注册账号");
    forgetBtn->setText("找回密码");
    loginBtn->setText("连接");
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(imageLabel,0,0,3,1);
    layout->addWidget(userNamaeEdit,0,1,1,2);
    layout->addWidget(registerBtn,0,3);
    layout->addWidget(passwdEdit,1,1,1,2);
    layout->addWidget(forgetBtn,1,3);
    layout->addWidget(rememberCheckBox,2,1);
    layout->addWidget(autoLoginCheckBox,2,2);
    layout->addWidget(loginBtn,3,1,1,2);
    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(10);
    layout->setContentsMargins(20,20,20,20);
    childWidget->setLayout(layout);
    childWidget->show();
}
//登录
void Widget::on_loginBtn_clicked()
{
    QAbstractSocket::SocketState  curState = socket->state();
    if(curState == QAbstractSocket::UnconnectedState)
    {
        QMessageBox::information(this,"提示","请先连接服务器再登录...",QMessageBox::Ok);
        return;
    }
    QJsonObject jsonMsg;
    jsonMsg.insert("option",OPTION::LOGIN);
    jsonMsg.insert("account",ui->accountEdit->text());
    jsonMsg.insert("password",ui->passwordEdit->text());
    QJsonDocument jsonDocument(jsonMsg);
    socket->write(jsonDocument.toJson());
}
//添加
void Widget::on_addBtn_clicked()
{
    nameEdit->clear();
    genderEdit->clear();
    accountEdit->clear();
    passwdEdit->clear();
    jobEdit->clear();
    salaryEdit->clear();
    addChildwidget->move((this->x()+(this->width()-addChildwidget->width())/2),this->y());
    addChildwidget->show();
}
//删除
void Widget::on_deleteBtn_clicked()
{
    deleteAccountEdit->clear();
    deleteChildWidget->show();
}
//查询
void Widget::on_checkBtn_clicked()
{
    if(userMsg.value("identity").toString() == "root")
    {
        checkAccountEdit->clear();
        checkChildWidget->show();
    }else if(userMsg.value("identity").toString() == "common")
    {
        showCheckMsg(userMsg);
    }
}
//修改
void Widget::on_modifyBtn_clicked()
{
    if(userMsg.value("identity").toString() == "root")
    {
        bool ok;
        QJsonObject jsonObject;
        checkAccount = QInputDialog::getText(this,"修改","请输入想要修改的账号",QLineEdit::Normal,"",&ok);
        if(ok && checkAccount.isEmpty())
        {
            qDebug()<<"账号不能为空,请重新输入";
        }else if(ok && !checkAccount.isEmpty())
        {
            jsonObject.insert("option",3);
            jsonObject.insert("request","message");
            jsonObject.insert("account",checkAccount);
            jsonObject.insert("identity",userMsg.value("identity"));
            socket->write(QJsonDocument(jsonObject).toJson());

        }
    }else if(userMsg.value("identity").toString() == "common")
    {
        modifyNameEdit->setText(userMsg.value("name").toString());
        modifyPasswordEdit->setText(userMsg.value("password").toString());
        modifyChildWidget->show();
    }
}
//注销
void Widget::on_cancelBtn_clicked()
{
    ui->accountEdit->clear();
    ui->passwordEdit->clear();
    ui->loginBtn->setEnabled(true);
    ui->cancelBtn->setEnabled(false);
    ui->addBtn->setEnabled(false);
    ui->deleteBtn->setEnabled(false);
    ui->checkBtn->setEnabled(false);
    ui->modifyBtn->setEnabled(false);
}

