#ifndef CLIENT_H_
#define CLIENT_H_

#include "client/video.h"
#include "game_connection.h"
#include <irrlicht.h>

class GameInterface;
class ClientGame;
class Input;
class Client : public irr::IEventReceiver
{
   public:
      Client();
      void go();
      bool connect(char* host);
      bool init();
      virtual ~Client();

      // overrides
      bool OnEvent(const irr::SEvent& event);
   protected:
   private:
      Video* mVideo;
      Input* mInput;
      GameConnection* mConnection;
      RefPtr<GameInterface> mInterface;
      ClientGame *mGame;

      bool step();
      void serviceConnection();
};

#endif /* CLIENT_H_ */
