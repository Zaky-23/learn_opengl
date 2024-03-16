#pragma once 

#include <concepts>
#include <cstdint>
#include <memory>
#include <string_view>

namespace core {
class Image {
friend class ImageBuilder;

private:
  Image(int32_t width, int32_t height, int32_t number_of_channels, void *data) : width_(width), height_(height), 
  number_of_channels_(number_of_channels), data_(nullptr) {};

private:
  int32_t width_;
  int32_t height_;
  int32_t number_of_channels_;
  std::shared_ptr<void> data_;
};

class ImageBuilder {
public:
  static
  ImageBuilder  Begin() { return ImageBuilder(); }
  ImageBuilder &WithDataFromFile(std::string_view path);
  ImageBuilder &WithDataFromMemroy(void *data);
  ImageBuilder &WithNumberOfChannels(int32_t number_of_desired_channels);
  Image         Finish();

private:
  ImageBuilder() : width_(0), height_(0), number_of_channels_(0), number_of_desired_channels_(0),
  data_(nullptr), flip_vertically_(false) {};

private:
  int32_t width_;
  int32_t height_;
  int32_t number_of_channels_;
  int32_t number_of_desired_channels_;
  void *data_;
  bool flip_vertically_;
};
}