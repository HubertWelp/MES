#ifndef MESMQTTNODE_H
#define MESMQTTNODE_H
#include "mqttnode.h"
#include "auftragsverwaltung.h"
#include <QObject>

class MESMQTTNode : public QObject
{
    Q_OBJECT
public:
    explicit MESMQTTNode(Auftragsverwaltung* av, QObject* parent=0);
    ~MESMQTTNode();
signals:

public slots:
void beauftragungStarten(int auftragsIndex);

private:
    static Auftragsverwaltung* auftraege;
    static void mqttMessageHandler(char* t, char* m, int l);
    static void bearbeiteTopic1(char* m, int l);
    static void bearbeiteTopic(char* m, int l);
    static void bearbeiteTopic3(char* m, int l);
    static void bearbeiteTopic4(char* m, int l);
    static MQTTNode mqttNode;
};

#endif // MESMQTTNODE_H
