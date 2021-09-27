#include <nan.h>
#include <pp/Common.h>
#include <pp/performance/Beatmap.h>
#include <pp/performance/osu/OsuScore.h>
#include <pp/performance/taiko/TaikoScore.h>
#include <pp/performance/catch/CatchScore.h>
#include <pp/performance/mania/ManiaScore.h>

using namespace v8;
using namespace pp;

#ifdef _WIN32
    #pragma comment(lib, "Ws2_32.lib")
#endif

NAN_METHOD(calculatePP) {
    Isolate* isolate = info.GetIsolate();
    Local<Context> context = isolate->GetCurrentContext();

    if (info.Length() < 2) {
        isolate->ThrowException(v8::Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
        return;
    }
    if(!info[0]->IsString() || !info[1]->IsNumber() || !info[2]->IsNumber() || !info[3]->IsNumber() || !info[4]->IsNumber() || !info[5]->IsNumber() || !info[6]->IsNumber() || !info[7]->IsNumber() || !info[8]->IsNumber() || !info[9]->IsNumber() || !info[10]->IsNumber() || !info[11]->IsNumber() || !info[12]->IsNumber()) {
        isolate->ThrowException(v8::Exception::TypeError(String::NewFromUtf8(isolate,"Wrong arguments").ToLocalChecked()));
        return;
    }
    EGamemode mode = pp::ToGamemode(*String::Utf8Value(isolate, info[0].As<String>()));
    int beatmapID = info[1].As<Number>()->Value();
    int score = info[2].As<Number>()->Value();
    int maxcombo = info[3].As<Number>()->Value();
    int Num300 = info[4].As<Number>()->Value();
    int Num100 = info[5].As<Number>()->Value();
    int Num50 = info[6].As<Number>()->Value();
    int NumMiss = info[7].As<Number>()->Value();
    int NumGeki = info[8].As<Number>()->Value();
    int NumKatu = info[9].As<Number>()->Value();
    EMods mods = static_cast<EMods>((int)std::round(info[10].As<Number>()->Value()));
    int numHitCicles = info[11].As<Number>()->Value();
    int numSpinners = info[12].As<Number>()->Value();
    const char kPathSeparator =
#ifdef _WIN32
        '\\';
#else
        '/';
#endif
    std::string path = std::string(".") + kPathSeparator + "util" + kPathSeparator + "osu_beatmaps_attributes" + kPathSeparator + std::to_string(beatmapID);
    switch (mode) {
        case EGamemode::Osu: {
            path += "_osu";
            break;
        }
        case EGamemode::Taiko: {
            path += "_taiko";
            break;
        }
        case EGamemode::Catch: {
            path += "_catch";
            break;
        }
        case EGamemode::Mania: {
            path += "_mania";
            break;
        }
    }
    path += ".osup";
    Beatmap beatmap(beatmapID);
    std::ifstream input(path);
    std::string line;
    std::vector<Beatmap::EDifficultyAttributeType> _difficultyAttributes(16, static_cast<Beatmap::EDifficultyAttributeType>(8));
    _difficultyAttributes[1] = Beatmap::DifficultyAttributeFromName("Aim");
    _difficultyAttributes[3] = Beatmap::DifficultyAttributeFromName("Speed");
    _difficultyAttributes[5] = Beatmap::DifficultyAttributeFromName("OD");
    _difficultyAttributes[7] = Beatmap::DifficultyAttributeFromName("AR");
    _difficultyAttributes[9] = Beatmap::DifficultyAttributeFromName("Max combo");
    _difficultyAttributes[11] = Beatmap::DifficultyAttributeFromName("Strain");
    _difficultyAttributes[13] = Beatmap::DifficultyAttributeFromName("Hit window 300");
    _difficultyAttributes[15] = Beatmap::DifficultyAttributeFromName("Score multiplier");
    beatmap.SetRankedStatus(static_cast<Beatmap::ERankedStatus>(1));
    beatmap.SetScoreVersion(static_cast<Beatmap::EScoreVersion>(1));
    beatmap.SetNumHitCircles(numHitCicles);
    beatmap.SetNumSpinners(numSpinners);
    while (std::getline(input, line)) {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::replace(line.begin(), line.end(), ',', '.');
        int mods;
        int attr;
        float val;
        std::stringstream ss;
        ss << line;
        ss >> mods;
        ss >> attr;
        ss >> val;
        ss.clear();
        ss.str();
        
        beatmap.SetDifficultyAttribute(static_cast<EMods>(mods), _difficultyAttributes[(s32)attr], val);
    }
    f32 pprec;
    switch (mode) {
        case EGamemode::Osu: {
            OsuScore tscore = OsuScore{
                0,
                mode,
                0,
                beatmapID,
                score,
                maxcombo,
                Num300,
                Num100,
                Num50,
                NumMiss,
                NumGeki,
                NumKatu,
                mods,
                beatmap
            };
            pprec = tscore.TotalValue();
            break;
        }
        case EGamemode::Taiko: {
            TaikoScore tscore = TaikoScore{
                0,
                mode,
                0,
                beatmapID,
                score,
                maxcombo,
                Num300,
                Num100,
                Num50,
                NumMiss,
                NumGeki,
                NumKatu,
                mods,
                beatmap
            };
            pprec = tscore.TotalValue();
            break;
        }
        case EGamemode::Catch: {
            CatchScore tscore = CatchScore{
                0,
                mode,
                0,
                beatmapID,
                score,
                maxcombo,
                Num300,
                Num100,
                Num50,
                NumMiss,
                NumGeki,
                NumKatu,
                mods,
                beatmap
            };
            pprec = tscore.TotalValue();
            break;
        }
        case EGamemode::Mania: {
            ManiaScore tscore = ManiaScore{
                0,
                mode,
                0,
                beatmapID,
                score,
                maxcombo,
                Num300,
                Num100,
                Num50,
                NumMiss,
                NumGeki,
                NumKatu,
                mods,
                beatmap
            };
            pprec = tscore.TotalValue();
            break;
        }
    }
    info.GetReturnValue().Set(Number::New(isolate, pprec));
}

NAN_MODULE_INIT(Init) {
    Nan::Export(target, "calculatePP", calculatePP);
}

NODE_MODULE(osu_performance, Init);