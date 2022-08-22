#include "linkbox.h"
#include "globe.h"

LinkBox::LinkBox(QWidget *parent)
	: QMainWindow{parent}, ip(new QLineEdit(this)), port(new QLineEdit(this)), commit(new QPushButton("提交", this)) {
	this->setFixedSize(400, 300);
	this->setWindowTitle("连接");

	ip->setFixedSize(400, 100);
	port->setFixedSize(400, 100);
	commit->setFixedSize(400, 100);

	ip->move(0, 0);
	port->move(0, 100);
	commit->move(0, 200);

	connect(commit, &QPushButton::clicked, this, &LinkBox::nextWindow);
}

void LinkBox::nextWindow() {
	if(Globe::client->link(ip->text(), port->text().toInt())) {
		logBox.show();
		this->hide();
	} else {

	}
}

LinkBox::~LinkBox() {
	delete ip;
	delete port;
	delete commit;
}
