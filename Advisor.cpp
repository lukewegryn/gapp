#include <QtWidgets>
#include <QFile>
#include <QDialog>
#include "Advisor.h"
#include <QCheckBox>

bool Advisor::isEndSlash(QString fileName)
{
	QFile inFile(fileName);
	if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		display->insertPlainText("Not a valid file!");
		return true;
	}
	else
	{
		QTextStream stream(&inFile);
		QString fileString = stream.readAll();
		if(fileString.endsWith("\\"))
		{
			inFile.close();
			return true;
		}
		else{
			inFile.close();
			return false;
		}
	}
}

QString Advisor::getText(QString fileName)
{
	bool endsWithSlash = isEndSlash(fileName);
	QStringList lineList;
	QFile inFile(fileName);
	int numLines = 0;
	if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
		display->insertPlainText("Not a valid file!\n");
	else{
		QTextStream stream(&inFile);
		while(!stream.atEnd()){
			QString line = stream.readLine();
			if(line.endsWith("\\")){
				do{
					line = line.remove(QChar('\\'), Qt::CaseInsensitive) + " " + stream.readLine();
				} while(line.endsWith("\\"));
			}
			lineList.append(line);
			numLines++;
		}
		inFile.close();
	}
		if(endsWithSlash)
		{
			display->insertPlainText("You can't end a file with a backslash!\n");
			return NULL;
		}
		else{
			int randNum = rand()%(numLines);
			if(numLines > 0)
				return lineList[randNum];
			else
				return NULL;
		}
}

Advisor::Advisor(QWidget *parent)
	: QWidget(parent)
{
	showAgain = true;
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
	return button;
}

void Advisor::adviceClicked()
{
	QString advice;
	if((advice = getText("advice.dat")) != NULL)
	{
		display->insertPlainText("Advice: " + advice + "\n");
	}
}

void Advisor::weatherClicked()
{
	QString weather;
	if((weather = getText("weather.dat")) != NULL)
	{
		display->insertPlainText("Weather: " + weather + "\n");
	}
}

void Advisor::reminderClicked()
{
	if(showAgain == true)
	{
		QCheckBox *checkbox = new QCheckBox("Show this message again.", this);
		checkbox->setCheckState(Qt::Checked);
		QMessageBox msgBox;
		QString reminder;
		if((reminder = getText("reminder.dat")) != NULL)
		{
			QString day = QString::number(rand()%(30-1)+1);
			QString month = QString::number(rand()%(12-1)+1);
			QString year = QString::number(rand()%(2017-2014)+2014);
			int hour = rand()%(24-1)+1;
			int minute = rand()%(60-1)+1;
			QTime theTime(hour, minute);
			msgBox.setText(reminder + "at " + theTime.toString("h:mm ap") + " on " + month + "/" + day + "/" + year + ".");
			msgBox.setCheckBox(checkbox);
			connect(checkbox, SIGNAL(stateChanged(int)), this, SLOT(reminderCheck()));
			msgBox.exec();
		}
		else
		{
			display->insertPlainText("You don't seem to have any reminders.\n");
		}
	}
	else
	{
		display->insertPlainText("You disabled reminders!\n");
	}
}

void Advisor::reminderCheck()
{
	showAgain = !showAgain;
}

void Advisor::quitClicked()
{
	QMessageBox msgBox;
	msgBox.setText("Are you sure you want to quit?");
	msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes );
	msgBox.setDefaultButton(QMessageBox::Cancel);
	int ret = msgBox.exec();
	switch (ret) {
		case QMessageBox::Yes:
			Advisor::quitProgram();
		break;
		default:
			break;
	}
}

void Advisor::quitProgram()
{
	this->close();
}
