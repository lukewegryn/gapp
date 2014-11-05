#ifndef ADVISOR_H
#define ADVISOR_H
#include <QWidget>

class Button;
class QLineEdit;

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
		Button *createButton(const QString &text, const char *member);
		void abortOperatiion();
		QLineEdit *display;
};

#endif