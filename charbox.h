#ifndef CHARBOX_H
#define CHARBOX_H

#include <QMainWindow>
#include <QListWidget>

#include <QHash>
#include <QVector>

#include <QTextEdit>
#include <QPushButton>

class CharBox : public QMainWindow
{
	Q_OBJECT

	static const int group;

	int id;
	QString name;
	int select;

	QListWidget* content;
	QListWidget* user;

	QVector<int>ids;
	QVector<QString>names;
	QHash<int, QVector<QString>>id_message;
	QHash<QString, int>str_id;

	QTextEdit* edit;
	QPushButton* button;
public:
	explicit CharBox(QWidget *parent = nullptr);
	~CharBox();
	void set(int id, const QString& name);

	void addUser(int id, const QString name);
	void subUser(int id, const QString name);

	void selectUser(QListWidgetItem *current, QListWidgetItem *previous) ;

	void recvText(int from, const QString s);
	void groupText(int from, const QString s);
	void backText(int to, const QString s);

	void sendText();

	int find(const QString& s);
	int find(int i);
signals:

};

#endif // CHARBOX_H
