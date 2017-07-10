#include "fertigungsauftragdialog.h"
#include "ui_fertigungsauftragdialog.h"
#include "produktbeschreibung.h"

FertigungsauftragDialog::FertigungsauftragDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FertigungsauftragDialog)
{
    ui->setupUi(this);
    ui->formatComboBox->addItem(QString::fromStdString(Produktbeschreibung::FORMAT[0]));
    ui->formatComboBox->addItem(QString::fromStdString(Produktbeschreibung::FORMAT[1]));
    ui->standbildComboBox->addItem(QString::fromStdString(Produktbeschreibung::STANDBILD[0]));
    ui->standbildComboBox->addItem(QString::fromStdString(Produktbeschreibung::STANDBILD[1]));
}

FertigungsauftragDialog::~FertigungsauftragDialog()
{
    delete ui;
}

QString FertigungsauftragDialog::getGravurtext()
{
    return ui->gravurTextEdit_3->text();
}

int FertigungsauftragDialog::getFormat()
{
    return ui->formatComboBox->currentIndex();
}

int FertigungsauftragDialog::getStandbild()
{
    return ui->standbildComboBox->currentIndex();
}
void FertigungsauftragDialog::setAuftragsNr(unsigned int an)
{
    ui->auftragsNrEdit->setText(QString::number(an));
}
