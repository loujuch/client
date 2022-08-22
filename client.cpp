#include "client.h"

#include <QtEndian>
#include <QDebug>

Client::Client():QObject(nullptr), tcpClient(new QTcpSocket), vaild(false) {
	connect(tcpClient, &QTcpSocket::readyRead, this, &Client::recv);
}

Client::~Client() {
	delete tcpClient;
}

bool Client::link(const QString& ip, int port) {
	if(vaild)return true;
	tcpClient->connectToHost(ip, port);
	if(tcpClient->waitForConnected(500)) {
		vaild=true;
		return true;
	} else {
		return false;
	}
}

void Client::recv() {
	if(!vaild)return;
	int type, id;
	QString s;
	readInt32(type);
	getMessage(s, id, type!=Error);
	qDebug()<<"type: "<<type<<", id: "<<id<<", s:"<<s<<'\n';
	switch(type) {
	case Error:
		emit ErrorSim(s);
		break;
	case LogSuccess:
		emit LogSuccessSim(id, s);
		break;
	case AloneText:
		emit AloneTextSim(id, s);
		break;
	case GroupText:
		emit GroupTextSim(id, s);
		break;
	case AddIdentity:
		emit AddIdentitySim(id, s);
		break;
	case SubIdentity:
		emit SubIdentitySim(id, s);
		break;
	case Back:
		emit BackTextSim(id, s);
		break;
	default:
		break;
	}
}

void Client::logUp(const QString& accunt, const QString& passwd, const QString& name) {
	if(!vaild)return;
	writeInt32(LogUp);
	writeString(accunt);
	writeString(passwd);
	writeString(name);
}

void Client::logIn(const QString& accunt, const QString& passwd) {
	if(!vaild)return;
	writeInt32(LogIn);
	writeString(accunt);
	writeString(passwd);
}

void Client::alone(const QString& content, int to) {
	if(!vaild)return;
	writeInt32(AloneText);
	writeInt32(to);
	writeString(content);
}

void Client::group(const QString& content) {
	if(!vaild)return;
	writeInt32(GroupText);
	writeString(content);
}

void Client::logOut() {
	if(!vaild)return;
	writeInt32(LogOut);
	vaild=false;
}

void Client::getMessage(QString& name, int& id, bool is) {
	if(!vaild)return;
	int len;
	if(is)readInt32(id);
	readInt32(len);
	readString(name, len);
}

void Client::readInt32(int& n) {
	if(!vaild)return;
	tcpClient->read((char*)&n, sizeof(int));
	n=qFromBigEndian(n);
}

void Client::writeInt32(int n) {
	if(!vaild)return;
	n=qToBigEndian(n);
	tcpClient->write((char*)&n, sizeof(int));
}

void Client::readString(QString&s, int n) {
	if(!vaild)return;
	s="";
	static char buffer[1024];
	int tmp=n, len;
	while(tmp>0) {
		tmp=std::min(1024, n);
		len=tcpClient->read(buffer, tmp);
		if(len<0)continue;
		tmp-=len;
		s.append(QByteArray(buffer, len));
	}
}

void Client::writeString(const QString& s) {
	if(!vaild)return;
	auto i=QByteArray(s.toUtf8());
	writeInt32(i.size());
	tcpClient->write(QByteArray(i.data(), i.size()));
}
