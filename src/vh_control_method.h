#ifndef VH_CONTROL_METHOD_H
#define VH_CONTROL_METHOD_H

#include "ProtectedClient.h"
#include "AgentControl.h"
#include "global_declaration.h"

void vh_speak(ProtectedClient<imi::AgentControlClient> &Client, const char* reply);
void vh_emotion(ProtectedClient<imi::AgentControlClient> &Client,::imi::Facial_Expression::type e,const float& intensity);
void vh_gesture(ProtectedClient<imi::AgentControlClient> &Client, imi::Animation::type a);
void vh_talk(ProtectedClient<imi::AgentControlClient> &Client,::imi::Facial_Expression::type e, imi::Animation::type a, const char* reply);

#endif