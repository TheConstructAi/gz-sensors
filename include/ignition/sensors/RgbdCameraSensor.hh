/*
 * Copyright (C) 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef IGNITION_SENSORS_RGBDCAMERASENSOR_HH_
#define IGNITION_SENSORS_RGBDCAMERASENSOR_HH_

#include <memory>
#include <cstdint>
#include <mutex>
#include <string>

#include <sdf/Sensor.hh>

#include <ignition/msgs/image.pb.h>

#include <ignition/sensors/Export.hh>
#include <ignition/sensors/Sensor.hh>
#include <ignition/sensors/RenderingSensor.hh>
#include <ignition/transport.hh>


#ifndef _WIN32
#  define RgbdCameraSensor_EXPORTS_API
#else
#  if (defined(RgbdCameraSensor_EXPORTS))
#    define RgbdCameraSensor_EXPORTS_API __declspec(dllexport)
#  else
#    define RgbdCameraSensor_EXPORTS_API __declspec(dllimport)
#  endif
#endif

namespace ignition
{
  namespace sensors
  {
    // Inline bracket to help doxygen filtering.
    inline namespace IGNITION_SENSORS_VERSION_NAMESPACE {
    // forward declarations
    class RgbdCameraSensorPrivate;

    /// \brief Depth camera sensor class.
    ///
    /// This class creates depth image from an ignition rendering scene.
    /// The scene  must be created in advance and given to Manager::Init().
    /// It offers both an ignition-transport interface and a direct C++ API
    /// to access the image data. The API works by setting a callback to be
    /// called with image data.
    class RgbdCameraSensor_EXPORTS_API RgbdCameraSensor : public RenderingSensor
    {
      /// \brief constructor
      public: RgbdCameraSensor();

      /// \brief destructor
      public: virtual ~RgbdCameraSensor();

      /// \brief Load the sensor based on data from an sdf::Sensor object.
      /// \param[in] _sdf SDF Sensor parameters.
      /// \return true if loading was successful
      public: virtual bool Load(const sdf::Sensor &_sdf) override;

      /// \brief Initialize values in the sensor
      /// \return True on success
      public: virtual bool Init() override;

      /// \brief Force the sensor to generate data
      /// \param[in] _now The current time
      /// \return true if the update was successfull
      public: virtual bool Update(const common::Time &_now) override;

      /// \brief Get a pointer to the depth camera
      /// \return Pointer to the depth camera
      public: rendering::DepthCameraPtr DepthCamera();

      /// \brief Get a pointer to the 2d image camera
      /// \return Pointer to the 2d image camera.
      public: rendering::CameraPtr RenderingCamera();

      /// \brief Set the rendering scene.
      /// \param[in] _scene Pointer to the scene
      public: virtual void SetScene(
                  ignition::rendering::ScenePtr _scene) override;

      /// \brief Get image width.
      /// \return width of the image
      public: unsigned int ImageWidth() const;

      /// \brief Get image height.
      /// \return height of the image
      public: unsigned int ImageHeight() const;

      /// \brief Get image width.
      /// \return width of the image
      public: virtual double FarClip() const;

      /// \brief Get image height.
      /// \return height of the image
      public: virtual double NearClip() const;

      /// \brief Data pointer for private data
      /// \internal
      private: std::unique_ptr<RgbdCameraSensorPrivate> dataPtr;
    };
    }
  }
}

#endif