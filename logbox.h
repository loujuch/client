#ifndef LOGBOX_H
#define LOGBOX_H

#include <QMainWindow>

#include <QPushButton>
#include <QLineEdit>

#include "charbox.h"

class LogBox : public QMainWindow {
	Q_OBJECT

	enum Type {
		login=0, logup
	};

	QLineEdit* accunt;
	QLineEdit* passwd;
	QLineEdit* name;
	QPushButton* logupB;
	QPushButton* loginB;
	QPushButton* commit;

	CharBox charBox;

	Type type;
public:
	explicit LogBox(QWidget *parent = nullptr);
	~LogBox();

	void setLogUp();
	void setLogIn();
	void startCommit();
	void nextWindow(int id, const QString name);
signals:

};

#endif // LOGBOX_H
