/*
 * Dummy source
 */

#include <r3dVoxel/ILogger.hpp>
#include <r3dVoxel/r3vABI.hpp>

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

R3VAPI void* r3vMalloc(std::size_t size) noexcept
{
	return std::malloc(size);
}

R3VAPI void r3vFree(void* pointer) noexcept
{
	std::free(pointer);
}

R3VAPI std::size_t r3vGetMemoryUsage() noexcept
{
	return 0;
}

R3VAPI std::size_t r3vGetSize(const void*) noexcept
{
	return 0;
}

R3VAPI void test()
{
	r3dVoxel::ILogger* test = r3vGetLogger("test");
	r3dVoxel::IGameEngine* engine = r3vInitialize();

	test->log(r3dVoxel::ELoggingLevel::DEBUG, "engine started at {0}", engine);
	test->log(r3dVoxel::ELoggingLevel::INFO, "Vulkan supported? {0:I}", glfwVulkanSupported());

	unsigned extCount = 0;
	const char** extensions = glfwGetRequiredInstanceExtensions(&extCount);

	test->log(r3dVoxel::ELoggingLevel::DEBUG, "Got {0} extensions available.", extCount);
	for(unsigned i = 0; i < extCount; i++)
		test->log(r3dVoxel::ELoggingLevel::DEBUG, "  #{0}: {1}", i, extensions[i]);

	auto _vkCreateInstance = (PFN_vkCreateInstance)glfwGetInstanceProcAddress(nullptr, "vkCreateInstance");

	VkInstanceCreateInfo ici{};
	ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ici.enabledExtensionCount = extCount;
	ici.ppEnabledExtensionNames = extensions;

	VkInstance instance;
	if(VkResult error = _vkCreateInstance(&ici, nullptr, &instance))
	{
		test->log(r3dVoxel::ELoggingLevel::SEVERE, "vkCreateInstance() failed with {0}", error);
		return;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* win = glfwCreateWindow(800, 600, "test", nullptr, nullptr);

	VkSurfaceKHR surface;
	if(VkResult error = glfwCreateWindowSurface(instance, win, nullptr, &surface))
	{
		test->log(r3dVoxel::ELoggingLevel::SEVERE, "glfwCreateWindowSurface() failed with {0}", error);
		return;
	}

	while(!glfwWindowShouldClose(win))
	{
		glfwPollEvents();
	}

	auto _vkDestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)glfwGetInstanceProcAddress(instance, "vkDestroySurfaceKHR");
	_vkDestroySurfaceKHR(instance, surface, nullptr);
	glfwDestroyWindow(win);
}
