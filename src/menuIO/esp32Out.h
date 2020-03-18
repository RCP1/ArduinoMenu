/* -*- C++ -*- */

#ifndef RSITE_ARDUINO_MENU_ESP32OUT
  #define RSITE_ARDUINO_MENU_ESP32OUT
  #ifdef ESP32
    #include "../menuDefs.h"
    #include <WiFi.h>
    // based on WebServer Sockets:
    //   https://github.com/Links2004/arduinoWebSockets
    #include <WebSocketsServer.h>
    #include <WebServer.h>
    #include <vector>
    #include "xmlFmt.h"

    using namespace std;

    namespace Menu {

      class esp32Out:public webOut {
        public:
          esp32Out(
            idx_t* t,
            panelsList& p,
            menuOut::styles styles=(menuOut::styles)(redraw|expandEnums)
          ):webOut(t,p,styles) {}
          menuOut& fill(
            int x1, int y1, int x2, int y2,char ch=' ',
            colorDefs color=bgColor,
            bool selected=false,
            status stat=enabledStatus,
            bool edit=false) override {return *this;}
          void setCursor(idx_t x,idx_t y,idx_t panelNr=0) override {}
          void clear() override {panels.reset();}
          void clear(idx_t panelNr) override {
            setCursor(0,0,panelNr);
            panels.nodes[panelNr]=NULL;
          }
          void clearLine(
            idx_t ln,
            idx_t panelNr=0,
            colorDefs color=bgColor,
            bool selected=false,
            status stat=enabledStatus,
            bool edit=false
          ) override {}
          void setColor(colorDefs c,bool selected=false,status s=enabledStatus,bool e=false) override {};
          //template<typename T> esp32Out& operator<<(T t)=0;
      };

      class esp32BufferedOut:public esp32Out {
        public:
          String response;
          using esp32Out::esp32Out;
          template<typename T> inline esp32BufferedOut& operator<<(T t) {response<<t;return *this;}
          size_t write(uint8_t ch) override {response+=(char)ch;return 1;}
      };

      menuOut& operator<<(menuOut&o,classes c);
      template<typename T> inline String& operator<<(String& o,T t) {return o.operator+=(t);}

      class esp32_WebServerOut:public esp32BufferedOut {
        public:
          WebServer &server;
          //using esp32Out::esp32Out;
          esp32_WebServerOut(
            WebServer &srv,
            /*const colorDef<esp32Out::webColor> (&c)[nColors],*/
            idx_t* t,
            panelsList& p
          ):esp32BufferedOut(t,p),server(srv) {}
          size_t write(uint8_t ch) override {response<<(char)ch;return 1;}
          // template<typename T> inline esp32_WebServerOut& operator<<(T t) {response<<t;return *this;}
      };

      class esp32_WebServerStreamOut:public esp32Out {
        public:
          WebServer &server;
          inline esp32_WebServerStreamOut(
            WebServer &srv,
            idx_t* t,
            panelsList& p
          ):esp32Out(t,p),server(srv) {}
          inline size_t write(uint8_t ch) override {
            char c[2]={ch,0};
            server.sendContent(c);
            return 1;
          }
          template<typename T> inline esp32_WebServerStreamOut& operator<<(T t) {
            server.sendContent(String()+t);
            return *this;
          }
      };

      // class esp32_WebSocketOut:public esp32BufferedOut {
      //   public:
      //     //client num... well we only serve a client at a time, so its safe to put t here
      //     // of course this kind of code is not thead safe...but we dont have theads anyway
      //     uint8_t num;
      //     String response;
      //     WebSocketsServer &webSocket;
      //     esp32_WebSocketOut(WebSocketsServer &socket,idx_t* tops,panelsList& panels)
      //       :webSocket(socket),esp32BufferedOut(tops,panels,(menuOut::styles)(minimalRedraw|expandEnums)) {}
      //     size_t write(uint8_t ch) override {response<<(char)ch;return 1;}
      // };

      //template<typename T> inline esp32_WebServerOut& operator<<(esp32_WebServerOut&o , T t) {return o.operator<<(t);}
      //template<typename T> inline esp32_WiFiClientOut& operator<<(esp32_WiFiClientOut&o , T t) {return o.operator<<(t);}
      //template<typename T> inline esp32Out& operator<<(esp32Out&o , T t) {return o.operator<<(t);}

    }//namespace Menu
    #include "esp32Out.hpp"
  #endif
#endif
