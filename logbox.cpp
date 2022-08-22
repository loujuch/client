#include "logbox.h"

#include "globe.h"

LogBox::LogBox(QWidget *parent)
	: QMainWindow{parent}, accunt(new QLineEdit(this)), passwd(new QLineEdit(this)), name(new QLineEdit(this)),
	logupB(new QPushButton("注册", this)), loginB(new QPushButton("登录", this)), commit(new QPushButton("提交", this)),
	type(logup) {
	this->setFixedSize(500, 500);
	this->setWindowTitle("注册");

	accunt->setFixedSize(500, 100);
	passwd->setFixedSize(500, 100);
	name->setFixedSize(500, 100);
	logupB->setFixedSize(250, 100);
	loginB->setFixedSize(250, 100);
	commit->setFixedSize(500, 100);

	logupB->move(0, 0);
	loginB->move(250, 0);
	accunt->move(0, 100);
	passwd->move(0, 200);
	name->move(0, 300);
	commit->move(0, 400);

	connect(logupB, &QPushButton::clicked, this, &LogBox::setLogUp);
	connect(loginB, &QPushButton::clicked, this, &LogBox::setLogIn);
	connect(commit, &QPushButton::clicked, this, &LogBox::startCommit);

	connect(Globe::client, &Client::LogSuccessSim, this, &LogBox::nextWindow);
}

void LogBox::setLogUp() {
	type=logup;
	this->setWindowTitle("注册");
	name->show();
}

void LogBox::setLogIn() {
	type=login;
	this->setWindowTitle("登录");
	name->hide();
}

void LogBox::startCommit() {
	if(type==logup) {
		Globe::client->logUp(accunt->text(), passwd->text(), name->text());
	} else {
		Globe::client->logIn(accunt->text(), passwd->text());
	}
}

void LogBox::nextWindow(int id, const QString name) {
	charBox.set(id, name);
	charBox.show();
	this->hide();
}

LogBox::~LogBox() {
	delete accunt;
	delete passwd;
	delete name;
	delete logupB;
	delete loginB;
	delete commit;
}
