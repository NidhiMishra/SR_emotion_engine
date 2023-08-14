import sys
sys.path.append("../gen-py")
sys.path.append("../src")

import I2P.ttypes
from Inputs import EmotionEngineService
import Inputs.constants
from Inputs.ttypes import *

from thrift.transport import TTransport
from thrift.transport import TSocket
from thrift.protocol import TBinaryProtocol
from thrift.protocol import TCompactProtocol

port = Inputs.constants.DEFAULT_EMOTIONENGINE_SERVICE_PORT
transport = TSocket.TSocket("localhost", port)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)
transport.open()

# Use the service we already defined
print 'Starting python client...'
service = EmotionEngineService.Client(protocol)
service.emotion(0,4,1)
