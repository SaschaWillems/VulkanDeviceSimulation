set "fp=%~dp0VkLayer_device_simulation.json"
reg add "HKLM\SOFTWARE\Khronos\Vulkan\ExplicitLayers" /v %fp% /t REG_DWORD /d 0