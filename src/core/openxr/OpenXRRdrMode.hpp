// Software Name : SIBR_core
// SPDX-FileCopyrightText: Copyright (c) 2023 Orange
// SPDX-License-Identifier: Apache 2.0
//
// This software is distributed under the Apache 2.0 License;
// see the LICENSE file for more details.
//
// Author: Cédric CHEDALEUX <cedric.chedaleux@orange.com> et al.

#include <core/view/RenderingMode.hpp>
#include <core/graphics/Window.hpp>
#include <core/openxr/Config.hpp>
#include <core/openxr/OpenXRHMD.hpp>
#include <core/openxr/SwapchainImageRenderTarget.hpp>

#include <vector>
#include <map>

namespace sibr
{
    struct ViewData {
        Eigen::Vector4f fov; // FOV: 4 float values
        Eigen::Vector3f position; // Position: 3 float values
        Eigen::Quaternionf quaternion; // Quaternion: 4 float values
    };

    /** OpenXRRdrMode renders a stereoscopic view to an Headset-Mouted display OpenXR device.
    *   It also renders both views to a SIBR view.
    *   \ingroup sibr_openxr
    */
    class SIBR_OPENXR_EXPORT OpenXRRdrMode : public IRenderingMode
    {
    public:
        /// Constructor.
        explicit OpenXRRdrMode(sibr::Window &window);
        ~OpenXRRdrMode();
        

        //OutPut File
        std::ofstream outFile;
        //Input File
        std::ifstream inFile;

        //Frame Index
        std::int16_t FrameIndex ;
        
        int PlayMode = 1; //0 is saving Tracks; 1 is Stop Saving(normal play); 2 is Input Replay

        void loadViewData( int viewIndex, ViewData& data);

        /** Perform rendering of a view.
         *\param view the view to render
         *\param eye the current camera
         *\param viewport the current viewport
         *\param optDest an optional destination RT
         */
        void render(ViewBase &view, const sibr::Camera &eye, const sibr::Viewport &viewport, IRenderTarget *optDest = nullptr);

        /** Get the current rendered image as a CPU image
         *\param current_img will contain the content of the RT */
        void destRT2img(sibr::ImageRGB &current_img)
        {
            return;
        }

        /** \return the left eye RT. */
        virtual const std::unique_ptr<RenderTargetRGB> &lRT() { return _leftRT; }
        /** \return the right eye RT. */
        virtual const std::unique_ptr<RenderTargetRGB> &rRT() { return _rightRT; }

        /** GUI for configuring OpenXR rendering */
        void onGui();
        

    private:
        std::unique_ptr<OpenXRHMD> m_openxrHmd;                  ///< OpenXR interface
        sibr::GLShader m_quadShader;                             ///< Shader for drawing left/right eye in desktop window
        std::map<int, SwapchainImageRenderTarget::Ptr> m_RTPool; ///< Pool for RenderTarget used to extract textures for each view
        int m_vrExperience = 0;                                  ///< 0: free world standing experience, 1: seated experience
        bool m_flipY = true;                                     ///< Rotate camera to render scenes which are y-inverted
        bool m_appFocused = false;                               ///< Application is visible and focused in the headset)
        int m_downscaleResolution = 1.0f;                        ///< Downscale rendering resolution to improve performance
        RenderTarget::UPtr _leftRT, _rightRT;                    ///< Only used to implement abstract method lRT andrRT!

        SwapchainImageRenderTarget::Ptr getRenderTarget(uint32_t texture, uint w, uint h);
    };

} /*namespace sibr*/