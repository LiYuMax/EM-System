#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/Tom.png"));
    //初始化
    Server = new QTcpServer;
    db = new QSqlDatabase;
    accountEdit = new QLineEdit;
    passwdEdit = new QLineEdit;
    jobEdit = new QLineEdit;
    salaryEdit = new QLineEdit;
    nameEdit = new QLineEdit;
    genderEdit = new QLineEdit;
    RootloginBtn = new QPushButton;
    CommonloginBtn = new QPushButton;
    childWidget = new QWidget;
    childlayout = new QGridLayout;
    accountLabel = new QLabel;
    passwordLabel = new QLabel;
    //方便测试
    ui->portLine->setText("8888");
    //子窗口布局
    childWidget->setWindowIcon(QIcon(":/Mickey Mouse.png"));
    childWidget->setFixedSize(300,250);
    RootloginBtn->setText("注册root");
    CommonloginBtn->setText("注册common");
    accountEdit->setPlaceholderText("账号");
    passwdEdit->setPlaceholderText("密码");
    jobEdit->setPlaceholderText("职位");
    salaryEdit->setPlaceholderText("工资");
    nameEdit->setPlaceholderText("姓名");
    genderEdit->setPlaceholderText("性别");
    childlayout->addWidget(nameEdit,0,1,1,2);
    childlayout->addWidget(genderEdit,1,1,1,2);
    childlayout->addWidget(accountEdit,2,1,1,2);
    childlayout->addWidget(passwdEdit,3,1,1,2);
    childlayout->addWidget(jobEdit,4,1,1,2);
    childlayout->addWidget(salaryEdit,5,1,1,2);
    childlayout->setHorizontalSpacing(10);
    childlayout->setVerticalSpacing(10);
    childlayout->setContentsMargins(20,20,20,20);
    childWidget->setLayout(childlayout);
    //创建数据库
    (*db) = QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("dataBase.db");
    if(!db->open())
    {
        qDebug()<<"打开数据库失败:"<<db->lastError();
    }
    //删除原表
    QSqlQuery query;
    if(!query.exec("DROP TABLE loginmsg"))
    {
        qDebug()<<"初始化删表失败"<<query.lastError();
    }
    else
    {
        qDebug()<<"初始化删表成功";
    }
     QStringList tables = db->tables();
    //创建新表loginmsg
    if(tables.contains("loginmsg"))
    {
        qDebug()<<"表loginmsg已存在，不需要再创建";
    } else
    {
       bool ret = query.exec("CREATE TABLE loginmsg (name TEXT, gender TEXT, account TEXT PRIMARY KEY, password TEXT, job TEXT, salary INT, identity TEXT)");
       if(false == ret)
       {
            qDebug()<<"表loginmsg创建失败:"<<query.lastError();
            return;
       }else
       {
            qDebug()<<"表loginmsg创建成功";
       }
    }
    //每次使用前清空数据库表
    if (!query.exec("DELETE FROM loginmsg")) {
       qDebug() << "清空表loginmsg失败" << query.lastError();
    } else {
       qDebug() << "表清空loginmsg成功";
    }
    db->close();
    //注册root用户
    connect(RootloginBtn,&QPushButton::clicked,this,[=]()
    {
        if (!db->open())
        {
            qDebug()<<"数据库打开失败"<<db->lastError();
            return;
        }
        QSqlQuery query;
        query.prepare("INSERT INTO loginmsg (name, gender, account, password, job, salary, identity) VALUES (:name, :gender, :account, :password, :job, :salary, :identity)");
        query.bindValue(":name",nameEdit->text());
        query.bindValue(":gender",genderEdit->text());
        query.bindValue(":account", accountEdit->text());
        query.bindValue(":password", passwdEdit->text());
        query.bindValue(":job",jobEdit->text());
        query.bindValue(":salary",salaryEdit->text().toInt());
        query.bindValue(":identity", "root");
        if (!query.exec())
        {
            QMessageBox::information(childWidget, "提示", "注册失败", QMessageBox::Ok);
            qDebug()<<query.lastError();
            return;
        }else
        {
             QMessageBox::information(childWidget, "提示", "注册成功", QMessageBox::Ok);
             childWidget->close();
        }
        db->close();
    });
    //注册普通用户
    connect(CommonloginBtn,&QPushButton::clicked,this,[=]()
    {
        if(!db->open())
       {
            qDebug()<<"数据库打开失败"<<db->lastError();
            return;
        }
        QSqlQuery query;
        query.prepare("INSERT INTO loginmsg (name, gender, account, password, job, salary, identity) values (:name, :gender, :account, :password, :job, :salary, :identity)");
        query.bindValue(":name",nameEdit->text());
        query.bindValue(":gender",genderEdit->text());
        query.bindValue(":account",accountEdit->text());
        query.bindValue(":password",passwdEdit->text());
        query.bindValue(":job",jobEdit->text());
        query.bindValue(":salary",salaryEdit->text().toInt());
        query.bindValue(":identity","common");
        if (!query.exec()) {
            QMessageBox::information(childWidget, "提示", "注册失败", QMessageBox::Ok);
            qDebug()<<query.lastError();
            return;
       }else
       {
            QMessageBox::information(childWidget, "提示", "注册成功", QMessageBox::Ok);
            childWidget->close();
       }
                db->close();
    });
    //注册登录请求
    connect(this,&Widget::loginSignal,this,&Widget::login);
    //注册添加请求
    connect(this,&Widget::addSignal,this,&Widget::add);
    //注册删除请求
    connect(this,&Widget::deleteSignal,this,&Widget::Delete);
    //注册修改请求
    connect(this,&Widget::modifySignal,this,&Widget::Modify);
    //注册查询请求
    connect(this,&Widget::checkSignal,this,&Widget::Check);
    //与客户端建立连接
    connect(Server,&QTcpServer::newConnection,this,[=]()
    {
        qDebug()<<"有新客户端连接";
        //创建一个新套接字接收新连接，与之交互
        QTcpSocket *newSocket = new QTcpSocket;
        newSocket = Server->nextPendingConnection();
        //处理断开连接
        connect(newSocket,&QTcpSocket::disconnected,this,[=]()
        {
            qDebug()<<"有客户端断开连接...";
            newSocket->deleteLater();
        });
        //处理接收信息
        connect(newSocket,&QTcpSocket::readyRead,this,[=]()
        {
            QByteArray data = newSocket->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
            QJsonObject jsonObject = jsonDocument.object();
            int option = jsonObject.value("option").toInt();
            switch(option)
            {
                case 0://是登录请求
                    emit loginSignal(newSocket,jsonObject.value("account").toString(),jsonObject.value("password").toString());
                    break;
                case 1://是添加请求
                    emit addSignal(newSocket,jsonObject.value("name").toString(),jsonObject.value("gender").toString(),jsonObject.value("account").toString(),
                         jsonObject.value("password").toString(),jsonObject.value("job").toString(),jsonObject.value("salary").toString());
                    break;
                case 2://是删除请求
                    emit deleteSignal(newSocket, jsonObject.value("account").toString());
                    break;
                case 3://是修改请求
                    emit modifySignal(newSocket,jsonObject);
                    break;
                case 4://是查询请求
                    emit checkSignal(newSocket,jsonObject.value("account").toString());
                    break;
              }
        });
    });
}
Widget::~Widget()
{
    delete ui;
    Server->deleteLater();
    accountEdit->deleteLater();
    passwdEdit->deleteLater();
    RootloginBtn->deleteLater();
    CommonloginBtn->deleteLater();
    childWidget->deleteLater();
    childlayout->deleteLater();
    accountLabel->deleteLater();
    passwordLabel->deleteLater();
    jobEdit->deleteLater();
    salaryEdit->deleteLater();
    nameEdit->deleteLater();
    genderEdit->deleteLater();
}
//开启服务器
void Widget::on_startBtn_clicked()
{
    ui->startBtn->setEnabled(false);
    unsigned short port = ui->portLine->text().toUShort();
    Server->listen(QHostAddress::Any,port);
    if(Server->isListening())
    {
        qDebug()<<"开启成功";
    }else
    {
        qDebug()<<"开启失败";
    }
}
//添加root用户
void Widget::on_pushButton_clicked()
{
    childlayout->addWidget(RootloginBtn,6,1,1,2);
    childWidget->setLayout(childlayout);
    accountEdit->clear();
    passwdEdit->clear();
    jobEdit->clear();
    salaryEdit->clear();
    nameEdit->clear();
    genderEdit->clear();
    childWidget->show();
}
//添加普通用户
void Widget::on_pushButton_2_clicked()
{
    childlayout->addWidget(CommonloginBtn,6,1,1,2);
    childWidget->setLayout(childlayout);
    accountEdit->clear();
    passwdEdit->clear();
    jobEdit->clear();
    salaryEdit->clear();
    nameEdit->clear();
    genderEdit->clear();
    childWidget->show();
}
//查询root用户
void Widget::on_pushButton_3_clicked()
{
    if (!db->open())
    {
        qDebug()<<"数据库打开失败"<<db->lastError();
        return;
    }
    QSqlQuery query;
    if(!query.exec("SELECT * FROM loginmsg WHERE identity = 'root'"))
    {
        qDebug()<<"查询失败"<<db->lastError();
        return;
    }
    else
    {
        while (query.next())
        {
            qDebug() <<"name"<<query.value(0).toString()<<"gender"<<query.value(1).toString()<<  " account:" << query.value(2).toString() << " password:" << query.value(3).toString() << "job" <<query.value(4).toString() << "salary" << query.value(5).toString() <<" identity:" << query.value(6).toString();
        }
        QMessageBox::information(this,"提示","查询成功",QMessageBox::Ok);
    }
     db->close();
}
//查询普通用户
void Widget::on_pushButton_4_clicked()
{
    if (!db->open())
    {
        qDebug()<<"数据库打开失败"<<db->lastError();
        return;
    }
    QSqlQuery query;
    if(!query.exec("SELECT * FROM loginmsg WHERE identity = 'common'"))
    {
        qDebug()<<"查询失败"<<db->lastError();
        return;
    }
    else
    {
        while (query.next())
       {
            qDebug() <<"name"<<query.value(0).toString()<<"gender"<<query.value(1).toString()<<  " account:" << query.value(2).toString() << " password:" << query.value(3).toString() << "job" <<query.value(4).toString() << "salary" << query.value(5).toString() <<" identity:" << query.value(6).toString();
        }
       QMessageBox::information(this,"提示","查询成功",QMessageBox::Ok);
    }
    db->close();
}
//处理登录请求
void Widget::login(QTcpSocket* socket,QString account, QString password)
{
        if(!db->open())
        {
            qDebug()<<"数据库打开失败";
            return;
        }
       QSqlQuery query;
       query.prepare("select * from loginmsg where account = :account");
       query.bindValue(":account",account);
       if(!query.exec())
       {
            qDebug()<<"登录查询失败";
            return;
       }
       QJsonObject jsonMsg;
       jsonMsg.insert("option",0);
       QJsonDocument jsonDocument;
       if(query.next() && query.value("password") == password)
       {
            jsonMsg.insert("result","success");
            jsonMsg.insert("name",query.value("name").toString());
            jsonMsg.insert("gender",query.value("gender").toString());
            jsonMsg.insert("account",query.value("account").toString());
            jsonMsg.insert("password",query.value("password").toString());
            jsonMsg.insert("job",query.value("job").toString());
            jsonMsg.insert("salary",query.value("salary").toString());
            jsonMsg.insert("identity",query.value("identity").toString());
            jsonDocument = QJsonDocument(jsonMsg);
       }else
       {
            jsonMsg.insert("result","fail");
            jsonDocument = QJsonDocument(jsonMsg);
       }
       socket->write(jsonDocument.toJson());
       db->close();
}
//处理添加请求
void Widget::add(QTcpSocket *socket, QString name, QString gender, QString account, QString password, QString job, QString salary)
{
       if(!db->open())
       {
            qDebug()<<"数据库打开失败";
            return;
       }
       QSqlQuery query;
       query.prepare("insert into loginmsg (name, gender, account, password, job, salary, identity) values (:name, :gender, :account, :password, :job, :salary, :identity)");
       query.bindValue(":name",name);
       query.bindValue(":gender",gender);
       query.bindValue(":account",account);
       query.bindValue(":password",password);
       query.bindValue(":job",job);
       query.bindValue(":salary",salary);
       query.bindValue(":identity","common");
       QJsonObject jsonObject;
       jsonObject.insert("option",1);
       if(!query.exec())
       {
            qDebug()<<"插入数据失败:"<<query.lastError();
            jsonObject.insert("result","添加成功");
            return;
       }else
       {
            qDebug()<<"插入数据成功";
            jsonObject.insert("result","添加失败");
       }
       socket->write(QJsonDocument(jsonObject).toJson());
       db->close();
}
//处理删除请求
void Widget::Delete(QTcpSocket *socket, QString account)
{
       if(!db->open())
       {
            qDebug()<<"打开数据库失败"<<db->lastError();
            return;
       }
       QSqlQuery query;
       query.prepare("DELETE FROM loginmsg WHERE account = :account");
       query.bindValue(":account",account);
       QJsonObject jsonObject;
       jsonObject.insert("option",2);
       if(!query.exec())
       {
            qDebug()<<"删除用户"<<account<<"失败";
            jsonObject.insert("result",QJsonValue(true));
            return;
       }else
       {
            qDebug()<<"删除用户"<<account<<"成功";
            jsonObject.insert("result",QJsonValue(false));
       }
       socket->write(QJsonDocument(jsonObject).toJson());
       db->close();
}
//处理修改请求
void Widget::Modify(QTcpSocket *socket, QJsonObject jsonObject)
{
       QSqlQuery query;
       QJsonObject reply;
       qDebug()<<"begin="<<jsonObject.value("request").toString();
       reply.insert("option",3);
       if(!db->open())
       {
            qDebug()<<"数据库打开失败"<<db->lastError();
             reply.insert("result",QJsonValue(false));
            return;
       }
       if(jsonObject.value("identity").toString() == "root")
       {
            if(jsonObject.value("request").toString() == "message")
            {
                qDebug()<<"我是message";
                reply.insert("request","message");
                query.prepare("select * from loginmsg where account = :account");
                query.bindValue(":account",jsonObject.value("account"));
                if(!query.exec())
                {
                    qDebug()<<"执行message查询失败"<<query.lastError();
                }else
                {
                    if(query.next())
                    {
                        reply.insert("name",query.value("name").toString());
                        reply.insert("gender",query.value("gender").toString());
                        reply.insert("account",query.value("account").toString());
                        reply.insert("password",query.value("password").toString());
                        reply.insert("job",query.value("job").toString());
                        reply.insert("salary",query.value("salary").toString());
                        reply.insert("result",QJsonValue(true));
                    }else
                    {
                        qDebug()<<"get message失败";
                        reply.insert("result",QJsonValue(false));
                    }
                }

            }else if(jsonObject.value("request").toString() == "modify")
            {
                //账号和权限是不能修改的即使是root
                qDebug()<<"我是服务器modify";
                query.prepare("update loginmsg set name = :name, gender = :gender, password = :password, job = :job, salary = :salary  where account = :account");
                query.bindValue(":name",jsonObject.value("name"));
                query.bindValue(":gender",jsonObject.value("gender"));
                query.bindValue(":password",jsonObject.value("password"));
                query.bindValue(":job",jsonObject.value("job"));
                query.bindValue(":salary",jsonObject.value("salary"));
                query.bindValue(":account",jsonObject.value("account"));
                if(!query.exec())
                {
                    qDebug()<<"modify执行失败";
                }else
                {
                    qDebug()<<"modify执行成功 ";
                }
            }
       }else if(jsonObject.value("identity").toString() == "common")
       {
            qDebug()<<"我是common";
            qDebug()<<jsonObject.value("name")<<jsonObject.value("password")<<jsonObject.value("account");
            query.prepare("update loginmsg set name = :name, password= :password where account = :account");
            query.bindValue(":name",jsonObject.value("name"));
            query.bindValue(":password",jsonObject.value("password"));
            query.bindValue(":account",jsonObject.value("account"));
            if(!query.exec())
            {
                qDebug()<<"执行修改失败啊啊"<<query.lastError();
                reply.insert("result",QJsonValue(false));
            }else
            {
                qDebug()<<"修改成功";
                reply.insert("result",QJsonValue(true));
            }
       }
       socket->write(QJsonDocument(reply).toJson());
        db->close();
}
//处理查询请求
void Widget::Check(QTcpSocket *socket, QString account)
{
       if(!db->open())
       {
            qDebug()<<"数据库打开失败"<<db->lastError();
            return;
       }
       QSqlQuery query;
       query.prepare("select * from loginmsg where account = :account");
       query.bindValue(":account",account);
       QJsonObject jsonObject;
       jsonObject.insert("option",4);
       if(!query.exec())
       {
            qDebug()<<"服务器执行查询失败"<<query.lastError();
            return;
       }else
       {
            if(query.next())
            {//查到
                qDebug()<<"查询成功";
            qDebug()<<query.value("name").toString()<<query.value("gender").toString()<<query.value("account").toString()<<
                    query.value("password").toString()<<query.value("job").toString()<<query.value("salary").toString()<<query.value("identity").toString();
                jsonObject.insert("result",QJsonValue(true));
                jsonObject.insert("name",query.value("name").toString());
                jsonObject.insert("gender",query.value("gender").toString());
                jsonObject.insert("account",query.value("account").toString());
                jsonObject.insert("password",query.value("password").toString());
                jsonObject.insert("job",query.value("job").toString());
                jsonObject.insert("salary",query.value("salary").toString());
                jsonObject.insert("identity",query.value("identity").toString());
            }else
            {//没查到
                qDebug()<<"查询失败";
                jsonObject.insert("result",QJsonValue(false));
            }
       }
       socket->write(QJsonDocument(jsonObject).toJson());
       db->close();
}
