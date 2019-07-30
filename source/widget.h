#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();

private:
	Ui::Widget *ui;

	void timerEvent(QTimerEvent* e);
	int m_timerId;

private slots:
	void on_startButton_clicked();

	void on_stopButton_clicked();

	void on_saveButton_clicked();

	void on_spinBox_word_valueChanged(int arg1);
};

#endif // WIDGET_H
