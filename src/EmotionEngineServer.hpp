#ifndef I2P_EMOTIONENGINESERVER_H
#define I2P_EMOTIONENGINESERVER_H

#include "Datastructure.h"
#include "AffectiveSystem.h"

#include "EmotionEngineService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>


class EmotionEngineServiceHandler : virtual public imi::EmotionEngineServiceIf {
 public:
  EmotionEngineServiceHandler( Affsys * in_aff_sys) {
	m_aff_sys = in_aff_sys;
  }

  void emotion(const  ::imi::Microseconds timestamp, const  ::imi::Emotion::type emotion, const double intensity) {
    Stimuli s;
	if (emotion == ::imi::Emotion::JOY) s.Etype = 12;
	if (emotion == ::imi::Emotion::DISAPPOINTMENT) s.Etype = 2;
	s.Intensity = intensity;
	s.Time = (double) timestamp * 1e-6;
	m_aff_sys->input_emo(s);
  }

private:
	Affsys * m_aff_sys;

};


#endif