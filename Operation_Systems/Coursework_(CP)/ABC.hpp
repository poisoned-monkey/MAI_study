#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "zmq.hpp"
using namespace std;

typedef struct {
	int sym;
	int task;
	int status;
} Message;

void print_menu() {
	cout << "1 - enter text" << endl
	<< "2 - send text" << endl
	<< "3 - clear buffer" << endl
	<< "0 - exit" << endl;
}

void send_message(void* socket, Message* out) {
	zmq_msg_t msg;
	zmq_msg_init_size(&msg, sizeof(Message));
	memcpy(zmq_msg_data(&msg), out, sizeof(Message));
	zmq_msg_send(&msg, socket, 0);
	zmq_msg_close(&msg);
}

void send_text(void* socket, string* text) {
	zmq_msg_t msg;
	zmq_msg_init_size(&msg, text->size());
	memcpy(zmq_msg_data(&msg), text->c_str(), text->size());
	zmq_msg_send(&msg, socket, 0);
	zmq_msg_close(&msg);
}

string receive_text(void* socket, zmq_msg_t* msg) {
	string text;
	zmq_msg_init(msg);
	zmq_msg_recv(msg, socket, 0);
	char* ptr = static_cast<char*>(zmq_msg_data(msg));
	return string(ptr, zmq_msg_size(msg));
}

Message* receive_message(void* socket, zmq_msg_t* msg) {
	Message *in;
	zmq_msg_init(msg);
	zmq_msg_recv(msg, socket, 0);
	in = static_cast<Message*>(zmq_msg_data(msg));
	return in;
}

Message init_message(){
	Message mes;
	mes.sym = -1;
	mes.task = -1;
	mes.status = -1;
	return mes;
}