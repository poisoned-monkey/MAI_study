#include "ABC.hpp"

string adr = "tcp://localhost:";

int main(){
	Message BtoC, *CtoB, BtoA, *AtoB;
	zmq_msg_t msg;
	BtoA = init_message();
	BtoC = init_message();

	void* context = zmq_ctx_new();
	void* psocket = zmq_socket(context, ZMQ_REQ);
	void* mysocket = zmq_socket(context, ZMQ_REP);
	zmq_bind(mysocket, "tcp://*:5002");
	zmq_connect(psocket, "tcp://localhost:5003");

	BtoC.status = 1;
	send_message(psocket, &BtoC);

	AtoB = receive_message(mysocket, &msg);
	if (AtoB->status == 1) cout << "B: A connected\n";
	else {
		cout << "Error: unsuccessful connection A to B";
		return -1;
	}
	zmq_msg_close(&msg);
	
	BtoA.status = 1;
	send_message(mysocket, &BtoA);

	bool loop = true;
	while(loop){
		AtoB = receive_message(mysocket, &msg);
		switch(AtoB->task){
			case 1:
				cout << "---------------" << endl;
				cout << "A sent " << AtoB->sym << " symbols" << endl;
				zmq_msg_close(&msg);
				BtoA.status = 2;
				send_message(mysocket, &BtoA);
				CtoB = receive_message(psocket, &msg);
				if(CtoB->task == 1){
					cout << "C recieved " << CtoB->sym << " symbols" << endl;
					cout << "---------------" << endl << endl;
					zmq_msg_close(&msg);
					BtoC.status = 2;
					send_message(psocket, &BtoC);
				} else {
					cout << "Error: missing message from C";
					return -1;
				}
				break;
			case 2: 
				loop = false;
				break;
		}
	}
	zmq_close(psocket);
	zmq_close(mysocket);
	zmq_ctx_destroy(context);
	return 0;
}