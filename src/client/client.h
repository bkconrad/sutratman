#ifndef CLIENT_H
#define CLIENT_H

#include "client/video.h"
#include "client_connection.h"

class Client
{
   public:
      Client();
      void go();
      bool init();
      virtual ~Client();
   protected:
   private:
      Video* mVideo;
      ClientConnection* mConnection;
      RefPtr<NetInterface> mInterface;

      bool connect(char* host);
      bool step();
      void serviceConnection();
};

#endif // CLIENT_H
