/*
* Vulkan Example using the LunarG device simulation layer
*
* Copyright (C) 2017 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include <assert.h>
#include <iostream>
#include <conio.h>

#include <vulkan/vulkan.h>

class VulkanTutorial {
public:
	VulkanTutorial() {
		VkInstance instance;

		struct PhysicalDevices {
			VkPhysicalDevice real;
			VkPhysicalDevice simulated;
		} physicalDevices;

		VkApplicationInfo applicationInfo{};
		applicationInfo.pApplicationName = "Vulkan Device Simulation Layer Example";
		applicationInfo.apiVersion = VK_API_VERSION_1_0;

		// Create instance withouth device simulation layer
		{
			VkInstanceCreateInfo instanceCreateInfo = {};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
			uint32_t deviceCount;
			// Get first device only
			vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
			assert(deviceCount > 0);
			deviceCount = 1;
			vkEnumeratePhysicalDevices(instance, &deviceCount, &physicalDevices.real);
			std::cout << "*** Actual device ***" << std::endl;
			displayDeviceInfo(physicalDevices.real);
			vkDestroyInstance(instance, nullptr);
		}

		// Create instance with device simulation layer enabled
		{
			VkInstanceCreateInfo instanceCreateInfo = {};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			// Enable the device simulation layer
			const char* layerName{ "VK_LAYER_LUNARG_device_simulation" };
			instanceCreateInfo.enabledLayerCount = 1;
			instanceCreateInfo.ppEnabledLayerNames = &layerName;
			vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
			uint32_t deviceCount;
			// Get physical device for the simulated device
			vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
			assert(deviceCount > 0);
			deviceCount = 1;
			vkEnumeratePhysicalDevices(instance, &deviceCount, &physicalDevices.simulated);
			std::cout << "*** Simulated device ***" << std::endl;
			displayDeviceInfo(physicalDevices.simulated);
			vkDestroyInstance(instance, nullptr);
		}
	}

	void displayDeviceInfo(VkPhysicalDevice device) {
		VkPhysicalDeviceFeatures features;
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceFeatures(device, &features);
		vkGetPhysicalDeviceProperties(device, &properties);
		std::cout << "Physical device:" << std::endl;
		std::cout << " deviceName: " << properties.deviceName << std::endl;
		std::cout << " driverVersion: " << properties.driverVersion << std::endl;
		std::cout << "Some features:" << std::endl;
		std::cout << " tessellationShader: " << features.tessellationShader << std::endl;
		std::cout << " geometryShader: " << features.geometryShader << std::endl;
		std::cout << " shaderInt16: " << features.shaderInt16 << std::endl;
		std::cout << " shaderInt64: " << features.shaderInt64 << std::endl;
		std::cout << " textureCompressionASTC_LDR: " << features.textureCompressionASTC_LDR << std::endl;
		std::cout << " textureCompressionBC: " << features.textureCompressionBC << std::endl;
		std::cout << " textureCompressionETC2: " << features.textureCompressionETC2 << std::endl;
		std::cout << "Some limits:" << std::endl;
		std::cout << " maxComputeWorkGroupSize: " << properties.limits.maxComputeWorkGroupSize[0] << "x" << properties.limits.maxComputeWorkGroupSize[1] << "x" << properties.limits.maxComputeWorkGroupSize[2] << std::endl << std::endl;
	}
};

// Main entry point
int main()
{
	VulkanTutorial *vulkanTutorial = new VulkanTutorial();
	delete(vulkanTutorial);
	std::cout << std::endl << "Press key to exit...";
	getch();
	return 0;
}