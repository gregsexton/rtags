#ifndef JSParser_h
#define JSParser_h

#include <RTags.h>
#include <Location.h>
#include <CursorInfo.h>
#include <rct/Log.h>
#include <rct/Map.h>
#include <rct/Path.h>
#include <rct/String.h>
#include <v8.h>

class JSParser
{
public:
    JSParser() : mIsolate(0), mFileId(0), mSymbols(0), mSymbolNames(0), mErrors(0) {}
    ~JSParser();
    bool init();

    bool parse(const Path &path, const String &contents,
               SymbolMap *cursors,
               SymbolNameMap *symbolNames,
               String *errors,
               String *json = 0);
private:
    bool recurseObject(v8::Handle<v8::Object> object, const char *name);
    void handleIdentifier(v8::Handle<v8::Object> object);

    v8::Persistent<v8::Context> mContext;
    v8::Persistent<v8::Object> mEsprima;
    v8::Persistent<v8::Function> mParse;
    v8::Isolate *mIsolate;
    enum Flag {
        NoFlag = 0x0,
        TreatRefsAsWeakVariables = 0x1
    };
    List<Map<String, uint32_t> > mScope;
    List<String> mParents;
    uint32_t mFileId;
    SymbolMap *mSymbols;
    SymbolNameMap *mSymbolNames;
    String *mErrors;
};


#endif
