// Software Name : SIBR_core
// SPDX-FileCopyrightText: Copyright (c) 2023 Orange
// SPDX-License-Identifier: Apache 2.0
//
// This software is distributed under the Apache 2.0 License;
// see the LICENSE file for more details.
//
// Author: Cédric CHEDALEUX <cedric.chedaleux@orange.com> et al.

#pragma once

# include <core/graphics/Config.hpp>


# ifdef SIBR_OS_WINDOWS
#  ifdef SIBR_STATIC_OPENXR_DEFINE
#    define SIBR_OPENXR_EXPORT
#    define SIBR_NO_OPENXR_EXPORT
#  else
#    ifndef SIBR_OPENXR_EXPORT
#      ifdef SIBR_OPENXR_EXPORTS
          /* We are building this library */
#        define SIBR_OPENXR_EXPORT __declspec(dllexport)
#      else
          /* We are using this library */
#        define SIBR_OPENXR_EXPORT __declspec(dllimport)
#      endif
#    endif
#  endif
# else
#  define SIBR_OPENXR_EXPORT
# endif