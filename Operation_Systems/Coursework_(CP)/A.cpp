#include <vector>
#include "ABC.hpp"

int main() {
	Message AtoB, *BtoA, AtoC, *CtoA;
	zmq_msg_t msg, out;
	vector<string> text;
	string s;
	int comand;
	AtoB = init_message();
	AtoC = init_message();

	void* context = zmq_ctx_new();
	void* psocket = zmq_socket(context, ZMQ_REQ);
	void* mysocket = zmq_socket(context, ZMQ_REP);
	zmq_bind(mysocket, "tcp://*:5001");
	zmq_connect(psocket, "tcp://localhost:5002");

	AtoB.status = 1;
	send_message(psocket, &AtoB);
	
	CtoA = receive_message(mysocket, &msg);
	if (CtoA->status == 1) cout << "A: C connected\n";
	else {
		cout << "Error: unsuccessful connection C to A";
		return -1;
	}
	zmq_msg_close(&msg);

	BtoA = receive_message(psocket, &msg);
	zmq_msg_close(&msg);

	print_menu();

	cout << "Enter comand:\n";

	bool loop = true;
	while(loop) {
		cout << "=> ";
		cin >> comand;
		switch (comand) {
			case 1:
				// text.clear();
				printf("Enter text, type END to finish:\n");
				cin.ignore(1);
				do{
					cout << "> ";
					getline(cin, s, '\n');
					if (s != "END") {
						text.push_back(s);
					}
				} while (s != "END");
				break;
			case 2:
				if(!text.empty()){
					for (const auto& item : text) {
						AtoC.task = 1;
						send_message(mysocket, &AtoC);
						CtoA = receive_message(mysocket, &msg);
						zmq_msg_close(&msg);
						s = item;
						send_text(mysocket, &s);

						AtoB.sym = item.length();
						AtoB.task = 1;
						send_message(psocket, &AtoB);

						BtoA = receive_message(psocket, &msg);
						if (BtoA->status == 2) {
							zmq_msg_close(&msg);
							CtoA = receive_message(mysocket, &msg);
							if (CtoA->status != 2) {
								zmq_msg_close(&msg);
								cout << "Error while sending string" << endl;
								return -1;
							}
						} else {
							cout << "Error: missing message from B" << endl;
							return -1;
						}
					}
				} else cout << "---No text to send---" << endl;
				break;
			case 3:
				text.clear();
				cout << "---Buffer cleared---" << endl;
				break;
			case 0:
				AtoC.task = 2;
				AtoB.task = 2;
				send_message(mysocket, &AtoC);
				send_message(psocket, &AtoB);
				loop = false;
				break;
		}
	}
	zmq_close(psocket);
	zmq_close(mysocket);
	zmq_ctx_destroy(context);
	return 0; 
}