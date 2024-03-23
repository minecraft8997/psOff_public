#pragma once

#include "utility/utility.h"
#include "types.h"

#include <stdint.h>

enum class ControllerType {
  Keyboard,
  Xinput,
  SDL,
};

enum class ControllerState {
  Unknown,
  Connected,
  Disconnected
};

class IController {
  CLASS_NO_COPY(IController);
  CLASS_NO_MOVE(IController);

  protected:
  ControllerType const m_type;
  ControllerState m_state;
  uint32_t m_userId;
  uint8_t m_connectCount;
  char m_guid[33];
  char m_name[33];

  IController(ControllerType type, uint32_t userid): m_type(type), m_userId(userid) {}

  public:
  virtual ~IController() = default;

  auto getUserID() const { return m_userId; }
  auto getType() const { return m_type; }
  auto getState() const { return m_state; }
  auto getName() const { return m_name; }
  auto getGUID() const { return m_guid; }
  auto getConnectionsCount() const { return m_connectCount; }
  auto isConnected() const { return m_state == ControllerState::Connected; }

  virtual bool reconnect()                                   = 0;
  virtual void close()                                       = 0;
  virtual bool readPadData(ScePadData& data)                 = 0;
  virtual bool setMotion(bool state)                         = 0;
  virtual bool setRumble(const ScePadVibrationParam* pParam) = 0;
  virtual bool setLED(const ScePadColor* pParam)             = 0;
  virtual bool resetLED()                                    = 0;
};
