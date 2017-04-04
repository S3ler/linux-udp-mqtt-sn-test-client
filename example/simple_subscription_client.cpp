#include <iostream>
#include "../Fakes/LinuxUdpClientFake.h"

int main() {
    device_address broker_address;
    broker_address.bytes[0] = 127;
    broker_address.bytes[1] = 0;
    broker_address.bytes[2] = 0;
    broker_address.bytes[3] = 1;

    uint16_t port = ntohs(8888);
    memcpy(&broker_address.bytes[4], &port, sizeof(uint16_t));

    LinuxUdpClientFake fourthclient;
    fourthclient.timout_seconds = 31;
    fourthclient.fromport +=9;
    const char *fourth_client_id = "Fourth Client Id9";

    fourthclient.send_connect(&broker_address, fourth_client_id, 500, false, false, false);
    if (!fourthclient.receive_connack(&broker_address, ACCEPTED, false)) {
        std::cout << "Connect failed" << std::endl;
        exit(0);
    }
    std::cout << "Connected" << std::endl;
    uint16_t fourth_register_topic_id = 0;
    const char *fourth_topic_name = "/fourth/registered/subscribed/topic/name";
    uint16_t fourth_topic_msg_id = 17;

    fourthclient.send_register(&broker_address, fourth_topic_msg_id, fourth_topic_name, false);

    if (!fourthclient.receive_regack(&broker_address, fourth_topic_msg_id, &fourth_register_topic_id, ACCEPTED,
                                     false)) {
        std::cout << "register failed" << std::endl;
        exit(0);
    }
    std::cout << "registered" << std::endl;

    uint16_t fourth_subscribe_msg_id = 18;

    // predefined subscription
    uint16_t fourth_predefined_subscribe_registered_topic_id = 0;
    uint8_t granted_predefined_subscription_qos = 0;
    uint16_t fourth_predefined_subscribe_topic_id = 50;
    uint16_t fourth_predefined_subscribe_msg_id = 19;

    fourthclient.send_subscribe(&broker_address, false, fourth_predefined_subscribe_topic_id, fourth_predefined_subscribe_msg_id, granted_predefined_subscription_qos);
    if (!fourthclient.receive_suback(&broker_address, &fourth_predefined_subscribe_registered_topic_id, fourth_predefined_subscribe_msg_id,
                                     &granted_predefined_subscription_qos, ACCEPTED)) {
        std::cout << "subscription failed" << std::endl;
        exit(0);
    }
    std::cout << "subscription predefined - granted qos: " << (int)granted_predefined_subscription_qos << " - topic_id: "<<fourth_predefined_subscribe_registered_topic_id << std::endl;

    // registered subscription
    uint8_t granted_registered_subscription_qos = 0;
    fourthclient.send_subscribe(&broker_address, true, fourth_register_topic_id, fourth_subscribe_msg_id, 2);
    if (!fourthclient.receive_suback(&broker_address, fourth_register_topic_id, fourth_subscribe_msg_id,
                                     &granted_registered_subscription_qos, ACCEPTED)) {
        std::cout << "subscription failed" << std::endl;
        exit(0);
    }
    std::cout << "subscription registered - granted qos: " << (int)granted_registered_subscription_qos << " - topic_id: "<<fourth_register_topic_id << std::endl;

    // topic name subscription
    uint16_t fourth_subscribed_topic_name_topic_id = 0;
    const char *fourth_subscribed_topic_name = "/fourth/topic/name/subscribed/something/other";

    uint16_t fourth_topic_name_predefined_topic_id = 0;
    uint8_t granted_topic_name_subscription_qos = 0;

    fourthclient.send_subscribe(&broker_address, (char *) fourth_subscribed_topic_name, 22, 0);
    if (!fourthclient.receive_suback(&broker_address, &fourth_topic_name_predefined_topic_id, 22,
                                     &granted_topic_name_subscription_qos, ACCEPTED)) {
        std::cout << "subscription failed" << std::endl;
        exit(0);
    }
    std::cout << "subscription topic name - granted qos: "  << (int)granted_topic_name_subscription_qos << " - topic_id: "<<fourth_topic_name_predefined_topic_id << std::endl;

    return 0;
}
