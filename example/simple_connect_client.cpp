#include <iostream>
#include "../src/LinuxUdpClientFake.h"

int main() {
    device_address broker_address;
    broker_address.bytes[0] = 127;
    broker_address.bytes[1] = 0;
    broker_address.bytes[2] = 0;
    broker_address.bytes[3] = 1;

    uint16_t port = ntohs(1883);
    memcpy(&broker_address.bytes[4], &port, sizeof(uint16_t));

    LinuxUdpClientFake fourthclient;
    fourthclient.timout_seconds = 31;
    fourthclient.fromport +=1;
    const char *fourth_client_id = "Fourth Client Id1";

    const char *fourth_m1_publish_data = "Publish Message with more text to a Predefined Topic without connect";
    fourthclient.send_publish(&broker_address,
                              (const uint8_t *) fourth_m1_publish_data, strlen(fourth_m1_publish_data) + 1, 50,
                              -1, false, false);
    std::cout << "published qos -1" << std::endl;


    fourthclient.send_connect(&broker_address, fourth_client_id, 100, false, false, false);
    if (!fourthclient.receive_connack(&broker_address, ACCEPTED, false)) {
        std::cout << "Connect failed" << std::endl;
        exit(0);
    }
    std::cout << "Connected" << std::endl;
    uint16_t fourth_register_topic_id = 0;
    const char *fourth_topic_name = "/fourth/topic/name";
    uint16_t fourth_topic_msg_id = 17;

    fourthclient.send_register(&broker_address, fourth_topic_msg_id, fourth_topic_name, false);

    if (!fourthclient.receive_regack(&broker_address, fourth_topic_msg_id, &fourth_register_topic_id, ACCEPTED,
                                     false)) {
        std::cout << "register failed" << std::endl;
        exit(0);
    }
    std::cout << "registered" << std::endl;
    const char *fourth_publish_data = "Fourth Client Publish Message with more text";
    int8_t fourth_publish_qos = 1;
    fourthclient.send_publish(&broker_address,
                              (const uint8_t *) fourth_publish_data, strlen(fourth_publish_data) + 1,
                              fourth_register_topic_id, fourth_publish_qos, true,
                              false);
    if (!fourthclient.receive_puback(&broker_address, fourth_register_topic_id, ACCEPTED, false)) {
        std::cout << "publish failed" << std::endl;
        exit(0);
    }

    // predefined subscription
    uint16_t fourth_predefined_subscribe_registered_topic_id = 0;
    uint8_t granted_predefined_subscription_qos = 0;
    uint16_t fourth_predefined_subscribe_topic_id = 50;
    uint16_t fourth_predefined_subscribe_msg_id = 19;

    fourthclient.send_subscribe(&broker_address, false, fourth_predefined_subscribe_topic_id, fourth_predefined_subscribe_msg_id, 1);
    if (!fourthclient.receive_suback(&broker_address, &fourth_predefined_subscribe_registered_topic_id, fourth_predefined_subscribe_msg_id,
                                     &granted_predefined_subscription_qos, ACCEPTED)) {
        std::cout << "subscription failed" << std::endl;
        exit(0);
    }
    std::cout << "subscription predefined - granted qos: " << (int)granted_predefined_subscription_qos << " - topic_id: "<<fourth_predefined_subscribe_registered_topic_id << std::endl;


    fourthclient.send_disconnect(&broker_address, false);
    if (!fourthclient.receive_disconnect(&broker_address, true)) {
        std::cout << "disconnect failed" << std::endl;
        exit(0);
    }
    std::cout << "disconnected" << std::endl;


    // connect this time with clean session
    fourthclient.send_connect(&broker_address, fourth_client_id, 100, true, false, false);
    if (!fourthclient.receive_connack(&broker_address, ACCEPTED, false)) {
        std::cout << "Connect with clean session failed" << std::endl;
        exit(0);
    }
    std::cout << "Connected with clean session" << std::endl;




    fourthclient.send_disconnect(&broker_address, false);
    if (!fourthclient.receive_disconnect(&broker_address, true)) {
        std::cout << "disconnect failed" << std::endl;
        exit(0);
    }
    std::cout << "disconnected from clean session" << std::endl;

    return 0;
}
