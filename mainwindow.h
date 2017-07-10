#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "auftragsverwaltung.h"
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, Auftragsverwaltung* av=NULL);
    ~MainWindow();
//    void setAuftragsverwaltung(Auftragsverwaltung* av);

private slots:
    void on_hinzufuegenButton_clicked();

    void on_beauftragenButton_clicked();

    void updateRow(int row);
    void resetBeauftragung();
    void anzeigenFehlerZustand(QString f);
//    void stopTimer(int r);
private:
    Ui::MainWindow *ui;
    void addRow(Fertigungsauftrag fa);
    QIcon statusIcon[3];
//    QTimer timer;
    Auftragsverwaltung* auftraege;
};

#endif // MAINWINDOW_H
