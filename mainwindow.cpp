#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), edit(new QTextEdit(this)), button(new QPushButton("commit", this)) {
	this->setFixedSize(320, 225);
	this->setWindowTitle("Wait Log");
	edit->setFixedSize(300, 150);
	edit->move(10, 10);
	button->setFixedSize(300, 50);
	button->move(10, 165);

//	client=new Client("127.0.0.1", 8080);

//	Client::link();

	bool flag;
	do {
//		flag=Client::link();
		if(flag)qDebug()<<"success!\n";
		else qDebug()<<"fail!\n";
	}while(!flag);

	connect(button, &QPushButton::clicked, this, [&](){
		send(edit->toPlainText().split('\n'));
		edit->setText("");
	});

	connect(client, &Client::ErrorSim, this, [&](const QString s){
		qDebug()<<"Error: "<<s<<"\n";
	});

	connect(client, &Client::LogSuccessSim, this, [&](int id, const QString s){
		myId=id;
		myName=s;
		qDebug()<<"myId: "<<myId<<" myName: "<<myName<<"\n";
	});

	connect(client, &Client::AddIdentitySim, this, [&](int id, const QString s){
		qDebug()<<"Add id:"<<id<<" name: "<<s<<"\n";
		table.insert(id, s);
	});

	connect(client, &Client::SubIdentitySim, this, [&](int id, const QString s){
		qDebug()<<"Sub id:"<<id<<" name: "<<s<<"\n";
		table.remove(id);
	});

	connect(client, &Client::AloneTextSim, this, [&](int id, const QString s){
		qDebug()<<"Message Alone From:"<<table[id]<<" content: "<<s<<"\n";
	});

	connect(client, &Client::GroupTextSim, this, [&](int id, const QString s){
		qDebug()<<"Message Group From:"<<table[id]<<" content: "<<s<<"\n";
	});
}

void MainWindow::send(QStringList a){
	qDebug()<<"send: "<<a.join(' ')<<'\n';
	if(a[0]=="logout") {
		client->logOut();
	}
	if(a[0]=="login") {
		client->logIn(a[1], a[2]);
	}
	if(a[0]=="logup") {
		client->logUp(a[1], a[2], a[3]);
	}
	if(a[0]=="alone") {
		client->alone(a[2], a[1].toInt());
	}
	if(a[0]=="group") {
		client->group(a[1]);
	}
	if(a[0]=="quit") {
		client->logOut();
	}
}

MainWindow::~MainWindow() {
	delete edit;
	delete button;
}

