#ifndef MQTTNODE_H
#define MQTTNODE_H

#include "MQTTClient.h"

#define ADDRESS     "tcp://192.168.77.253:1883"
//#define ADDRESS     "tcp://127.0.0.1:1883"
#define CLIENTID    "MES"
#define TOPIC       "welp"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

class MQTTNode
{

public:
    MQTTNode(char* sURI=ADDRESS, char* cID=CLIENTID);
    ~MQTTNode();
    void setMsgRcvdCallback(void (*callback)(char*, char*, int));
    void subscribe(char* topic, int qos=0);
    void unsubscribe(char* topic);
    void publish(char* topic, char* message, int len, int qos=0);


private:
    static void delivered(void *context, MQTTClient_deliveryToken dt);
    static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
    static void connlost(void *context, char *cause);

    MQTTClient client;
    char serverURI[500];
    char clientID[500];
    static void (*msgRcvdCallback)(char*, char*, int);

};

#endif // MQTTNODE_H
