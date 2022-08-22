#ifndef LINKBOX_H
#define LINKBOX_H

#include <QMainWindow>

#include <QPushButton>
#include <QLineEdit>

#include "logbox.h"

class LinkBox : public QMainWindow {
	Q_OBJECT

	QLineEdit* ip;
	QLineEdit* port;
	QPushButton* commit;

	LogBox logBox;
public:
	explicit LinkBox(QWidget *parent = nullptr);
	~LinkBox();

	void nextWindow();
signals:

};

#endif // LINKBOX_H
