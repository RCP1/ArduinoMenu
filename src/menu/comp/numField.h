/* -*- C++ -*- */
#pragma once
/**
* @file numField.h
* @brief range validated numeric field
*/

#include <menu.h>

// namespace AM5 {

  /**
  * The NumField class links to any numeric type variable
  * and allows changing it between the validation range
  */
  template<typename T,T& value,T low,T high,T step,T tune,typename I=Empty<>>
  class NumField:public I {
    public:
      using I::I;
      using This=NumField<T,value,low,high,step,tune,I>;
      inline NumField()
        :reflex(value)
        // ,low(l)
        // ,high(h)
        // ,step(s)
        // ,tune(t)
        {}
      // constexpr static inline bool canNav() {return true;}
      // inline NavAgent activate() {return {this,&cmds};}
      template<typename N,typename O,typename H>
      inline void print(N& nav,O& out,H& i) {
        // out.template fmtValue<true,Nav,Out,This>(nav,out,*this,0);
        out.template raw(value);
        // out.template fmtValue<false,Nav,Out,This>(nav,out,*this,0);
        I::print(nav,out,i);
      }
      // inline void out(MenuOut &o) const {
      //   //reflex=*value;can not update here!
      //   o<<*value;
      // }
      inline bool up() {
        T s=tunning?tune:step;
        if (value+s<=high) value+=s;
        return true;
      }
      inline bool down() {
        T s=tunning?tune:step;
        if (value-s>=low) {
          value-=s;
          return true;
        }
        return false;
      }
      template<typename Nav> inline bool enter(Nav& nav,Idx at=0) {return tunning^=true;}
      // inline bool enter() {return tunning^=true;}
      inline bool esc() {return true;}//true=>allow unfocus
      inline Modes mode() {return tunning?Modes::Tune:Modes::Edit;}
    protected:
      bool tunning=false;//TODO: this state should be stored on navigation! (or field agent)
      T reflex;//to check if original value changed
      // T low,high,step,tune;
      // static ItemCmd<This> cmds;
  };

  // template<typename T>
  // using NumField=asValue<NavHandler<NumFieldDef<T>>>;
// };
