#include <Windows.h>
#include <string>


namespace ProCrEncrypter {

	class PCEncrypter
	{
	private:
		std::string encryptionKey = "";
	public:
		PCEncrypter(std::string key);
		void Encrypt(std::string input, std::string& output);
		void Decrypt(std::string input, std::string& output);
	};
}