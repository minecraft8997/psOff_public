#define _CRT_SECURE_NO_WARNINGS
#include "common.h"
#include "core/imports/imports_runtime.h"
#include "logging.h"
#include "types.h"

#include <cstdlib>
#include <vector>
LOG_DEFINE_MODULE(libSceLibcInternal);

namespace {} // namespace

// ### OBJECTS
extern "C" {
EXPORT auto     __NID(_Stdout)              = stdout;
EXPORT uint32_t __NID(Need_sceLibcInternal) = 1;
}
// - ### OBJECTS

extern "C" {

EXPORT const char* MODULE_NAME = "libSceLibcInternal";

/**
 * @brief std::ios_base::Init::Init
 *
 */
EXPORT SYSV_ABI void __NID(_ZNSt8ios_base4InitC1Ev)() {}

/**
 * @brief std::_Winit::_Winit()
 *
 */
EXPORT SYSV_ABI void __NID(_ZNSt6_WinitC1Ev)() {}

EXPORT SYSV_ABI void __NID(_init_env)() {
  LOG_USE_MODULE(libSceLibcInternal);
  LOG_TRACE(L"todo %S", __FUNCTION__);
}

EXPORT SYSV_ABI int __NID(vprintf)(const char* str, va_list args) {
  LOG_USE_MODULE(libSceLibcInternal);

  std::string format(str);
  LOG_DEBUG(std::wstring(format.begin(), format.end()).c_str(), args);

  return Ok;
}

EXPORT SYSV_ABI int __NID(snprintf)(char* s, size_t n, const char* format, va_list args) {
  return std::snprintf(s, n, format, args);
}

EXPORT SYSV_ABI int __NID(fflush)(FILE* stream) {
  return std::fflush(stream);
}

EXPORT SYSV_ABI void* __NID(memset)(void* s, int c, size_t n) {
  return std::memset(s, c, n);
}

EXPORT SYSV_ABI void* __NID(memcpy)(void* d, void* s, size_t n) {
  return std::memcpy(d, s, n);
}

EXPORT SYSV_ABI void* __NID(memmove)(void* dst, void const* src, size_t n) {
  return std::memmove(dst, src, n);
}

EXPORT SYSV_ABI size_t __NID(strlen)(const char* str) {
  return std::strlen(str);
}

EXPORT SYSV_ABI char* __NID(strncat)(char* dst, const char* src, size_t size) {
  return std::strncat(dst, src, size);
}

EXPORT SYSV_ABI char* __NID(strstr)(char* haystack, const char* needle) {
  return std::strstr(haystack, needle);
}

EXPORT SYSV_ABI int __NID(strncmp)(const char* str1, const char* str2, size_t size) {
  return std::strncmp(str1, str2, size);
}

EXPORT SYSV_ABI int __NID(__cxa_guard_acquire)(uint64_t* guard_object) {
  LOG_USE_MODULE(libSceLibcInternal);
  LOG_ERR(L"todo %S", __FUNCTION__);
  return 0;
}

EXPORT SYSV_ABI int __NID(__cxa_guard_release)(uint64_t* guard_object) {
  LOG_USE_MODULE(libSceLibcInternal);
  LOG_ERR(L"todo %S", __FUNCTION__);
  return 0;
}

EXPORT SYSV_ABI int __NID(__cxa_guard_abort)(uint64_t* guard_object) {
  LOG_USE_MODULE(libSceLibcInternal);
  LOG_ERR(L"todo %S", __FUNCTION__);
  return 0;
}

EXPORT SYSV_ABI int __NID(__cxa_atexit)(void (*func)(void*), void* arg, int moduleId) {
  LOG_USE_MODULE(libSceLibcInternal);
  LOG_TRACE(L"%S", __FUNCTION__);

  accessRuntimeExport()->cxa_add_atexit(
      CxaDestructor {
          .destructor_func   = func,
          .destructor_object = arg,
      },
      moduleId);
  return 0;
}

EXPORT SYSV_ABI void __NID(__cxa_finalize)(int moduleId) {
  LOG_USE_MODULE(libSceLibcInternal);
  LOG_DEBUG(L"%S", __FUNCTION__);

  accessRuntimeExport()->cxa_finalize(moduleId);
}
}
