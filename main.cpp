#include "linkbox.h"
#include "globe.h""

#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	Globe::client=new Client;
	LinkBox w;
	w.show();
	return a.exec();
}
