#include <string>
#include <vector>

namespace BSystem {
	enum bindTypes {
		HOLD,
		TOGGLE,
	};

	enum valueTypes {
		INT,
		FLOAT,
		BOOL,
		STRING
	};


	struct dValuee {
		int _int;
		float _float;
		bool _bool;
		std::string _string;
	};

	struct nValuee {
		int _int;
		float _float;
		bool _bool;
		std::string _string;
	};

	struct SBind {
		void* emulator;

		dValuee defValue;
		nValuee newValue;

		int bindButton = 0x0;

		bindTypes bindType;
		valueTypes valueType;
	};

	inline std::vector<SBind> Binds;

	void runBindSystem();
	void addNewBind(void* bindableObject, BSystem::bindTypes bindType, BSystem::valueTypes valueType, BSystem::nValuee nVal, int bindButton);
}