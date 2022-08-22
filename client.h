#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

#include <QObject>

class Client: public QObject {
	Q_OBJECT

	enum MessageType {
		LogUp=0, LogIn, LogOut, LogSuccess, AloneText, GroupText, AddIdentity, SubIdentity, Error, Back
	};

	QTcpSocket* tcpClient;

	bool vaild;

	void readInt32(int& n);
	void writeInt32(int n);

	void readString(QString&s, int n);
	void writeString(const QString& s);

	void getMessage(QString& name, int& id, bool is);

	void recv();
public:
	Client();
	~Client();

	bool link(const QString& ip, int port);

	void logUp(const QString& accunt, const QString& passwd, const QString& name);
	void logIn(const QString& accunt, const QString& passwd);
	void alone(const QString& content, int n);
	void group(const QString& content);
	void logOut();

signals:
	void ErrorSim(const QString s);
	void LogSuccessSim(int id, const QString s);
	void AloneTextSim(int id, const QString s);
	void GroupTextSim(int id, const QString s);
	void AddIdentitySim(int id, const QString s);
	void SubIdentitySim(int id, const QString s);
	void BackTextSim(int id, const QString s);
};

#endif // CLIENT_H
