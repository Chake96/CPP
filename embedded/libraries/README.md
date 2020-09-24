C++ Libraries
=============
Table of Contents
-----------------
-Packets
-Robot

#### Packets
This library is a generic library for creating and sending messages between two transceivers.
The packets are serializable into byte streams which can be sent through any network. The minimum size of packet is 8 bytes and the largest size is 61 bytes. 61 Bytes was chosen as it is the size of the buffer for the RFM69HCW with AES encryption enabled.
-packet.h -> the base class from which all packet classes are derived from
        1. Provides a distinct interface to perform all universal operations on a packet
        2. Defines a is_pointer template utility to determine if the packet is a pointer or not
-packets.h -> defines the packets namespace and the types enum class
    1. Number Packet
    2. Plan Packet
    3. Error Packet
    4. Communication Packet
    5. Ultrasonic Sensor Packet
    6. Infared Sensor Packet
    7. Spectrometer Sensor Packet
    8. IMU Sensor Packet

-pair.h -> contains a lightweight implementation of std::pair
    1. Used in absence of standard library

#### Robot
This library is used to represent the physical robot and its operation

- motor.h -> a header only base class representation of a generic physical electric motor

- bldc.h -> derived from motor, this class represents the physical BLDC motors used on the robot

- plan.h -> this is a class used to represent the set of instructions the robot is to run, plans are created by the remote basestation and wirelessly transmitted to the robot for future execution.
    -this header file contains the enum class for command types
    -this header file also contains the struct for commands:
        1)commands are used to build complete plans
        2)commands have a type defined by the command_options enum
        3)commands have a duration, this can either be a measurement of time or distance
