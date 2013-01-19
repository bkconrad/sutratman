#ifndef CLIENT_H_
#define CLIENT_H_

#include "client/video.h"
#include "client_connection.h"

class Client
{
   public:
      Client();
      void go();
      bool connect(char* host);
      bool init();
      virtual ~Client();
   protected:
   private:
      Video* mVideo;
      ClientConnection* mConnection;
      RefPtr<NetInterface> mInterface;

      bool step();
      void serviceConnection();
};

#endif /* CLIENT_H_ */
