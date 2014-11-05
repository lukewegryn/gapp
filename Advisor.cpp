#include <QtWidgets>

#include "Advisor.h"

Advisor::Advisor(QWidget *parent)
	: QWidget(parent)
{
	//signalMapper = new QSignalMapper(this);
	display = new QTextEdit();
	display->setReadOnly(true);
	display->setAlignment(Qt::AlignLeft);
	//display->setMaxLength(20);

	QFont font = display->font();
	font.setPointSize(font.pointSize());
	display->setFont(font);
	QPushButton *adviceButton = createButton(tr("Advice"),SLOT(adviceClicked()));
	QPushButton *weatherButton = createButton(tr("Weather"), SLOT(weatherClicked()));
	QPushButton *reminderButton = createButton(tr("Reminder"), SLOT(reminderClicked()));
	QPushButton *quitButton = createButton(tr("Quit"), SLOT(quitClicked()));

	QGridLayout *mainLayout = new QGridLayout;
	//mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addWidget(display, 0,0,1,12);
	mainLayout->addWidget(adviceButton, 1,0,1,12);
	mainLayout->addWidget(weatherButton, 2, 0, 1, 12);
	mainLayout->addWidget(reminderButton, 3, 0, 1, 12);
	mainLayout->addWidget(quitButton, 4 ,0, 1, 12);

	//connect(signalMapper, SIGNAL(mapped(QString)), this, SIGNAL(clicked(QString)));
	setLayout(mainLayout);

	setWindowTitle(tr("Advisor"));
}

QPushButton *Advisor::createButton(const QString &text, const char *member)
{
	QPushButton *button = new QPushButton(text);
	connect(button, SIGNAL(clicked()), this, member);
	//signalMapper->setMapping(button, text);
	return button;
}

void Advisor::adviceClicked()
{
	//QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
	//clickedButton->insertPlainText(QString("Hello"));
	display->insertPlainText("Hello");
}

void Advisor::weatherClicked()
{
	//QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
}

void Advisor::reminderClicked()
{
	//QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
}

void Advisor::quitClicked()
{
	this->close();
}