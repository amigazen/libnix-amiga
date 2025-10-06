#ifndef _BASE_H_
#define _BASE_H_

#ifdef SMALL_DATA

#define A4(x) "a4@(" #x ":W)"

#define GETAGBASE  movel a4@(_AmigaGuideBase:W),a6
#define GETASLBASE movel a4@(_AslBase:W),a6
#define GETBULBASE movel a4@(_BulletBase:W),a6
#define GETDOSBASE movel a4@(_DOSBase:W),a6
#define GETDTBASE  movel a4@(_DataTypesBase:W),a6
#define GETGADBASE movel a4@(_GadToolsBase:W),a6
#define GETGFXBASE movel a4@(_GfxBase:W),a6
#define GETINTBASE movel a4@(_IntuitionBase:W),a6
#define GETLOCBASE movel a4@(_LocaleBase:W),a6
#define GETLOWBASE movel a4@(_LowLevelBase:W),a6
#define GETRETBASE movel a4@(_RealTimeBase:W),a6
#define GETUTLBASE movel a4@(_UtilityBase:W),a6
#define GETWBBASE  movel a4@(_WorkbenchBase:W),a6


#else

#define A4(x) #x

#define GETAGBASE  movel _AmigaGuideBase,a6
#define GETASLBASE movel _AslBase,a6
#define GETBULBASE movel _BulletBase,a6
#define GETDOSBASE movel _DOSBase,a6
#define GETDTBASE  movel _DataTypesBase,a6
#define GETGADBASE movel _GadToolsBase,a6
#define GETGFXBASE movel _GfxBase,a6
#define GETINTBASE movel _IntuitionBase,a6
#define GETLOCBASE movel _LocaleBase,a6
#define GETLOWBASE movel _LowLevelBase,a6
#define GETRETBASE movel _RealTimeBase,a6
#define GETUTLBASE movel _UtilityBase,a6
#define GETWBBASE  movel _WorkbenchBase,a6

#endif

#endif _BASE_H_
