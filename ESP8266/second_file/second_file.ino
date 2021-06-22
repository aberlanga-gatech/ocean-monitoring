// HTTP protocols:
// internet to router: public IP
// router to device: private IP
// http operates through the OSI layers
// the http protocol lives in the application, presentation and session layers (TCP?IP application layer)
// tcp/udp are in the transport layer
// IP is in the network layer
// data link and physical (network interface for TCP/IP) correspond to ethernet and other link-layer protocols
// TCP/IP is a client-server model of communication
// packetization for E2E communication (address, transmission, routing, receiving)
// UDP has less headers. used when an inexact package amount is needed (e.g. VOIP: can afford to lose some packets)
// time-sensitive applications use UDP over TCP/IP
// HTTP is supported on top of TCP/IP -> used to deliver data on the WWW
// web client sends data to the HTTP pipeline, web server receives it on the pipeline
// http is more verbose in headers and addressing because data delivery is a priority
// MQTT is a publish-subscribe model for lightweight M2M communication
// server does not access and store data from a pipeline, rather the client sends data directly to the server
// the server only relays the data to the subscribers; simple i/o
// topics work to sort the controls / messages
// different QoS: fire & forget 0, at least once received 1, exactly receive 2
// QoS 0 only publishes regardless of connection success
// QoS 1 message is stored and able to be sent more than once
// QoS 2 message is stored and survives connection lost with no duplicates


// thingSpeak is a IoT suite with MATLAB that allows various protocols (all except for the classified ones)
// TCP is better than IP for data because TCP is fast and lossless
// IP is unreliable unless paired with TCP (hackable)
// IP is good for establishing connections and making datagrams (header and data) to establish the connection route
// IP has no security so pure IP packages can be easily intercepted
// IP and UDP dont require a connection to be established: data can be sent into space for anyone to get
// FTP is used to copy files between hosts
// FTP uses two processes: Control and Data Transfer
// one establishes the connection with TCP/IP, the other one actually sends payloads
// Telnet is used to access and control a client from another one
// Telnet clients usually have UIs to facilitate navigation -- they operate as a standalone protocol
// SSH is similar to Telnet but it is less secure and not as versatile
// HTTP is a communication protocol (like FTP)
// defines the mechanism for communication between browser and server
// no copying with HTTP, only spectating on request
// HTTP is a request and response protocol
// HTTP has additional request lines/headers for security and data deliverability


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
