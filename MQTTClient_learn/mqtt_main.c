#include <stdio.h>

#include "MQTTClient.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#define ADDRESS "tcp://42.192.22.176:1883"
#define USERNAME "Black"
#define PASSWORD "1358"
#define CLIENTID "c-client"
#define QOS 0
#define TOPIC "emqx/c-test"
#define TIMEOUT 10000L

void publish(MQTTClient client, char *topic, char *payload)
{
	MQTTClient_message message = MQTTClient_message_initializer;
	message.payload = payload;
	message.payloadlen = strlen(payload);
	message.qos = QOS;
	message.retained = 0;
	MQTTClient_deliveryToken token;
	MQTTClient_publishMessage(client, topic, &message, &token);
	MQTTClient_waitForCompletion(client, token, TIMEOUT);
	printf("Send `%s` to topic `%s` \n", payload, TOPIC);
}

int on_message(void *context, char *topicName, int topicLen,
	       MQTTClient_message *message)
{
	char *payload = message->payload;
	printf("Received `%s` from `%s` topic \n", payload, topicName);
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 1;
}

int main(int argc, char *argv[])
{
	int ret;
	MQTTClient client;
	int status;

	status = MQTTClient_create(&client, ADDRESS, CLIENTID, 0, NULL);
	if (status != MQTTCLIENT_SUCCESS) {
		printf("Create Client Error!");
		return status;
	}

	MQTTClient_connectOptions conn_opts =
		MQTTClient_connectOptions_initializer;
	conn_opts.username = USERNAME;
	conn_opts.password = PASSWORD;
	MQTTClient_setCallbacks(client, NULL, NULL, on_message, NULL);
	if ((ret = MQTTClient_connect(client, &conn_opts)) !=
	    MQTTCLIENT_SUCCESS) {
		printf("Failed to connect, return code %d\n", ret);
		exit(-1);
	} else {
		printf("Connected to MQTT Broker!\n");
	}
	// subscribe topic
	MQTTClient_subscribe(client, TOPIC, QOS);
	char payload[16];
	for (int i = 0; i < 100; i += 1) {
		// publish message to broker
		snprintf(payload, 16, "message-%d", i);
		publish(client, TOPIC, payload);
		sleep(1);
	}
	MQTTClient_disconnect(client, TIMEOUT);
	MQTTClient_destroy(&client);
	return ret;
}
