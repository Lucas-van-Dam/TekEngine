#define GLM_ENABLE_EXPERIMENTAL

#ifdef TEK_PLATFORM_WINDOWS
#else
	#error TEK engine does not support any other platform other than windows
#endif

#ifdef TEK_ENABLE_ASSERTS
#define TEK_CORE_ASSERT(x, ...) { if(!(x)) {TEK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define TEK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define TEK_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)