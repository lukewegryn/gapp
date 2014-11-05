#ifndef ADVISOR_H
#define ADVISOR_H
#include <QWidget>
#include <QSignalMapper>

class QPushButton;
class QTextEdit;

class Advisor:public QWidget
{
	Q_OBJECT

	public:
		Advisor(QWidget *parent = 0);

	private slots:
		void adviceClicked();
		void weatherClicked();
		void reminderClicked();
		void quitClicked();
		
	private:
		QPushButton *createButton(const QString &text, const char *member);
		void abortOperatiion();
		QTextEdit *display;
		QSignalMapper *signalMapper;
};

#endif