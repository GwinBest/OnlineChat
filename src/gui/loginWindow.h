#pragma once

#include "../common/common.h"
#include "iImGuiWindow.h"

namespace Gui
{
	class LoginWindow final : public IImGuiWindow
	{
	public:
		LoginWindow() = default;

		static bool IsSignUpLabelPressed() noexcept;
		static bool IsLoginButtonPressed() noexcept;

		static const char* GetLogin() noexcept;
		static const std::string& GetPassword() noexcept;

		static void SetShowUserNotFoundMessage(const bool value) noexcept;

	private:
		void DrawGui() noexcept override;

	private:
		static inline char _inputBufferLogin[Common::userLoginSize] = "";
		static inline std::string _inputBufferPassword;

		static inline bool _isInputLoginEmpty = false;
		static inline bool _isInputPasswordEmpty = false;

		static inline bool _showUserNotFoundMessage = false;

		static inline bool _isLoginButtonPressed = false;
		static inline bool _isSignUpLabelPressed = false;
	};

} // !namespace Gui