cmake_minimum_required(VERSION 3.2)
project(FakeClientTests)

set(CMAKE_CXX_STANDARD 11)

add_executable(runSimpleFakeClientPublishTests
        ../Fakes/LinuxUdpClientFake.cpp
        ../Fakes/LinuxUdpClientFake.h
        simple_publish_client.cpp
        )

add_executable(runSimpleFakeClientWillTests
        ../Fakes/LinuxUdpClientFake.cpp
        ../Fakes/LinuxUdpClientFake.h
        simple_test_client_with_will.cpp
        )

add_executable(runSimpleFakeClientSubscriptionTests
        ../Fakes/LinuxUdpClientFake.cpp
        ../Fakes/LinuxUdpClientFake.h
        simple_subscription_client.cpp
        )

add_executable(runSimpleFakeClientSubscriptionReceivePublishTests
        ../Fakes/LinuxUdpClientFake.cpp
        ../Fakes/LinuxUdpClientFake.h
        simple_subscription_receive_publish_client.cpp
        )

add_executable(runSimpleFakeClientConnectTests
        ../Fakes/LinuxUdpClientFake.cpp
        ../Fakes/LinuxUdpClientFake.h
        simple_connect_client.cpp
        )

