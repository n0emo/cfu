#pragma once

#include "entt/resource/cache.hpp"
#include "raylib.h"
namespace cfu::res {

namespace music {
    // TODO: RES_MUSIC_ID_LIST
    #define RES_MUSIC_ID_LIST\
    CFU_X(xd_music, "xd.mp3")                                                                           \

    enum MusicId {
        #define CFU_X(name, ...) name,
        RES_MUSIC_ID_LIST
        #undef CFU_X
    };

}
struct CfuMusic{
   Music music {};

   CfuMusic(std::string_view path);
   CfuMusic(CfuMusic&& other) noexcept;
   auto operator=(CfuMusic&& other) noexcept -> CfuMusic&;
   ~CfuMusic();

   CfuMusic(const CfuMusic&) = delete;
   auto operator=(const CfuMusic&) -> CfuMusic& = delete;

   operator Music();
};

using MusicCache = entt::resource_cache<CfuMusic>;

namespace sounds {
    #define RES_SOUND_ID_LIST \
    CFU_X(xd_sound, "xd.mp3")                                                                           \

    enum SoundId{
        #define CFU_X(name, ...) name,
        RES_SOUND_ID_LIST
        #undef CFU_X
    };
    // TODO: RES_SOUND_ID_LIST
}

struct CfuSound{
    Sound sound {};

    CfuSound(std::string_view path);
    CfuSound(CfuSound&& other) noexcept;
    auto operator=(CfuSound&& other) noexcept -> CfuSound&;
    ~CfuSound();

    CfuSound(const CfuSound&) = delete;
    auto operator=(const CfuSound&) -> CfuSound& = delete;

    operator Sound();
};

using SoundCache = entt::resource_cache<CfuSound>;

} // namespace cfu::res
