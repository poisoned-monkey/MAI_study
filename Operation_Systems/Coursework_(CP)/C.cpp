#include "ABC.hpp"

string adr = "tcp://localhost:";

int main() {
	Message CtoA, *AtoC, CtoB, *BtoC;
	string text;
	zmq_msg_t msg;
	CtoA = init_message();
	CtoB = init_message();

	void* context = zmq_ctx_new();
	void* psocket = zmq_socket(context, ZMQ_REQ);
	void* mysocket = zmq_socket(context, ZMQ_REP);
	zmq_bind(mysocket, "tcp://*:5003");
	zmq_connect(psocket, "tcp://localhost:5001");
	
	CtoA.status = 1;
	send_message(psocket, &CtoA);

	BtoC = receive_message(mysocket, &msg);
	if (BtoC->status == 1) cout << "C: B connected\n";
	else {
		cout << "Error: unsuccessful connection B to C";
		return -1;
	}
	zmq_msg_close(&msg);

	bool loop = true;
	while(loop){
		AtoC = receive_message(psocket, &msg);
		switch(AtoC->task){
			case 1:
			{
				zmq_msg_close(&msg);
				send_message(psocket, &CtoA);
				string recvd = receive_text(psocket, &msg);
				CtoB.sym = recvd.length();
				CtoB.task = 1;
				zmq_msg_close(&msg);
				send_message(mysocket, &CtoB);

				BtoC = receive_message(mysocket, &msg);
				// cout << "Recieved string: " << recvd << endl;
				if(!recvd.empty()) cout << "Recieved string: " << recvd << endl;
				else cout << "Empty line" << endl;

				if(BtoC->status == 2){
					zmq_msg_close(&msg);
					CtoA.status = 2;
					send_message(psocket, &CtoA);
				}
				break;
			}
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