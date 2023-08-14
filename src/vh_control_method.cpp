#include "vh_control_method.h"

void vh_speak(ProtectedClient<imi::AgentControlClient> &Client, const char* reply){
	try 
	{	
			Client.getClient()->speak(reply,0);	
	}
	catch( apache::thrift::TException &tx ) 
	{
			std::cerr << "EXCEPTION opening the network conn: " << tx.what() << "\n";
	}
}
void vh_emotion(ProtectedClient<imi::AgentControlClient> &Client,::imi::Facial_Expression::type e, const float& intensity){
	try 
	{
			//Client.getClient()->setEmotionalState(e,10*intensity);
			Client.getClient()->setFaceExpression(e,10*intensity);
	}
	catch( apache::thrift::TException &tx ) 
	{
			std::cerr << "EXCEPTION opening the network conn: " << tx.what() << "\n";
	}
}
void vh_gesture(ProtectedClient<imi::AgentControlClient> &Client, imi::Animation::type a){
	try 
	{
	        Client.getClient()->playAnimation(a);	
	}
	catch( apache::thrift::TException &tx ) 
	{
			std::cerr << "EXCEPTION opening the network conn: " << tx.what() << "\n";
	}
}

void vh_talk(ProtectedClient<imi::AgentControlClient> &Client,::imi::Facial_Expression::type e, imi::Animation::type a, const char* reply){
	try 
	{
			Client.getClient()->setFaceExpression(e,10);
			Client.getClient()->speak(reply,0);
	        Client.getClient()->playAnimation(a);	
	}
	catch( apache::thrift::TException &tx ) 
	{
			std::cerr << "EXCEPTION opening the network conn: " << tx.what() << "\n";
	}
}