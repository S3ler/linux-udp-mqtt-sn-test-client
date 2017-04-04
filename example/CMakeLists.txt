cmake_minimum_required(VERSION 3.2)
project(FakeClientTests)

set(CMAKE_CXX_STANDARD 11)

add_executable(runSimpleFakeClientPublishTests
        ../src/LinuxUdpClientFake.cpp
        ../src/LinuxUdpClientFake.h
        ../Gateway/global_defines.h
        ../Gateway/mqttsn/mqttsn_messages.h
        simple_publish_client.cpp
        )

add_executable(runSimpleFakeClientWillTests
        ../src/LinuxUdpClientFake.cpp
        ../src/LinuxUdpClientFake.h
        ../Gateway/global_defines.h
        ../Gateway/mqttsn/mqttsn_messages.h
        simple_test_client_with_will.cpp
        )

add_executable(runSimpleFakeClientSubscriptionTests
        ../src/LinuxUdpClientFake.cpp
        ../src/LinuxUdpClientFake.h
        ../Gateway/global_defines.h
        ../Gateway/mqttsn/mqttsn_messages.h
        simple_subscription_client.cpp
        )

add_executable(runSimpleFakeClientSubscriptionReceivePublishTests
        ../src/LinuxUdpClientFake.cpp
        ../src/LinuxUdpClientFake.h
        ../Gateway/global_defines.h
        ../Gateway/mqttsn/mqttsn_messages.h
        simple_subscription_receive_publish_client.cpp
        )

add_executable(runSimpleFakeClientConnectTests
        ../src/LinuxUdpClientFake.cpp
        ../src/LinuxUdpClientFake.h
        ../Gateway/global_defines.h
        ../Gateway/mqttsn/mqttsn_messages.h
        simple_connect_client.cpp
        )

