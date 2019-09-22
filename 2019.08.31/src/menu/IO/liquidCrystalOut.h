/* -*- C++ -*- */
#pragma once
/**
* @file liquidCrystalOut.h
* @author Rui Azevedo
* @brief use arduino standard LCD library as menu output
*/

#include <LiquidCrystal.h>
#include <menu.h>

// namespace Menu {
  template<LiquidCrystal& dev, typename O=TextMeasure>
  struct LiquidCrystalOut:public O {
    using O::O;
    using This = LiquidCrystalOut<dev,O>;
    static inline void setCursor(idx_t x,idx_t y) {
      trace(MDO<<"lcd.setCursor("<<x<<","<<y<<") "<<endl);
      dev.setCursor(x,y);
    }
    template<typename T>
    inline void raw(T i) {
      trace(MDO<<"lcd.raw(\""<<i<<"\") "<<endl);
      dev.print(i);}
    template<typename Out>
    static inline void clrLine(Out& out,idx_t n) {
      trace(MDO<<"lcd.clrLine("<<n<<") "<<endl);
      dev.setCursor(0,n);
      for(int n=0;n<out.width();n++) dev.print(' ');
    }
  };
// };