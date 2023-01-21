#include "BindSystem.h"
#include <Windows.h>


void BSystem::addNewBind(void* bindableObject, BSystem::bindTypes bindType, BSystem::valueTypes valueType, BSystem::nValuee nVal, int bindButton) {
	BSystem::SBind sb;

	sb.emulator = bindableObject;

	sb.bindButton = bindButton;

	sb.bindType = bindType;
	sb.valueType = valueType;

	sb.defValue._bool = nVal._bool;
	sb.defValue._float = nVal._float;
	sb.defValue._int = nVal._int;
	sb.defValue._string = nVal._string;

	sb.newValue = nVal;

	BSystem::Binds.push_back(sb);
}

void BSystem::runBindSystem() {
	for (auto item : BSystem::Binds)
	{
		if (item.bindType == BSystem::TOGGLE)
		{
			if (GetAsyncKeyState(item.bindButton) & 1)
			{
				switch (item.valueType)
				{

				case BSystem::BOOL:
					if (*(bool*)item.emulator == (bool)item.newValue._bool)
					{
						*(bool*)item.emulator = item.defValue._bool;
						MessageBoxA(0, std::to_string(item.defValue._bool).c_str(), "", 0);
					}
					else
					{
						MessageBoxA(0, std::to_string(*(bool*)item.emulator).c_str(), "", 0);
						item.defValue._bool = *(bool*)item.emulator;
						*(bool*)item.emulator = (bool)item.newValue._bool;
					}
					break;

				case BSystem::INT:
					if (*(int*)item.emulator == (int)item.newValue._int)
						*(int*)item.emulator = (int)item.defValue._int;
					else
					{
						item.defValue._int = *(int*)item.emulator;
						*(int*)item.emulator = (int)item.newValue._int;
					}

				case BSystem::FLOAT:
					if (*(float*)item.emulator == (float)item.newValue._float)
						*(float*)item.emulator = (float)item.defValue._float;
					else
					{
						item.defValue._float = *(float*)item.emulator;
						*(float*)item.emulator = (float)item.newValue._float;
					}
					break;

				case BSystem::STRING:
					if (*(std::string*)item.emulator == (std::string)item.newValue._string)
						*(std::string*)item.emulator = (std::string)item.defValue._string;
					else
					{
						(std::string)item.defValue._string = *(std::string*)item.emulator;
						*(std::string*)item.emulator = (std::string)item.newValue._string;
					}
					break;


				default:
					break;
				}
			}
		}
		else {
			if (GetAsyncKeyState(item.bindButton) != 0)
			{
				switch (item.valueType)
				{

				case BSystem::BOOL:
					item.defValue._bool = *(bool*)item.emulator;
					*(bool*)item.emulator = (bool)item.newValue._bool;
					break;

				case BSystem::INT:
					item.defValue._int = *(int*)item.emulator;
					*(int*)item.emulator = (int)item.newValue._int;
					break;

				case BSystem::FLOAT:
					item.defValue._float = *(float*)item.emulator;
					*(float*)item.emulator = (float)item.newValue._float;
					break;

				case BSystem::STRING:
					item.defValue._string = *(std::string*)item.emulator;
					*(std::string*)item.emulator = (std::string)item.newValue._string;
					break;


				default:
					break;
				}
			}
			else {
				switch (item.valueType)
				{

				case BSystem::BOOL:
					*(bool*)item.emulator = (bool)item.defValue._bool;
					break;

				case BSystem::INT:
					*(int*)item.emulator = (int)item.defValue._int;
					break;

				case BSystem::FLOAT:
					*(float*)item.emulator = (float)item.defValue._float;
					break;

				case BSystem::STRING:
					*(std::string*)item.emulator = (std::string)item.defValue._string;
					break;


				default:
					break;
				}
			}
		}

	}
}