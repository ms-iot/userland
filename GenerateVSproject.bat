@REM
@REM Copyright (c) 2015, Microsoft Corporation. All rights reserved.
@REM
@REM This program and the accompanying materials
@REM are licensed and made available under the terms and conditions of the BSD License
@REM which accompanies this distribution.  The full text of the license may be found at
@REM http://opensource.org/licenses/bsd-license.php
@REM
@REM THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
@REM WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
@REM
@echo off
pushd %~dp0

set USERLAND_ROOT=%~dp0
set USERLAND_BUILD_DIR=%~dp0\build_win32

:: Create build directory
if not exist %USERLAND_BUILD_DIR% md %USERLAND_BUILD_DIR%

cd %USERLAND_BUILD_DIR%

cmake cmake -G "Visual Studio 14 2015 ARM" %USERLAND_ROOT%

popd