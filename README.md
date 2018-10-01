Userland - Windows 10 IoT Core
==============

This repository contains the source code for the ARM side libraries used on
Raspberry Pi ported to Windows IoT Core. This repository originated from
https://github.com/raspberrypi/userland and provides various interface
(EGL, mmal, GLESv2, vcos) on ARM side. Only a subset of interface has been
ported to Windows IoT Core. This repository is made available so user can
access Raspberry Pi feature that is expose through VCHIQ driver. VCHIQ driver
is available for reference [here](https://github.com/ms-iot/bsp).

The original userland repository uses CMAKE a cross platform build tool that is
compiler independent. The following are tools required to compile on Windows
IoT CORE.

## Requirement

Latest Microsoft Visual Studio
  (https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx)

Latest version of Windows CMAKE
  (https://cmake.org/download/.)

## Compilation Steps

1) Run "GenerateVSproject.bat" batch file. This will generate all project and
   solution in the "build_win32" folder.

2) Go to "build_win32" folder and open vmcs_host_apps.sln solution file.

3) There are 2 options to build all project. (1) Build the solution or
   (2) build the ALL_BUILD project.
   
 
## Notes
 
 Not all components are ported to Windows IoT Core, TODO comments can be found
 in various CMAKELists.txt file documenting what is component is omitted.
 
 There are substantial warnings during compilation that are not fixed to minimize
 code difference from the original repository.
 
 The OS abstraction layer (VCOS) is not complete for Windows, only the minimum required
 interface is supported. 
 
 For more information about Windows 10 IoT Core, see our online documentation [here](http://windowsondevices.com)

 This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
