#include <QtWidgets>

#include "button.h"
#include "Advisor.h"

Advisor::Advisor(QWidget *parent)
	: QWidget(parent)
{
	Button *adviceButton = createButton(tr("Advice"),SLOT(adviceClicked()));
	Button *weatherButton = createButton(tr("Weather"), SLOT(weatherClicked()));
	Button *reminderButton = createButton(tr("Reminder"), SLOT(reminderClicked()));
	Button *quitButton = createButton(tr("Quit"), SLOT(quitClicked()));

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addWidget(adviceButton, 0,0,1,6);
	mainLayout->addWidget(weatherButton, 1, 0, 1, 6);
	mainLayout->addWidget(reminderButton, 2, 0, 1, 6);
	mainLayout->addWidget(quitButton, 3 ,0, 1, 6);
	setLayout(mainLayout);

	setWindowTitle(tr("Advisor"));
}

Button *Advisor::createButton(const QString &text, const char *member)
{
	Button *button = new Button(text);
	connect(button, SIGNAL(clicked()), this, member);
	return button;
}

void Advisor::adviceClicked()
{
	Button *clickedButton = qobject_cast<Button *>(sender());
}

void Advisor::weatherClicked()
{
	Button *clickedButton = qobject_cast<Button *>(sender());
}

void Advisor::reminderClicked()
{
	Button *clickedButton = qobject_cast<Button *>(sender());
}

void Advisor::quitClicked()
{
	Button *clickedButton = qobject_cast<Button *>(sender());
}