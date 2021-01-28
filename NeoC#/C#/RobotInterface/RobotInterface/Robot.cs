using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Utilities;

namespace RobotInterface
{
    class Robot
    {
        public ConcurrentQueue<Message> messageQueue = new ConcurrentQueue<Message>();
        public float timestamp;
        public float positionXOdo;
        public float positionYOdo;
        public float positionThetaOdo;
        public float vLin;
        public float vAng;

        public float vLinCo;
        public float vAngCo;
        public float vLinPo;
        public float vAngPo;
        public float errLin;
        public float errAng;


    }

    class Message
    {
        public UInt16 Function;
        public UInt16 PayloadLength;
        public byte[] Payload;

        public Message(UInt16 function, UInt16 payloadLength, byte[] payload)
        {
            Function = function;
            PayloadLength = payloadLength;
            Payload = payload;
        }
    }
}
