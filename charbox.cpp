#include "charbox.h"

#include "globe.h"

const int CharBox::group=INT_MIN;

CharBox::CharBox(QWidget *parent)
	: QMainWindow{parent}, select(group), content(new QListWidget(this)), user(new QListWidget(this)),
	edit(new QTextEdit(this)), button(new QPushButton("发送", this)) {
	ids.push_back(group);
	names.push_back("群聊");
	id_message.insert(group, QVector<QString>());
	user->addItem("群聊");
	this->setFixedSize(800, 600);
	this->setWindowTitle("群聊");

	content->setSelectionMode(QAbstractItemView::NoSelection);
	user->setSelectionMode(QAbstractItemView::SingleSelection);
	user->setCurrentRow(0);

	content->setFixedSize(500, 400);
	user->setFixedSize(300, 600);
	edit->setFixedSize(500, 125);
	button->setFixedSize(150, 75);

	content->move(0, 0);
	user->move(500, 0);
	edit->move(0, 400);
	button->move(300, 525);

	connect(button, &QPushButton::clicked, this, &CharBox::sendText);
	connect(Globe::client, &Client::GroupTextSim, this, &CharBox::groupText);
	connect(Globe::client, &Client::AloneTextSim, this, &CharBox::recvText);
	connect(Globe::client, &Client::BackTextSim, this, &CharBox::backText);

	connect(Globe::client, &Client::AddIdentitySim, this, &CharBox::addUser);
	connect(Globe::client, &Client::SubIdentitySim, this, &CharBox::subUser);

	connect(user, &QListWidget::currentItemChanged, this, &CharBox::selectUser);
}

CharBox::~CharBox() {
	delete content;
	delete user;
	delete edit;
	delete button;
}

void CharBox::addUser(int id, const QString name) {
	ids.push_back(id);
	names.push_back(name);
	id_message.insert(id, QVector<QString>());
	user->addItem(name);
}

int CharBox::find(const QString& name) {
	for(int i=0;i<names.size();++i) {
		if(names[i]==name)return i;
	}
	return -1;
}

int CharBox::find(int j) {
	for(int i=0;i<ids.size();++i) {
		if(ids[i]==j)return i;
	}
	return -1;
}

void CharBox::subUser(int id, const QString name) {
	int i=find(name);
	if(i<0)return;
	user->takeItem(i);
	ids.erase(ids.begin()+i);
	names.erase(names.begin()+i);
}

void CharBox::selectUser(QListWidgetItem *current, QListWidgetItem *previous) {
	content->clear();
	int f=find(current->text());
	if(f<0)return;
	select=ids[f];
	for(auto&i:id_message[select]) {
		content->addItem(i);
	}
	edit->clear();
}

void CharBox::backText(int to, const QString s) {
	QString o=name+":\n"+s+"\n\n";
	id_message[to].append(o);
	if(select==to)content->addItem(o);
}

void CharBox::recvText(int from, const QString s) {
	int i=find(from);
	if(i<0)return;
	QString o=names[i]+":\n"+s+"\n\n";
	id_message[from].append(o);
	if(select==from)content->addItem(o);
}

void CharBox::groupText(int from, const QString s) {
	int i=find(from);
	if(i<0)return;
	QString o=names[i]+":\n"+s+"\n\n";
	id_message[group].append(o);
	if(select==group)content->addItem(o);
}

void CharBox::sendText() {
	if(select==group) {
		Globe::client->group(edit->toPlainText());
	} else {
		Globe::client->alone(edit->toPlainText(), select);
	}
	edit->clear();
}

void CharBox::set(int id, const QString& s) {
	this->id=id;
	this->name=s;
	this->setWindowTitle(s);
}
