#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QHash>

class MainWindow : public QMainWindow
{
	Q_OBJECT

	int myId;
	QString myName;

	QHash<int, QString> table;

	QTextEdit* edit;
	QPushButton* button;

	Client* client;
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void send(QStringList s);
};
#endif // MAINWINDOW_H
