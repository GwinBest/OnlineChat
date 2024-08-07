#include "signUpWindow.h"

#include "../utils/loadImage.h"

#include <imgui_internal.h>

namespace Gui
{
	bool SignUpWindow::IsSignUpButtonPressed() noexcept
	{
		if (_isSignUpButtonPressed)
		{
			_isSignUpButtonPressed = false;
			return true;
		}

		return false;
	}

	bool SignUpWindow::IsBackToLoginButtonPressed() noexcept
	{
		if (_isBackToLoginButtonPressed)
		{
			_isBackToLoginButtonPressed = false;
			return true;
		}

		return false;
	}

	const char* SignUpWindow::GetName() noexcept
	{
		return _inputBufferName;
	}

	const char* SignUpWindow::GetLogin() noexcept
	{
		return _inputBufferLogin;

	}

	const std::string& SignUpWindow::GetPassword() noexcept
	{
		return _inputBufferPassword;

	}

	void SignUpWindow::SetShowUserAlreadyExistMessage(const bool state) noexcept
	{
		_showUserAlreadyExistMessage = state;
	}

	void SignUpWindow::DrawGui() noexcept
	{
		
		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_NoTabBar);							// enable docking 

		ImGui::Begin("##signUp window");
		ImGuiStyle& windowStyle = ImGui::GetStyle();
		ImVec4 oldButtonColor = windowStyle.Colors[ImGuiCol_Button];
		windowStyle.Colors[ImGuiCol_Button] = windowStyle.Colors[ImGuiCol_WindowBg];									// set the button color to the same 
																														// as the bg window so that only the arrow is visible

		int32_t backToLoginButtonWidth = 0;																				// loads from loadTextureFromFile
		int32_t backToLoginButtonHeight = 0;																			// loads from loadTextureFromFile
		ImTextureID backToLoginButtonTexture = nullptr;
		loadTextureFromFile(".\\resources\\images\\arrowBack.png",reinterpret_cast<GLuint*>(&backToLoginButtonTexture), &backToLoginButtonWidth, &backToLoginButtonHeight);
		if (ImGui::ImageButton("##back to login", backToLoginButtonTexture, ImVec2(backToLoginButtonWidth, backToLoginButtonHeight)))
		{
			_isBackToLoginButtonPressed = true;
			
			_inputBufferName[0] = '\0';
			_inputBufferLogin[0] = '\0';
			_inputBufferPassword = "";

			_isInputNameEmpty = false;
			_isInputLoginEmpty = false;
			_isInputPasswordEmpty = false;

			_showUserAlreadyExistMessage = false;
		}
		windowStyle.Colors[ImGuiCol_Button] = oldButtonColor;															// reset the button color to default
		
		static const std::string welcomeText = "Welcome to the Online Chat app!";
		const float welcomeTextX = ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(welcomeText.c_str()).x / 2;
		constexpr float welcomeTextY = 100.0f;
		ImGui::SetCursorPos(ImVec2(welcomeTextX, welcomeTextY));
		ImGui::TextDisabled(welcomeText.c_str());

		static const std::string loginText = "Create a new account";
		const float loginTextX = ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize(loginText.c_str()).x / 2;
		ImGui::SetCursorPosX(loginTextX);
		ImGui::Text(loginText.c_str());
		//TODO: gap between text and input text when fullscreen

		static constexpr float inputTextWidth = 300.0f;
		ImVec4 oldInputTextColor = windowStyle.Colors[ImGuiCol_FrameBg];
		ImVec4 inputTextEmptyColor = ImVec4(0.8f, 0.0f, 0.0f, 0.5f);

		if (_isInputNameEmpty)
		{
			windowStyle.Colors[ImGuiCol_FrameBg] = inputTextEmptyColor;
		}
		const float inputNameX = ImGui::GetWindowSize().x / 2 - inputTextWidth / 2;
		const float inputNameY = ImGui::GetWindowSize().y / 2 - welcomeTextY - 50.0f;
		ImGui::SetCursorPos(ImVec2(inputNameX, inputNameY));
		ImGui::PushItemWidth(inputTextWidth);
		ImGui::InputTextWithHint("##input text name", "Name", _inputBufferName, IM_ARRAYSIZE(_inputBufferName));
		ImGui::PopItemWidth();
		windowStyle.Colors[ImGuiCol_FrameBg] = oldInputTextColor;
		
		if (_showUserAlreadyExistMessage)
		{
			ImGui::SetCursorPos(ImVec2(inputNameX, inputNameY - 25));
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "This user already registered!");
		}

		if (_isInputLoginEmpty)
		{
			windowStyle.Colors[ImGuiCol_FrameBg] = inputTextEmptyColor;
		}
		const float inputLoginX = inputNameX;
		const float inputLoginY = inputNameY + 50.0f;
		ImGui::SetCursorPos(ImVec2(inputLoginX, inputLoginY));
		ImGui::PushItemWidth(inputTextWidth);
		ImGui::InputTextWithHint("##input text login", "Login", _inputBufferLogin, IM_ARRAYSIZE(_inputBufferLogin));
		ImGui::PopItemWidth();
		windowStyle.Colors[ImGuiCol_FrameBg] = oldInputTextColor;

		if (_isInputPasswordEmpty)
		{
			windowStyle.Colors[ImGuiCol_FrameBg] = inputTextEmptyColor;
		}
		const float inputPasswordX = inputNameX;
		const float inputPasswordY = inputLoginY + 50.0f;
		ImGui::SetCursorPos(ImVec2(inputPasswordX, inputPasswordY));
		ImGui::PushItemWidth(inputTextWidth);
		ImGui::InputTextWithHint("##input text password", "Password", &_inputBufferPassword, ImGuiInputTextFlags_Password);
		ImGui::PopItemWidth();
		windowStyle.Colors[ImGuiCol_FrameBg] = oldInputTextColor;


		const float singUpButtonX = inputNameX;
		const float signUpButtonY = inputPasswordY + 50.0f;
		ImGui::SetCursorPos(ImVec2(singUpButtonX, signUpButtonY));
		if (ImGui::Button("Create an account", ImVec2(inputTextWidth, 0)))												// 0 means that Y will be default for ImGui
		{
			if (_inputBufferName[0] == '\0')
			{
				_isInputNameEmpty = true;
			}
			else
			{
				_isInputNameEmpty = false;
			}

			if (_inputBufferLogin[0] == '\0')
			{
				_isInputLoginEmpty = true;
			}
			else
			{
				_isInputLoginEmpty = false;
			}

			if (_inputBufferPassword.empty())
			{
				_isInputPasswordEmpty = true;
			}
			else
			{
				_isInputPasswordEmpty = false;
			}

			if (!_isInputNameEmpty && !_isInputLoginEmpty && !_isInputPasswordEmpty)
			{
				_isSignUpButtonPressed = true;

				_showUserAlreadyExistMessage = false;
			}
		}

		ImGui::End();
	}
} // !namespace Gui