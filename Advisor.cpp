#include <QtWidgets>
#include <QFile>
#include "Advisor.h"

bool isEndSlash(QString fileName)
{
	QFile inFile(fileName);
	inFile.open(QIODevice::ReadOnly | QIODevice::Text);
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
	return button;
}

void Advisor::adviceClicked()
{
	bool endsWithSlash = isEndSlash("advice.dat");
	QStringList lineList;
	QFile inFile("advice.dat");
	int numLines = 0;
	if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
		display->insertPlainText("Not a valid advice.dat file!\n");
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
			display->insertPlainText("You can't end advice.dat with a backslash!\n");
		}
		else{
			int randNum = rand()%(numLines);
			display->insertPlainText("Advice: " + lineList[randNum] + "\n");
		}
}

void Advisor::weatherClicked()
{
	bool endsWithSlash = isEndSlash("weather.dat");
	QStringList lineList;
	QFile inFile("weather.dat");
	int numLines = 0;
	if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
		display->insertPlainText("Not a valid weather.dat file!\n");
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
			display->insertPlainText("You can't end weather.dat with a backslash!\n");
		}
		else{
			int randNum = rand()%(numLines);
			display->insertPlainText("Weather: " + lineList[randNum] + "\n");
		}
}

void Advisor::reminderClicked()
{
	display->insertPlainText("Reminder");
}

void Advisor::quitClicked()
{
	this->close();
}
