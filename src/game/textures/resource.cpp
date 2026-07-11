#include "./resource.hpp"

#include <format>
#include "raylib.h"

namespace cfu::res {

    CfuTexture::CfuTexture(std::string_view path) {
        auto final_path = std::format("assets/textures/{}", path);
        this-> texture = LoadTexture(final_path.c_str());
    }

    CfuTexture::CfuTexture(CfuTexture&& other) noexcept : texture(other.texture) {
        other.texture= {};
    }

    auto CfuTexture::operator=(CfuTexture&& other) noexcept -> CfuTexture& {
        this->texture= other.texture;
        other.texture= {};
        return *this;
    }

    CfuTexture::~CfuTexture() {
        if (IsTextureValid(this->texture)) UnloadTexture(this->texture);
    }

    CfuTexture::operator Texture2D() {
        return texture;
    }

} // namespace cfu::res
