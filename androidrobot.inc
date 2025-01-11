/* androidrobot.inc version 6.0-beta.1
 * Persistence of Vision Raytracer include file
 * POV-Ray Object Collection
 *
 * A 3-D model of Google's Android[TM] mascot.
 *
 * Android is a trademark of Google LLC.  The Android robot is reproduced or
 * modified from work created and shared by Google and used according to terms
 * described in the Creative Commons 3.0 Attribution License.
 * See https://developer.android.com/distribute/marketing-tools/ and
 * https://creativecommons.org/licenses/by/3.0/ for more information.
 *
 * See also https://commons.wikimedia.org/wiki/File:Android_Robot_POV-Ray.png
 *
 * Portions of the SDL source code are copyright (C) 2009 Karl Ostmo.  Some
 * rights reserved.  Portions of the SDL source code are copyright (C) 2011 -
 * 2025 Richard Callwood III.  Some rights reserved.
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
 * Original code by Karl Ostmo:
 *
 * Vers.  Date         Comments
 * -----  ----         --------
 * 1.0    2009-Oct-30  The original code is written as droid.pov.
 *
 * Modifications by Richard Callwood III:
 *
 * Vers.  Date         Comments
 * -----  ----         --------
 * 2.0    2011-Jul-23  The code is separated into include and demo files.
 *                     The code is made fully namespace compliant.
 *                     The pigment is removed from the robot and the
 *                     official color is declared separately.
 *                     The robot can be posed.
 *                     A #version is added, either 3.5 or 3.7.
 *
 * 2.1    2012-Jun-26  Non-gamma-adjusted official color is added.
 * 2.1a   2012-Jun-28  A correction is made to Google license statement.
 *
 * 2.2    2014-Oct-05  The arms are moved away from the body, as they appear in
 *                     the 2D logo.
 *                     A backwards compatibility switch is added.
 *                     The Google license statement is upgraded.
 *
 * 3.0    2015-Apr-25  The robot is remodeled based on an SVG source.
 *                     Tools are added to facilitate user modeling of eyes.
 * 3.0a   2015-Apr-27  A correction is made to the user manual.
 *
 * 4.0    2018-Sep-23  The short prefix is reinstated.
 *                     The official color is updated.
 *
 * 4.0.1  2019-Mar-22  View_POV_Include_Stack is utilized.
 *
 * 5.0    2020-Sep-19  The official color is updated to its 2019 value.
 *                     The #version preserved between 3.5 and 3.8.
 *                     The pre-3.7 nonlinear color adjustment is changed from a
 *                     power function to sRGB.
 *                     New body proportions are added, extrapolated from the
 *                     2019 head logo.  Proportions of previous versions remain
 *                     selectable.
 *                     The head is available standalone.
 *
 * 6.0    20??-???-??  "Magic numbers" are centralized in an array.
 *                     New body proportions are added, extrapolated from the
 *                     2023 head logo.  Proportions of previous versions remain
 *                     selectable.
 *                     The nonlinear color adjustment is reverted to a power
 *                     gamma for #version < 3.7.  (See "Stock colors and
 *                     assumed_gamma 1 in POV-Ray 3.6" (2020-Oct-12) in
 *                     povray.binaries.images.)
 *                     A gamma can be set for #version < 3.7.
 *                     Additional identifier synonyms are added, including
 *                     international spellings.
 *                     The license is upgraded to LGPL 3.
 *
 * Implementation note: due to POV-Ray namespace scope leakage, local variables
 * and function parameters (other than x, y, and z) *must* be prefixed.
 */
#ifndef (AndroidRobot_Inc_Temp) #declare AndroidRobot_Inc_Temp = version;

//Take advantage of POV-Ray 3.7+ feature if and only if available:
#version max (3.5, min (3.8, version));

#ifdef (View_POV_Include_Stack)
  #debug concat
  ( "#include \"androidrobot.inc\" //version 6.0-beta.1\n  #version ",
    str(version,0,1), ";\n"
  )
#end

#ifndef (AndroidRobot_Version) #declare AndroidRobot_Version = 6.0; #end
#ifndef (AndroidRobot_Gamma) #declare AndroidRobot_Gamma = 1.0; #end

//============================= PUBLIC CONSTANTS ===============================

#declare ANDROIDROBOT_HEIGHT = 1.65;
#declare ANDROIDROBOT_V_BASE = <0, -0.55, 0>;

//======================= INTERNAL (PRIVATE) FEATURES ==========================
// These features are not intended for direct use by the end user.

//---------------------- Ostmo model -----------------------

#declare DROID__ANTENNAE_ANGLE = 30;
#declare DROID__ANTENNAE_LENGTH = 0.2;
#declare DROID__EYE_HEIGHT = 0.8;

#macro AndroidRobot__V2
( Use_merge, x_Head, x_Left_arm, x_Right_arm, x_Left_leg, x_Right_leg
)
  #local DROID_ZARM = (AndroidRobot_Version < 2.2? 0.6: 0.65);

  #local Droid_Arm = #if (Use_merge) merge #else union #end
  { sphere { <0, 0.5, 0>, 0.1 }
    cylinder { <0, 0.5, 0>, <0, 0.1, 0>, 0.1 }
    sphere { <0, 0.1, 0>, 0.1 }
  }

  #local Droid_Leg = #if (Use_merge) merge #else union #end
  { cylinder
    { <0, 0.5, 0>, <0, -0.2, 0>, 0.1
      translate <0, -0.25, 0>
    }
    sphere
    { <0, -0.2, 0>, 0.1
      translate <0, -0.25, 0>
    }
  }

  #if (Use_merge) merge #else union #end
  {
   //Torso
    cylinder { <0, 0.6, 0>, <0, -0.1, 0>, 0.5 }
    cylinder { <0, 0.1, 0>, <0, -0.2, 0>, 0.4 }
    torus { 0.4, 0.1 translate -0.1 * y }

   //Head
    object
    { AndroidRobot__Head_v2 (Use_merge)
      AndroidRobot_Head_x (x_Head)
    }

    object
    { Droid_Arm
      translate -0.5 * y //move to origin
      transform { x_Right_arm }
      translate 0.5 * y //move back from origin
      translate z*(-DROID_ZARM)
    }

    object
    { Droid_Arm
      translate -0.5 * y //move to origin
      transform { x_Left_arm }
      translate 0.5 * y //move back from origin
      translate z*(DROID_ZARM)
    }

    object
    { Droid_Leg
      translate 0.1 * y //move to origin
      transform { x_Left_leg }
      translate -0.1 * y //move back from origin
      translate z*(.25)
    }

    object
    { Droid_Leg
      translate 0.1 * y //move to origin
      transform { x_Right_leg }
      translate -0.1 * y //move back from origin
      translate z*(-.25)
    }

  }
#end

//--------------------------------------

#macro AndroidRobot__Head_v2 (Use_merge)

  #local Droid_Antenna = cylinder
  { <0, DROID__ANTENNAE_LENGTH, 0>, <0, 0, 0>, 0.02
  }

  #local Droid_EyeSocket = cylinder
  { <0, 0.5, 0>, <0, 0, 0>, 0.05
    rotate z*(-90)
    translate <0, DROID__EYE_HEIGHT, 0>
  }

  #if (Use_merge) merge #else union #end
  { difference
    { AndroidRobot_Head (0)
      object { Droid_EyeSocket translate z*(-.25) }
      object { Droid_EyeSocket translate z*(.25) }
    }
    object
    { Droid_Antenna
      rotate x*(-DROID__ANTENNAE_ANGLE)
      translate <0, 1, -0.25>
    }
    object
    { Droid_Antenna
      rotate x*(DROID__ANTENNAE_ANGLE)
      translate <0, 1, 0.25>
    }
  }
#end

//-------------------- Callwood model ----------------------

/* The messy values in this section were derived from the file
 * https://commons.wikimedia.org/wiki/File:Android_robot.svg, and transformed
 * such that the new version of the robot has the same size and position as the
 * Ostmo model.
 *
 * The Android Web page from which the Wikimedia image was taken now redirects
 * to a page (see the Google attribution in the header comment) with various SVG
 * files over time that have only the head defined.  The proportions of these
 * new SVG files have been extrapolated for AndroidRobot versions 5.0 and 6.0,
 * respectively. --RC
 */
// Per Dijkstra, keep all the messy values in a data structure:
#declare droid__Dimensions = array [28][3]
{// torso and limbs
  { 0.483731, 0.485546, 0.487218, }, // torso radius
  { 0.116946, 0.117385, 0.117789, }, // butt minor radius
  { 0.108441, 0.108848, 0.109223, }, // limb radius
  { 0.632571, 0.634945, 0.637131, }, // shoulder z
  { 0.180735, 0.181413, 0.182038, }, // hip z
  { 0.615738, 0.620112, 0.624142, }, // torso top
  {-0.202352,-0.201047,-0.199845, }, // torso bottom
  { 0.525902, 0.529939, 0.533659, }, // shoulder y center of curvature
  { 0.010277, 0.012379, 0.014316, }, // hip y center of curvature
  { 0.451836, 0.453532, 0.455094, }, // limb length excluding end radii
 // antennae
  { 29,       30,       30.08,    }, // antenna angle
  { 0.015416, 0.016810, 0.044792, }, // antenna side radius
  { 0.015416, 0.016810, 0.044809, }, // antenna end radius
  { 0.108972, 0.304231, 0.299381, }, // antenna z top center of curvature
  { 0.871424, 0,        0,        }, // antenna y origin (v3)
  { 0.422600, 1.188860, 1.185402, }, // antenna y top center of curvature
  { 0.034552, 0,        0,        }, // bottom of unrotated antenna (v3)
  { 0,        0.18,     0.21,     }, // antenna length (v4 and later)
 // eyes
  { 0.871424, 0.837335, 0.840155, }, // eye y
  { 0.223260, 0.223475, 0.224056, }, // eye z
  { 0.040399, 0.040399, 0.052345, }, // eye y radius
  { 0.040399, 0.040399, 0.042417, }, // eye z radius
  { 0,        0,       -33.60,    }, // eye rotation
 // head
  { 0.483731, 0.487201, 0.490235, }, // head side radius
  { 0.446521, 0.481096, 0.491788, }, // head y radius
  { 0.653479, 0.618904, 0.608212, }, // head y center of curvature
  { 0.654011, 0.658529, 0.662691, }, // head bottom
  { 0.634874, 0.639320, 0.643417, }, // head y center of motion
}
// Select index into the above array:
// Argument: x - AndroidRobot version
#declare Droid__fn_Index = function (x)
{ select (x - 5, 0, select (x - 6, 1, 2))
}

#macro AndroidRobot__V3
( Use_merge, x_Head, x_Left_arm, x_Right_arm, x_Left_leg, x_Right_leg
)
  #local droid_Ix = Droid__fn_Index (AndroidRobot_Version);

  #local DROID_RTORSO = droid__Dimensions [0][droid_Ix];
  #local DROID_RBUTT = droid__Dimensions [1][droid_Ix];
  #local DROID_RLIMB = droid__Dimensions [2][droid_Ix];
  #local DROID_ZSHOULDER = droid__Dimensions [3][droid_Ix];
  #local DROID_ZHIP = droid__Dimensions [4][droid_Ix];
  #local DROID_Y2TORSO = droid__Dimensions [5][droid_Ix];
  #local DROID_Y1TORSO = droid__Dimensions [6][droid_Ix];
  #local DROID_YSHOULDER = droid__Dimensions [7][droid_Ix];
  #local DROID_Y2LEG = droid__Dimensions [8][droid_Ix];
  #local DROID_HLIMB = droid__Dimensions [9][droid_Ix];

  #local DROID_ZBUTT = DROID_RTORSO - DROID_RBUTT;  // center of curvature
  #local DROID_YBUTT = DROID_Y1TORSO + DROID_RBUTT; // center of curvature
  #local DROID_YHIPF = DROID_Y1TORSO + DROID_RLIMB; // leg final translation
  #local DROID_YHIP0 = DROID_Y2LEG - DROID_YHIPF;   // leg translation to origin

  #local Droid_Limb = #if (Use_merge) merge #else union #end
  { sphere { 0, DROID_RLIMB }
    cylinder { 0, -DROID_HLIMB * y, DROID_RLIMB }
    sphere { -DROID_HLIMB * y, DROID_RLIMB }
  }

  #if (Use_merge) merge #else union #end
  {
   // torso
    cylinder { DROID_Y2TORSO * y, DROID_YBUTT * y, DROID_RTORSO }
    cylinder { (DROID_YBUTT + 0.001) * y, DROID_Y1TORSO * y, DROID_ZBUTT }
    torus { DROID_ZBUTT, DROID_RBUTT translate DROID_YBUTT * y }

   // head
    object
    { AndroidRobot__Head_v3 (Use_merge)
      AndroidRobot_Head_x (x_Head)
    }

    object
    { Droid_Limb
      transform { x_Right_arm }
      translate <0, DROID_YSHOULDER, -DROID_ZSHOULDER>
    }
    object
    { Droid_Limb
      transform { x_Left_arm }
      translate <0, DROID_YSHOULDER, DROID_ZSHOULDER>
    }
    object
    { Droid_Limb
      translate DROID_YHIP0 * y
      transform { x_Right_leg }
      translate <0, DROID_YHIPF, -DROID_ZHIP>
    }
    object
    { Droid_Limb
      translate DROID_YHIP0 * y
      transform { x_Left_leg }
      translate <0, DROID_YHIPF, DROID_ZHIP>
    }
  }
#end

//--------------------------------------

#macro AndroidRobot__Head_v3 (Use_merge)
  #local droid_Ix = Droid__fn_Index (AndroidRobot_Version);
  #local DROID_AANTENNA = droid__Dimensions [10][droid_Ix];
  #local DROID_RANTENNA = droid__Dimensions [11][droid_Ix];
  #local DROID_RYANTENNA = droid__Dimensions [12][droid_Ix];
  #local DROID_ZANTENNA = droid__Dimensions [13][droid_Ix];
  #local DROID_YORIGIN = droid__Dimensions [14][droid_Ix];
  #local DROID_Y2ANTENNA = droid__Dimensions [15][droid_Ix];
  #local DROID_Y1ANTENNA = droid__Dimensions [16][droid_Ix];
  #local DROID_HANTENNA = droid__Dimensions [17][droid_Ix];

  #local droid_v_Eye = AndroidRobot_Eye_Radii_v();
  #local Droid_EyeSocket = cylinder
  { 0, x, 1
    scale <1, droid_v_Eye.y, droid_v_Eye.z>
    rotate droid_v_Eye * x
    translate AndroidRobot_Eye_v() * <0, 1, 1>
  }

  // Different algorithms are needed here because the older SVG
  // created a vertical antenna, then rotated it into place,
  // whereas later SVGs created the antennae in situ.
  #local Droid_Antenna = #if (Use_merge) merge #else union #end
  { #if (AndroidRobot_Version < 5.0)
      cylinder { DROID_Y1ANTENNA * y, DROID_Y2ANTENNA * y, DROID_RANTENNA }
      sphere { DROID_Y2ANTENNA * y, DROID_RANTENNA }
      translate DROID_ZANTENNA * z
      rotate DROID_AANTENNA * x
      translate DROID_YORIGIN * y
    #else
      sphere { 0, 1 scale <DROID_RANTENNA, DROID_RYANTENNA, DROID_RANTENNA> }
      cylinder { 0, -DROID_HANTENNA * y, DROID_RANTENNA }
      rotate DROID_AANTENNA * x
      translate <0, DROID_Y2ANTENNA, DROID_ZANTENNA>
    #end
  }

  #if (Use_merge) merge #else union #end
  { difference
    { object { AndroidRobot_Head (0) }
      object { Droid_EyeSocket }
      object { Droid_EyeSocket scale <1, 1, -1> }
    }
    object { Droid_Antenna }
    object { Droid_Antenna scale <1, 1, -1> }
  }
#end

//============================== PUBLIC MACROS =================================

#macro AndroidRobot_Eye_v()
  #local droid_Ix = Droid__fn_Index (AndroidRobot_Version);
  #local Droid_Test = AndroidRobot_Head (0)
  trace
  ( Droid_Test,
    ( AndroidRobot_Version < 3.0?
      <1, DROID__EYE_HEIGHT, 0.25>:
      <1, droid__Dimensions [18][droid_Ix], droid__Dimensions [19][droid_Ix]>
    ),
    -x
  )
#end

//--------------------------------------

#macro AndroidRobot_Eye_Radii_v()
  #local droid_Ix = Droid__fn_Index (AndroidRobot_Version);
  ( AndroidRobot_Version < 3.0?
    <0.05, 0.05, 0>:
    < droid__Dimensions [22][droid_Ix], // rotation
      droid__Dimensions [20][droid_Ix], // y radius
      droid__Dimensions [21][droid_Ix]  // z radius
    >
  )
#end

//--------------------------------------

#macro AndroidRobot_Head (Outset)
  #if (AndroidRobot_Version < 3.0)
    difference
    { sphere { <0, 0.6, 0>, 0.5 + Outset }
      plane { y, 0.65 - Outset }
    }
  #else
    #local droid_Ix = Droid__fn_Index (AndroidRobot_Version);
    #local DROID_RZHEAD = droid__Dimensions [23][droid_Ix];
    #local DROID_RYHEAD = droid__Dimensions [24][droid_Ix];
    #local DROID_YCHEAD = droid__Dimensions [25][droid_Ix];
    #local DROID_Y1HEAD = droid__Dimensions [26][droid_Ix];
    intersection
    { sphere
      { 0, 1
        scale <DROID_RZHEAD, DROID_RYHEAD, DROID_RZHEAD> + Outset
        translate DROID_YCHEAD * y
      }
      plane { -y, Outset - DROID_Y1HEAD }
    }
  #end
#end

//--------------------------------------

#macro AndroidRobot_Make_Head (Use_merge)
  #if (AndroidRobot_Version < 3.0)
    AndroidRobot__Head_v2 (Use_merge)
  #else
    AndroidRobot__Head_v3 (Use_merge)
  #end
#end

//--------------------------------------

#macro AndroidRobot_Head_x (x_Head)
  #local droid_Neck =
  ( AndroidRobot_Version < 3.0?
    0.625: droid__Dimensions [27] [Droid__fn_Index (AndroidRobot_Version)]
  );
  transform
  { translate -droid_Neck * y // Move center of neck to origin
    transform { x_Head }
    translate droid_Neck * y // Move back from origin
  }
#end

//--------------------------------------

#macro AndroidRobot_Posed
( Use_merge, x_Head, x_Left_arm, x_Right_arm, x_Left_leg, x_Right_leg
)
  #if (AndroidRobot_Version < 3.0)
    AndroidRobot__V2
    ( Use_merge, x_Head, x_Left_arm, x_Right_arm, x_Left_leg, x_Right_leg
    )
  #else
    AndroidRobot__V3
    ( Use_merge, x_Head, x_Left_arm, x_Right_arm, x_Left_leg, x_Right_leg
    )
  #end
#end

//--------------------------------------

#macro AndroidRobot (Use_merge)
  AndroidRobot_Posed
  ( Use_merge, transform{}, transform{}, transform{}, transform{}, transform{}
  )
#end

//--------------------------------------

#macro AndroidRobot_Set_Color (Version)
  #declare DROID_C_RAWCOLOR = rgb
  ( Version < 4?
    <164, 198, 57>:   // #A4C639
    ( Version < 5?
      <120, 194, 87>: // #78C257
      <61, 220, 132>  // #3DDC84
    )
  ) / 255;
  #if (version < 3.7)
    #declare DROID_C_COLOR = rgb
    < pow (DROID_C_RAWCOLOR.red, 2.2 / AndroidRobot_Gamma),
      pow (DROID_C_RAWCOLOR.green, 2.2 / AndroidRobot_Gamma),
      pow (DROID_C_RAWCOLOR.blue, 2.2 / AndroidRobot_Gamma)
    >;
  #else
    #declare DROID_C_COLOR = srgbft DROID_C_RAWCOLOR;
  #end
  #declare ANDROIDROBOT_C_RAWCOLOUR = DROID_C_RAWCOLOR;
  #declare ANDROIDROBOT_C_RAWCOLOR = DROID_C_RAWCOLOR;
  #declare DROID_C_RAWCOLOUR = DROID_C_RAWCOLOR;
  #declare ANDROIDROBOT_C_COLOR = DROID_C_COLOR;
  #declare ANDROIDROBOT_C_COLOR = DROID_C_COLOR;
  #declare DROID_C_COLOUR = DROID_C_COLOR;
#end

AndroidRobot_Set_Color (AndroidRobot_Version) // Initialize.

//---------------------- GRANDFATHERED -------------------------

#macro AndroidRobot_Eye_radius()
  #local droid_Ix = Droid__fn_Index (AndroidRobot_Version);
  ( AndroidRobot_Version < 3.0?
    0.05:
    sqrt (droid__Dimensions [20][droid_Ix] * droid__Dimensions [21][droid_Ix])
  )
#end

//================================= SYNONYMS ===================================

#declare DROID_HEIGHT = ANDROIDROBOT_HEIGHT;
#declare DROID_V_BASE = ANDROIDROBOT_V_BASE;
#macro Droid (Use_merge) AndroidRobot (Use_merge) #end
#macro Droid_Eye_v() AndroidRobot_Eye_v() #end
#macro Droid_Eye_Radii_v() AndroidRobot_Eye_Radii_v() #end
#macro Droid_Eye_radius() AndroidRobot_Eye_radius() #end
#macro Droid_Head (Outset) AndroidRobot_Head (Outset) #end
#macro Droid_Head_x (x_Head) AndroidRobot_Head_x (x_Head) #end
#macro Droid_Make_Head (Use_merge) AndroidRobot_Make_Head (Use_merge) #end
#macro Droid_Make_head (Use_merge) AndroidRobot_Make_Head (Use_merge) #end
#macro Droid_Posed
( Use_merge, x_Head, x_Left_arm, x_Right_arm, x_Left_leg, x_Right_leg
)
  AndroidRobot_Posed
  ( Use_merge, x_Head, x_Left_arm, x_Right_arm, x_Left_leg, x_Right_leg
  )
#end
#macro Droid_Set_Color (Version) AndroidRobot_Set_Color (Version) #end
#macro Droid_Set_color (Version) AndroidRobot_Set_Color (Version) #end
#macro Droid_Set_Colour (Version) AndroidRobot_Set_Color (Version) #end
#macro Droid_Set_colour (Version) AndroidRobot_Set_Color (Version) #end

#macro AndroidRobot_posed
( Use_merge, x_Head, x_Left_arm, x_Right_arm, x_Left_leg, x_Right_leg
)
  AndroidRobot_Posed
  ( Use_merge, x_Head, x_Left_arm, x_Right_arm, x_Left_leg, x_Right_leg
  )
#end
#macro AndroidRobot_Make_head (Use_merge) AndroidRobot_Make_Head (Use_merge) #end
#macro AndroidRobot_Set_color (Version) AndroidRobot_Set_Color (Version) #end
#macro AndroidRobot_Set_Colour (Version) AndroidRobot_Set_Color (Version) #end
#macro AndroidRobot_Set_colour (Version) AndroidRobot_Set_Color (Version) #end


//==============================================================================

#version AndroidRobot_Inc_Temp;
#end
// end of androidrobot.inc
