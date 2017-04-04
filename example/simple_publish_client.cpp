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
    fourthclient.fromport +=1;
    const char *fourth_client_id = "Fourth Client Id1";

    const char *fourth_m1_publish_data = "Publish Message with more text to a Predefined Topic without connect";
    fourthclient.send_publish(&broker_address,
                              (const uint8_t *) fourth_m1_publish_data, strlen(fourth_m1_publish_data) + 1, 50,
                              -1, false, false);
    std::cout << "published qos -1" << std::endl;


    fourthclient.send_connect(&broker_address, fourth_client_id, 20, false, false, false);
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
    std::cout << "published qos 0 predefined" << std::endl;
    const char *fourth_second_publish_data = "Publish Message with more text to a Predefined Topic";
    fourthclient.send_publish(&broker_address,
                              (const uint8_t *) fourth_second_publish_data, strlen(fourth_second_publish_data) + 1, 50,
                              0, false, false);
    std::cout << "published qos 0" << std::endl;

    std::cout << "published qos 1 registered" << std::endl;
    const char *fourth_third_publish_data = "Publish Message with more text to a Registered Topic";
    fourthclient.send_publish(&broker_address,
                              (const uint8_t *) fourth_third_publish_data, strlen(fourth_third_publish_data) + 1, fourth_register_topic_id,
                              1, true, false);
    if (!fourthclient.receive_puback(&broker_address, fourth_register_topic_id, ACCEPTED, false)) {
        std::cout << "publish failed" << std::endl;
        exit(0);
    }
    std::cout << "published qos 1" << std::endl;


    fourthclient.send_disconnect(&broker_address, false);
    if (!fourthclient.receive_disconnect(&broker_address, true)) {
        std::cout << "disconnect failed" << std::endl;
        exit(0);
    }
    std::cout << "disconnected" << std::endl;

    return 0;
}
