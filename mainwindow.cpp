#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fertigungsauftragdialog.h>
#include <QObject>
#include <QMessageBox>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent, Auftragsverwaltung* av) :
    QMainWindow(parent),auftraege(av),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setHorizontalHeaderLabels(QString("AuftragNr;Format;Gravurtext;Standbild;ba;fr;bo;vs;RFID-Nr").split(";"));
    ui->tableWidget->setColumnWidth(0,120);
    ui->tableWidget->setColumnWidth(1,80);
    ui->tableWidget->setColumnWidth(2,340);
    ui->tableWidget->setColumnWidth(3,80);
    ui->tableWidget->setColumnWidth(4,30);
    ui->tableWidget->setColumnWidth(5,30);
    ui->tableWidget->setColumnWidth(6,30);
    ui->tableWidget->setColumnWidth(7,30);
    ui->tableWidget->setColumnWidth(8,120);

    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color:lightgray }");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section { background-color:lightgray }");
//    ui->tableWidget->setStyleSheet("background-color:lightblue");
//    ui->beauftragenButton->setStyleSheet( "background-color:lightblue");

    statusIcon[Bearbeitungsstatus::offen]=QIcon(":/new/statusIcons/offen.png");
    statusIcon[Bearbeitungsstatus::erledigt]=QIcon(":/new/statusIcons/erledigt.png");
    statusIcon[Bearbeitungsstatus::na]=QIcon(":/new/statusIcons/na.png");


    if(!auftraege)
    {
        auftraege = new Auftragsverwaltung();
    }
    auftraege->lade();
    for(int i=0;i<auftraege->getAnzahlAuftraege();i++)
    {
        addRow(auftraege->getAuftrag(i));
     //   cout << auftraege->getAuftrag(i) << endl;
    }
    connect(auftraege,SIGNAL(auftragChanged(int)),this,SLOT(updateRow(int)));
//    connect(auftraege,SIGNAL(beauftragt(int)),this,SLOT(stopTimer(int r)));
//    connect(&timer,SIGNAL(timeout()),this,SLOT(resetBeauftragung()));
    connect(auftraege,SIGNAL(fehlerZustand(QString)),this, SLOT(anzeigenFehlerZustand(QString)));
}

MainWindow::~MainWindow()
{
//    Fertigungsauftrag fa = auftraege->getAuftrag(4);
//    fa.setRFIDNr(1234);
//    auftraege->setAuftrag(4,fa);
    auftraege->speichere();
    delete ui;
}

//void MainWindow::setAuftragsverwaltung(Auftragsverwaltung* av)
//{
//    auftraege = av;
//}

void MainWindow::updateRow(int row)
{
    QTableWidgetItem* item;
    QColor cpb(240,240,240);
    Fertigungsauftrag fa=auftraege->getAuftrag(row);

    /** Fülle die Tabellenzeile mit den Daten des Fertigungsauftrags von fa **/
    item=ui->tableWidget->item(row,0);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::number(fa.getAuftragsnummer()));
//    ui->tableWidget->setItem(row,0,item);

    item=ui->tableWidget->item(row,1);
    item->setBackgroundColor(cpb);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(fa.getProduktbeschreibung().formatToString()));
//    ui->tableWidget->setItem(row,1,item);

    item=ui->tableWidget->item(row,2);
    item->setBackgroundColor(cpb);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(fa.getProduktbeschreibung().getGravurtext()));
//    ui->tableWidget->setItem(row,2,item);

    item=ui->tableWidget->item(row,3);
    item->setBackgroundColor(cpb);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(fa.getProduktbeschreibung().standbildToString()));
//    ui->tableWidget->setItem(row,3,item);

    item=ui->tableWidget->item(row,4);
    item->setIcon(statusIcon[fa.getBearbeitungsstatus().getBeauftragt()]);
//    ui->tableWidget->setItem(row,4,item);

    item=ui->tableWidget->item(row,5);
    item->setIcon(statusIcon[fa.getBearbeitungsstatus().getGefraest()]);
//    ui->tableWidget->setItem(row,5,item);

    item=ui->tableWidget->item(row,6);
    item->setIcon(statusIcon[fa.getBearbeitungsstatus().getGebohrt()]);
//    ui->tableWidget->setItem(row,6,item);

    item=ui->tableWidget->item(row,7);
    item->setIcon(statusIcon[fa.getBearbeitungsstatus().getVersendet()]);
//    ui->tableWidget->setItem(row,7,item);

    item=ui->tableWidget->item(row,8);
    item->setTextAlignment(Qt::AlignCenter);
    QString qs=QString("%1").arg(fa.getRFIDNr(),0,16);
    item->setText(qs);
//    ui->tableWidget->setItem(row,8,item);

}

void MainWindow::addRow(Fertigungsauftrag fa)
{
    QTableWidgetItem* item;
    QColor cpb(240,240,240);
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    /** Fülle die Tabellenzeile mit den Daten des Fertigungsauftrags von fa **/
    item=new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::number(fa.getAuftragsnummer()));
    ui->tableWidget->setItem(row,0,item);

    item=new QTableWidgetItem();
    item->setBackgroundColor(cpb);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(fa.getProduktbeschreibung().formatToString()));
    ui->tableWidget->setItem(row,1,item);

    item=new QTableWidgetItem();
    item->setBackgroundColor(cpb);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(fa.getProduktbeschreibung().getGravurtext()));
    ui->tableWidget->setItem(row,2,item);

    item=new QTableWidgetItem();
    item->setBackgroundColor(cpb);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(QString::fromStdString(fa.getProduktbeschreibung().standbildToString()));
    ui->tableWidget->setItem(row,3,item);

    item=new QTableWidgetItem();
    item->setIcon(statusIcon[fa.getBearbeitungsstatus().getBeauftragt()]);
    ui->tableWidget->setItem(row,4,item);

    item=new QTableWidgetItem();
    item->setIcon(statusIcon[fa.getBearbeitungsstatus().getGefraest()]);
    ui->tableWidget->setItem(row,5,item);

    item=new QTableWidgetItem();
    item->setIcon(statusIcon[fa.getBearbeitungsstatus().getGebohrt()]);
    ui->tableWidget->setItem(row,6,item);

    item=new QTableWidgetItem();
    item->setIcon(statusIcon[fa.getBearbeitungsstatus().getVersendet()]);
    ui->tableWidget->setItem(row,7,item);

    item=new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    QString qs=QString("%1").arg(fa.getRFIDNr(),0,16);
    item->setText(qs);
    ui->tableWidget->setItem(row,8,item);
    //    Qt::ItemFlags flags;
    //    flags = item->flags();
    //    flags |= Qt::ItemIsSelectable;
    //    flags &= ~Qt::ItemIsEditable; // reset/clear the flag
    //    item->setFlags(flags);
    ui->tableWidget->scrollToBottom();

}

void MainWindow::on_hinzufuegenButton_clicked()
{
    FertigungsauftragDialog dialog;
    Fertigungsauftrag fa;
    dialog.setFixedHeight(240);
    dialog.setFixedWidth(420);
    unsigned int maxNr = auftraege->getNextAuftragsNr();
    dialog.setAuftragsNr(maxNr);
    if(dialog.exec())
    {
        cout << "Auftragsdaten übertragen\n";
        fa.setAuftragsNr(maxNr);
        Produktbeschreibung p = fa.getProduktbeschreibung();
        p.setHochFormat((bool)dialog.getFormat());
        p.setStandbild((bool)dialog.getStandbild());
        p.setGravurtext(dialog.getGravurtext().toStdString());
        fa.setProduktbeschreibung(p);
        Bearbeitungsstatus b = fa.getBearbeitungsstatus();
        b.setGefraest(Bearbeitungsstatus::offen);
        if(!dialog.getStandbild())
            b.setGebohrt(Bearbeitungsstatus::offen);
        b.setVersendet(Bearbeitungsstatus::offen);
        fa.setBearbeitungsstatus(b);
        auftraege->addAuftrag(fa);
        addRow(fa);
        auftraege->speichere();
    }
}

void MainWindow::on_beauftragenButton_clicked()
{
    int selectedRow = ui->tableWidget->currentRow();
    cout << "MainWindow::beauftrageButton_clicked " << selectedRow << endl;
//    Fertigungsauftrag fa=auftraege->getAuftrag(selectedRow);
//    if(fa.getBearbeitungsstatus()->getBeauftragt()!=Bearbeitungsstatus::offen)
//    {
//        // Auftrag wurde bereits beauftragt -> Hinweis
//        QMessageBox msgBox(QMessageBox::Information,"Hinweis","Dieser Fertigungsauftrag ist bereits in Bearbeitung!");
//        msgBox.exec();
//    }else if(auftraege->getIndexBeauftragung()!=-1)
//    {
//        QMessageBox msgBox(QMessageBox::Information,"Hinweis","Anderer Fertigungsauftag wird gerade beauftragt!");
//        msgBox.exec();
//    }
//        timer.setSingleShot(true);
//        timer.start(20000);
     QTimer::singleShot(10000,this,SLOT(resetBeauftragung()));
     auftraege->setIndexBeauftragung(selectedRow);

}
void MainWindow::resetBeauftragung()
{
    auftraege->resetIndexBeauftragung();
}

//void MainWindow::stopTimer(int r)
//{
//    if(r==-1)
//    {
//        timer.stop();
//        cout << "Timer gestoppt " << endl;
//    }
//}
void MainWindow::anzeigenFehlerZustand(QString f)
{
    QMessageBox msgBox(QMessageBox::Critical,"Achtung",f);
    msgBox.exec();
}
