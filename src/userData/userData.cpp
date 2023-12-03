#include "UserData.h"

namespace UserData
{	
	void User::PushUserCredentialsToDatabase(const std::string& name, const std::string& login, const size_t password) noexcept
	{
		Network::UserRequest request =
		{
			.actionType = Network::ActionType::kAddUserCredentialsToDatabase,
			.name = name,
			.login = login,
			.password = password
		};

		Network::Client::GetInstance().SendUserCredentials(request);
	}

	std::string User::GetUserNameFromDatabase(const std::string& login, const size_t password) noexcept
	{
		Network::UserRequest request =
		{
			.actionType = Network::ActionType::kGetUserNameFromDatabase,
			.name  = "",
			.login = login,
			.password = password
		};

		Network::Client::GetInstance().SendUserCredentials(request);
		std::string serverResponse = Network::Client::GetInstance().GetServerResponse<std::string>();

		return serverResponse;
	}

	bool User::IsUserExist(const std::string& login, const size_t password) noexcept
	{
		Network::UserRequest request =
		{
			.actionType = Network::ActionType::kCheckUserExistence,
			.name = "",
			.login = login,
			.password = password
		};

		Network::Client::GetInstance().SendUserCredentials(request);
		std::string serverResponse = Network::Client::GetInstance().GetServerResponse<std::string>();
		
		if (serverResponse == "Exist")
		{
			return true;
		}

		return false;
	}

	std::vector<UserData::User*> User::FindUsersByLogin(std::string& userLogin)
	{
		Network::UserRequest request =
		{
			.actionType = Network::ActionType::kFindUsersByLogin,
			.login = userLogin
		};

		Network::Client::GetInstance().SendUserCredentials(request);
		std::vector<UserData::User*> response = Network::Client::GetInstance().GetServerResponse<std::vector<UserData::User*>>();

		return response;
	}

	std::string User::GetUserName() const noexcept
	{
		return _userName;
	}

	std::string User::GetUserLogin() const noexcept
	{
		return _userLogin;
	}

	size_t User::GetUserPassword() const noexcept
	{
		return _userPassword;
	}

	void User::SetUserName(const std::string& name) noexcept
	{
		_userName = name;
	}

	void User::SetUserLogin(const std::string& login) noexcept
	{
		_userLogin = login;
	}

	void User::SetUserPassword(const size_t password) noexcept
	{
		_userPassword = password;
	}

} // !namespace UserData