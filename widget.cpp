#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this);
	if (fileName.isEmpty())
	{
		// error
		QMessageBox::warning(this, tr("Briefing Creator"),
				tr("Cannot write file %1")
				.arg(fileName));
		return;
	}

	// create briefing.sqf file
	QFile sqf(fileName);
	sqf.open(QIODevice::WriteOnly | QIODevice::Text);

	QString buffer;
	QTextStream sqfstream(&sqf);

	// fill in our buffer with the actual briefing data

	// initial stuff, switch...
	buffer.append("waitUntil {!(isNull player)};\nwaitUntil {player == player};\n\nswitch (side player) do\n");

	// case west
	buffer.append("{\n\tcase WEST:\n\t{\n\n");

	buffer.append("// 6\n\t\tplayer createDiaryRecord\n\t\t[\n\t\t\t\"Diary\",\n\t\t\t[\n\t\t\t\t\"DIARY\",\n\t\t\t\t\"" + ui->diary->text() + "\"\n\t\t\t]\n\t\t];\n\n");
	buffer.append("// 5\n\t\tplayer createDiaryRecord\n\t\t[\n\t\t\t\"Diary\",\n\t\t\t[\n\t\t\t\t\"SUPPORT\",\n\t\t\t\t\"" + ui->support->text() + "\"\n\t\t\t]\n\t\t];\n\n");
	buffer.append("// 4\n\t\tplayer createDiaryRecord\n\t\t[\n\t\t\t\"Diary\",\n\t\t\t[\n\t\t\t\t\"ORDERS\",\n\t\t\t\t\"" + ui->orders->text() + "\"\n\t\t\t]\n\t\t];\n\n");
	buffer.append("// 3\n\t\tplayer createDiaryRecord\n\t\t[\n\t\t\t\"Diary\",\n\t\t\t[\n\t\t\t\t\"TACTICAL\",\n\t\t\t\t\"" + ui->tactical->text() + "\"\n\t\t\t]\n\t\t];\n\n");
	buffer.append("// 2\n\t\tplayer createDiaryRecord\n\t\t[\n\t\t\t\"Diary\",\n\t\t\t[\n\t\t\t\t\"INTEL\",\n\t\t\t\t\"" + ui->intel->text() + "\"\n\t\t\t]\n\t\t];\n\n");
	buffer.append("// 1\n\t\tplayer createDiaryRecord\n\t\t[\n\t\t\t\"Diary\",\n\t\t\t[\n\t\t\t\t\"GEN SITREP\",\n\t\t\t\t\"" + ui->gensitrep->text() + "\"\n\t\t\t]\n\t\t];\n\n");

	buffer.append("\t};\n\n");

	// case east
	buffer.append("\tcase EAST:\n\t{\n\n");
	buffer.append("\t};\n\n");

	// case resistance
	buffer.append("\tcase RESISTANCE:\n\t{\n\n");
	buffer.append("\t};\n\n");

	// case CIVILIAN
	buffer.append("\tcase CIVILIAN:\n\t{\n\n");
	buffer.append("\t};\n\n");

	// close the switch brace
	buffer.append("};\n");

	sqfstream << buffer;

	sqf.close();
}
