/* androidrobot_head.pov version 6.0-beta.1
 * Persistence of Vision Raytracer scene description file
 * POV-Ray Object Collection demo
 *
 * Demo of the head of Google's Android[TM] mascot.
 *
 * Android is a trademark of Google LLC.  The Android robot is reproduced or
 * modified from work created and shared by Google and used according to terms
 * described in the Creative Commons 3.0 Attribution License.
 * See https://developer.android.com/distribute/marketing-tools/ and
 * https://creativecommons.org/licenses/by/3.0/ for more information.
 *
 * Copyright (C) 2020, 2025 Richard Callwood III.  Some rights reserved.
 * This file is licensed under the terms of the GNU-LGPL.
 *
 * This library is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  Please
 * visit https://www.gnu.org/licenses/lgpl-3.0.html for the text
 * of the GNU Lesser General Public License version 3.
 *
 * Vers.  Date         Comments                                           Author
 * -----  ----         --------                                           ------
 * 5.0    2020-Sep-19  Created                                             R.C.
 * 6.0    2021-Jan-11  The eyes are remodeled for the eccentricity of the  R.C.
 *                     2023 model's orbits.
 *                     The license is upgraded to LGPL 3.
 */
// +W280 +H210 +A +AM2 +R4
#version max (3.5, min (3.8, version));

#ifndef (Rad) #declare Rad = yes; #end // Use radiosity?

global_settings
{ assumed_gamma 1
  max_trace_level 50 // There's little visual difference over 50.
  #if (Rad)
    radiosity
    { count 100
      error_bound 0.5
      pretrace_end 0.01
      recursion_limit 2
    }
  #end
  photons { spacing 0.002 autostop 0 }
}

#include "consts.inc" // for glass property
#include "androidrobot.inc"

camera
{ location <2.25, 0.32, 0.3>
  look_at <0, 0.27, 0>
  right 4/3 * x
  angle 30
}

light_source
{ <1, 1, -0.7> * 1000, rgb 1.5
  parallel point_at 0
  area_light x * 160, y * 160, 17, 17
  circular orient adaptive 1 jitter
}

#default { finish { diffuse 0.75 ambient (Rad? 0: 0.1) } }

sky_sphere
{ pigment
  { function { pow (1 - y, 3) }
    color_map { [0 rgb 0.1] [1 rgb 0.6] }
  }
}

plane
{ y, 0
  texture { pigment { rgb 1 } }
  texture
  { pigment { rgbf 1 }
    finish { reflection { 1 fresnel } conserve_energy }
  }
  interior { ior 1.5 }
}

//============================== THE ROBOT HEAD ================================

#declare v_Eye = AndroidRobot_Eye_Radii_v();
#declare UserDefinedEye = sphere
{ 0, 1
  scale <0.5 * v_Eye.z, v_Eye.y, v_Eye.z>
  rotate v_Eye * x
  pigment { rgbf 1 }
  finish
  { reflection { 0 1 fresnel } conserve_energy
    specular 125 roughness 0.001
  }
  interior { ior Crown_Glass_Ior }
  photons { target collect off reflection on refraction on }
  translate AndroidRobot_Eye_v() - <0.75 * v_Eye.z, 0, 0>
}

union
{ AndroidRobot_Make_head (no)
  object { UserDefinedEye }
  object { UserDefinedEye scale <1, 1, -1> }
  pigment { ANDROIDROBOT_C_COLOR }
  translate -0.6 * y
}

// end of androidrobot_head.pov
