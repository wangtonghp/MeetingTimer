#include "widget.h"
#include "ui_widget.h"
#include <QFont>
#include <QFileDialog>
#include <QTextStream>

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);
	// 時間・金額表示部分を編集不可に変更
	ui->lineEdit_time->setEnabled(false);
	ui->lineEdit_money->setEnabled(false);
	// 画面前面に必ず表示するように変更
	this->setWindowFlags(Qt::WindowStaysOnTopHint);

}

Widget::~Widget()
{
	delete ui;
}


void Widget::on_startButton_clicked()
{
	m_timerId = startTimer(1000); //1[s]
}

void Widget::on_stopButton_clicked()
{
	killTimer(m_timerId);
}


void Widget::on_spinBox_word_valueChanged(int arg1)
{
	//文字の大きさを変更
	ui->plainTextEdit->setFont(QFont("MS UI Gothic", arg1));
}


void Widget::on_saveButton_clicked()
{
	//データをcsvに保存
	//ファイルオープン処理
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
		tr("Text Files (*.txt)"));

	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (!file.open(QIODevice::WriteOnly)) {
			// error message
		} else {
			QTextStream stream(&file);
			stream.setCodec("UTF-8");
			stream << "unit_price;person;limit_time;time;cost" << "\n";
			stream << ui->spinBox_unit->text() << ";" << ui->spinBox_person->text() << ";" << ui->spinBox_time->text() << ";" << ui->lineEdit_time->text() << ";" << ui->lineEdit_money->text() << "\n";
			stream << ui->plainTextEdit->toPlainText();
			stream.flush();
			file.close();
		}
	}
}

void Widget::timerEvent(QTimerEvent* e)
{
	static qint32 time = 0;
	// 設定数値を数値に変換
	qint32 humanNum = ui->spinBox_person->text().toInt();
	qint32 unit = ui->spinBox_unit->text().toInt();
	qint32 timeLimit = ui->spinBox_time->text().toInt();

	if(e->timerId() == m_timerId)
	{
		time++;
		qint32 money = unit * humanNum * time / 3600; //時給を秒給に変更

		//時計表示に変更
		qint32 sec = time%60;
		qint32 temp = time/60;
		qint32 hour = temp/60;
		qint32 min = temp%60;

		//会議時間をオーバーしていたら音を鳴らし，文字を赤くする
		if(time == (timeLimit*60))
		{
			//音を鳴らす
			QApplication::beep();
			//文字を赤くする
			ui->lineEdit_time->setStyleSheet("color: red;");
			ui->lineEdit_money->setStyleSheet("color: red;");
		}

		//時間と金額を更新
		ui->lineEdit_money->setText(QString::number(money));
		ui->lineEdit_time->setText(QString::number(hour).rightJustified(2,'0') + ":" + QString::number(min).rightJustified(2,'0') + ":" + QString::number(sec).rightJustified(2,'0'));
	}

}

