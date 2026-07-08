#include "./resource.hpp"

#include <format>

#include "../raymath.hpp"

namespace cfu::res {

VoxelModel::VoxelModel(std::string_view path) {
    auto final_path = std::format("assets/vox/{}", path);
    this->model = LoadModel(final_path.c_str());
    this->bounding_box = GetModelBoundingBox(this->model);
    const auto x = (this->bounding_box.min.x - this->bounding_box.max.x) * 0.5f;
    const auto y = (this->bounding_box.min.y - this->bounding_box.max.y) * 0.5f;
    const auto z = (this->bounding_box.min.z - this->bounding_box.max.z) * 0.5f;
    this->model.transform = MatrixTranslate(x, y, z);
    this->path = final_path;
}

VoxelModel::VoxelModel(VoxelModel&& other) noexcept : model(other.model), path(other.path) {
    other.model = {};
    other.path = {};
}

auto VoxelModel::operator=(VoxelModel&& other) noexcept -> VoxelModel& {
    this->model = other.model;
    this->path = other.path;
    other.model = {};
    other.path = {};
    return *this;
}

VoxelModel::~VoxelModel() {
    if (IsModelValid(this->model)) UnloadModel(this->model);
}

VoxelModel::operator Model() {
    return model;
}

} // namespace cfu::res
