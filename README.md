# SDL_TestApp
A windows testing app on SDL apis.  
- Tested with SDL 2.30.8 on 10/25/2024.  

**How to run?**
1. download the latest stable SDL release like SDL2-devel-2.30.8-VC.zip (from https://github.com/libsdl-org/SDL/releases)
2. VS project configurations:
- add extra include path: D:\SDKs\SDL2-devel-2.30.8-VC\SDL2-2.30.8\include
- add extra lib path: D:\SDKs\SDL2-devel-2.30.8-VC\SDL2-2.30.8\lib\x64
- linked to SDL2.lib
3. copy SDL2.dll to App Build folder


**How to migrate applications from SDL 2.0 to SDL 3.0.**  
https://github.com/libsdl-org/SDL/blob/main/docs/README-migration.md

**NOTE**  
1. SDL_CreateWindowFrom is removed from SDL3  
2. SDL 3: it crashes when calling SDL_CreateWindow in a MFC application.