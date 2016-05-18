#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QFileDialog>

namespace Ui {
class settingDialog;
}

class settingDialog : public QDialog
{
    Q_OBJECT

signals:
    void info(const qreal &x, const qreal &y, const qreal &width, const qreal &height);
    void file(const QString &fileString);
    void shutMe(settingDialog *);

public:
    explicit settingDialog(QWidget *parent = 0);
    ~settingDialog();
    void setInfo(const qreal &x, const qreal &y, const qreal &width, const qreal &height);
    void setFile(const QString &fileString);
    void setID(const int &ID);

private slots:
    void confirmThing(QAbstractButton*);

    void on_pushButton_clicked();

private:
    Ui::settingDialog *ui;
};

#endif // SETTINGDIALOG_H
