#ifndef FERTIGUNGSAUFTRAGDIALOG_H
#define FERTIGUNGSAUFTRAGDIALOG_H

#include <QDialog>

namespace Ui {
class FertigungsauftragDialog;
}

class FertigungsauftragDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FertigungsauftragDialog(QWidget *parent = 0);
    ~FertigungsauftragDialog();
    QString getGravurtext();
    int getFormat();
    int getStandbild();
    void setAuftragsNr(unsigned int an);

private:
    Ui::FertigungsauftragDialog *ui;
};

#endif // FERTIGUNGSAUFTRAGDIALOG_H
