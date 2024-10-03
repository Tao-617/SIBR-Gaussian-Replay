// Software Name : SIBR_core
// SPDX-FileCopyrightText: Copyright (c) 2023 Orange
// SPDX-License-Identifier: Apache 2.0
//
// This software is distributed under the Apache 2.0 License;
// see the LICENSE file for more details.
//
// Author: Cédric CHEDALEUX <cedric.chedaleux@orange.com> et al.

#include <core/openxr/SwapchainImageRenderTarget.hpp>

namespace sibr
{

    SwapchainImageRenderTarget::SwapchainImageRenderTarget(uint32_t texture, uint w, uint h) : m_texture(texture),
                                                                                               m_W(w),
                                                                                               m_H(h)
    {
        // Allocate a Framebuffer
        glGenFramebuffers(1, &m_fbo);

        // Associate Framebuffer to Swapchain Image texture
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
        unbind();
    }

    SwapchainImageRenderTarget::~SwapchainImageRenderTarget(void)
    {
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
    }

    GLuint SwapchainImageRenderTarget::texture(uint) const
    {
        return m_texture;
    }

    GLuint SwapchainImageRenderTarget::handle(uint) const
    {
        return m_texture;
    }

    void SwapchainImageRenderTarget::bind(void)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    }

    void SwapchainImageRenderTarget::unbind(void)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void SwapchainImageRenderTarget::clear(void)
    {
        bind();
        glClearColor(0.f, 0, 0, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        unbind();
    }

    uint SwapchainImageRenderTarget::w(void) const
    {
        return m_W;
    }

    uint SwapchainImageRenderTarget::h(void) const
    {
        return m_H;
    }

    GLuint SwapchainImageRenderTarget::fbo(void) const
    {
        return m_fbo;
    }

} /*namespace sibr*/