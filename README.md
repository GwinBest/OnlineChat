# OnlineChat
## How to clone
This repo uses gitmodules, so clone it recursive:
```
git clone --recursive https://github.com/GwinBest/OnlineChat.git
```
## Build Tools
### [CMake](https://cmake.org/download/)
## Database
If you need to run the server, then download the [MySql](https://dev.mysql.com/downloads/installer/)
## Getting Started
First, clone a repository
```
git clone --recursive https://github.com/GwinBest/OnlineChat.git
```
Then, make a build folder
```
cd OnlineChat
mkdir build
cd build
```
Run cmake 
```
cmake ..
```
To build all apps run
```
cmake --build .
```
Or, if you want to specify
```
cmake --build . --target (serverApp | clientApp)
```
# MySQL setup
First, set up the server, after that add your server credentials to environment variables
## Windows(PowerShell)
```
setx CHAT_DB_HOST "your_db_ip:your_db_port"
setx CHAT_DB_USER "your_db_user"
setx CHAT_DB_PASSWORD "your_db_password"
setx CHAT_DB_SCHEMA "your_db_schema"
setx CHAT_SERVER_IP "your_server_ip"
setx CHAT_SERVER_PORT "your_server_port"
```
After that, run the [following code](https://github.com/GwinBest/onlineChat/blob/5d7b133a00e55d44e87736bf6c8b9af14148c8a9/sqlScripts/create.sql) to create all necessary tables 
