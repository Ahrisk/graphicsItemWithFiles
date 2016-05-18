#include "settingdialog.h"
#include "ui_settingdialog.h"

settingDialog::settingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(confirmThing(QAbstractButton*)));
    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());
    this->setWindowTitle("Settings");
    this->ui->lineEdit->setEnabled(false);
}

settingDialog::~settingDialog()
{
    delete ui;
}

void settingDialog::setInfo(const qreal &x, const qreal &y, const qreal &width, const qreal &height)
{
    ui->spinBox_x->setValue(qRound(x));
    ui->spinBox_y->setValue(qRound(y));
    ui->spinBox_width->setValue(qRound(width));
    ui->spinBox_height->setValue(qRound(height));
}

void settingDialog::setFile(const QString &fileString)
{
    ui->lineEdit->setText(fileString);
}

void settingDialog::setID(const int &ID)
{
    QString st = "ID: " + QString::number(ID, 10);
    ui->label_top->setText(st);
}

void settingDialog::confirmThing(QAbstractButton *tButton)
{
    if (ui->buttonBox->button(QDialogButtonBox::Ok) == tButton)
    {
        emit info(ui->spinBox_x->value(), ui->spinBox_y->value(),
                  ui->spinBox_width->value(), ui->spinBox_height->value());
        emit file(ui->lineEdit->text());
        emit shutMe(this);
    }
    else if (ui->buttonBox->button(QDialogButtonBox::Cancel) == tButton)
    {
        emit shutMe(this);
    }
}

void settingDialog::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Settings", "/", "all(*.*)");
    ui->lineEdit->setText(path);
}
