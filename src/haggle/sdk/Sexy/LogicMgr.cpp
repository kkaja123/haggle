#include "LogicMgr.hpp"
#include "utils/memory.hpp"
#include "callbacks/callbacks.hpp"

Sexy::LogicMgr* Sexy::LogicMgr::logic_mgr;

static char* (__fastcall* Sexy__LogicMgr__LogicMgr_)(Sexy::LogicMgr*, char*, char*);
char* __fastcall Sexy__LogicMgr__LogicMgr(Sexy::LogicMgr* this_, char* edx, char* thunderball)
{
	Sexy::LogicMgr::logic_mgr = this_;
	return Sexy__LogicMgr__LogicMgr_(this_, edx, thunderball);
}

static void(__fastcall* Sexy__LogicMgr__DoPowerup_)(Sexy::LogicMgr*, char*, Sexy::Ball*, Sexy::PhysObj*, int, int);
void __fastcall Sexy__LogicMgr__DoPowerup(Sexy::LogicMgr* this_, char* edx, Sexy::Ball* a2, Sexy::PhysObj* a3, int powerup, int a5)
{
	return Sexy__LogicMgr__DoPowerup_(this_, edx, a2, a3, powerup, a5);
}

static void(__fastcall* Sexy__LogicMgr__PegHit_)(Sexy::LogicMgr*, char*, Sexy::Ball*, Sexy::PhysObj*, bool);
void __fastcall Sexy__LogicMgr__PegHit(Sexy::LogicMgr* this_, char* edx, Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4)
{
	callbacks::run_peg_hit_callbacks(ball, phys_obj, a4);
	Sexy__LogicMgr__PegHit_(this_, edx, ball, phys_obj, a4);
	callbacks::run_after_peg_hit_callbacks(ball, phys_obj, a4);
}

static void(__fastcall* Sexy__LogicMgr__BeginShot_)(Sexy::LogicMgr*, char*, bool);
void __fastcall Sexy__LogicMgr__BeginShot(Sexy::LogicMgr* this_, char* edx, bool doGetReplayPoint)
{
	callbacks::run_begin_shot_callbacks(this_, doGetReplayPoint);
	Sexy__LogicMgr__BeginShot_(this_, edx, doGetReplayPoint);
	callbacks::run_after_begin_shot_callbacks(this_, doGetReplayPoint);
}

static char* (__fastcall* Sexy__LogicMgr__BeginTurn2_)(Sexy::LogicMgr*, char*);
char* __fastcall Sexy__LogicMgr__BeginTurn2(Sexy::LogicMgr* this_, char* edx)
{
	callbacks::run_basic_callbacks(callbacks::type::begin_turn_2);
	auto retn = Sexy__LogicMgr__BeginTurn2_(this_, edx);
	callbacks::run_after_begin_turn_2_callbacks(this_);
	return retn;
}

static void (__fastcall* Sexy__LogicMgr__FinishInitLevelText_)(Sexy::LogicMgr*, char*);
void __fastcall Sexy__LogicMgr__FinishInitLevelText(Sexy::LogicMgr* this_, char* edx)
{
	callbacks::run_basic_callbacks(callbacks::type::finish_init_level);
	Sexy__LogicMgr__FinishInitLevelText_(this_, edx);
}

static void(__fastcall* Sexy__LogicMgr__DoLevelDone_)(Sexy::LogicMgr*, char*);
void __fastcall Sexy__LogicMgr__DoLevelDone(Sexy::LogicMgr* this_, char* edx)
{
	callbacks::run_basic_callbacks(callbacks::type::do_level_done);
	Sexy__LogicMgr__DoLevelDone_(this_, edx);
}

static bool(__fastcall* Sexy__LogicMgr__BeatLevel_)(Sexy::LogicMgr*, char*);
bool __fastcall Sexy__LogicMgr__BeatLevel(Sexy::LogicMgr* this_, char* edx)
{
	auto retn = Sexy__LogicMgr__BeatLevel_(this_, edx);

	if (retn) callbacks::run_basic_callbacks(callbacks::type::after_beat_level_true);
	else if (!retn) callbacks::run_basic_callbacks(callbacks::type::after_beat_level_false);

	return retn;
}

void Sexy::LogicMgr::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x004610D0, Sexy__LogicMgr__LogicMgr, (void**)&Sexy__LogicMgr__LogicMgr_);
			MH_CreateHook((void*)0x0046EDF0, Sexy__LogicMgr__DoPowerup, (void**)&Sexy__LogicMgr__DoPowerup_);
			MH_CreateHook((void*)0x0046F480, Sexy__LogicMgr__PegHit, (void**)&Sexy__LogicMgr__PegHit_);
			MH_CreateHook((void*)0x0046AC70, Sexy__LogicMgr__BeginShot, (void**)&Sexy__LogicMgr__BeginShot_);
			MH_CreateHook((void*)0x0044B5B0, Sexy__LogicMgr__BeginTurn2, (void**)&Sexy__LogicMgr__BeginTurn2_);
			MH_CreateHook((void*)0x0046C220, Sexy__LogicMgr__FinishInitLevelText, (void**)&Sexy__LogicMgr__FinishInitLevelText_);
			MH_CreateHook((void*)0x0046A9C0, Sexy__LogicMgr__DoLevelDone, (void**)&Sexy__LogicMgr__DoLevelDone_);
			MH_CreateHook((void*)0x0043D530, Sexy__LogicMgr__BeatLevel, (void**)&Sexy__LogicMgr__BeatLevel_);
		} break;

		case PeggleVersion::NightsDeluxe10:
		{
			MH_CreateHook((void*)0x00466C30, Sexy__LogicMgr__LogicMgr, (void**)&Sexy__LogicMgr__LogicMgr_);
			MH_CreateHook((void*)0x0046E9C0, Sexy__LogicMgr__DoPowerup, (void**)&Sexy__LogicMgr__DoPowerup_);
			MH_CreateHook((void*)0x004701B0, Sexy__LogicMgr__PegHit, (void**)&Sexy__LogicMgr__PegHit_);

			MH_CreateHook((void*)0x0046C230, Sexy__LogicMgr__BeginShot, (void**)&Sexy__LogicMgr__BeginShot_);
			MH_CreateHook((void*)0x0046B950, Sexy__LogicMgr__BeginTurn2, (void**)&Sexy__LogicMgr__BeginTurn2_);
			//MH_CreateHook((void*)0x0046C220, Sexy__LogicMgr__FinishInitLevelText, (void**)&Sexy__LogicMgr__FinishInitLevelText_);
			MH_CreateHook((void*)0x0046BE60, Sexy__LogicMgr__DoLevelDone, (void**)&Sexy__LogicMgr__DoLevelDone_);
			MH_CreateHook((void*)0x0046BA90, Sexy__LogicMgr__BeatLevel, (void**)&Sexy__LogicMgr__BeatLevel_);

		} break;
	}
}

bool Sexy::LogicMgr::check_exists()
{
	if (logic_mgr != nullptr)
	{
		return true;
	}

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			int* checkPtr = reinterpret_cast<int*>(0x00687394);  // ThunderballApp pointer (static)
			if (reinterpret_cast<int*>(*checkPtr) == nullptr)
			{
				logic_mgr = nullptr;
				return false;
			}

			checkPtr = reinterpret_cast<int*>(*checkPtr + 0x7B8);  // Board pointer (dynamic)
			if (reinterpret_cast<int*>(*checkPtr) == nullptr)
			{
				logic_mgr = nullptr;
				return false;
			}

			checkPtr = reinterpret_cast<int*>(*checkPtr + 0x154);  // LogicMgr pointer (dynamic)
			if (reinterpret_cast<int*>(*checkPtr) == nullptr)
			{
				logic_mgr = nullptr;
				return false;
			}
		} break;
	}

	return TryPointerRefresh();  // The static LogicMgr pointer was null, but it looks like the LogicMgr exists in the game memory. Try to retrieve it.
}

bool Sexy::LogicMgr::TryPointerRefresh()
{
	int* checkPtr = nullptr;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			checkPtr = reinterpret_cast<int*>(0x00687394);  // ThunderballApp pointer (static)
			if (reinterpret_cast<int*>(*checkPtr) == nullptr)
			{
				logic_mgr = nullptr;
				return false;
			}

			checkPtr = reinterpret_cast<int*>(*checkPtr + 0x7B8);  // Board pointer (dynamic)
			if (reinterpret_cast<int*>(*checkPtr) == nullptr)
			{
				logic_mgr = nullptr;
				return false;
			}

			checkPtr = reinterpret_cast<int*>(*checkPtr + 0x154);  // LogicMgr pointer (dynamic)
			if (reinterpret_cast<int*>(*checkPtr) == nullptr)
			{
				logic_mgr = nullptr;
				return false;
			}
		} break;
	}

	if (!checkPtr) return false;
	logic_mgr = reinterpret_cast<LogicMgr*>(*checkPtr);
	return logic_mgr != 0;
}

Sexy::LogicMgr* Sexy::LogicMgr::IncNumBalls(int top_count, int bottom_count, bool bottom)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x0045D880;
		} break;
	}

	if (!check_exists() || !address) return 0;
	return reinterpret_cast<LogicMgr * (__thiscall*)(LogicMgr*, int, int, bool)>(address)
		(Sexy::LogicMgr::logic_mgr, top_count, bottom_count, bottom);
}

int Sexy::LogicMgr::BeginShot(bool doGetReplayPoint)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x0046AC70;
		} break;
	}

	if (!check_exists() || !address) return 0;
	return reinterpret_cast<int(__thiscall*)(LogicMgr*, bool)>(address)(logic_mgr, doGetReplayPoint);
}

void Sexy::LogicMgr::MouseDown(int xPos, int yPos, int mouseButtonId, bool b1, bool b2)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x00472810;
		} break;
	}

	if (!check_exists() || !address) return;
	return reinterpret_cast<void(__thiscall*)(LogicMgr*, int, int, int, bool, bool)>(address)(logic_mgr, xPos, yPos, mouseButtonId, b1, b2);
}

void Sexy::LogicMgr::DoPowerup(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, int powerup, int a5)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x0046EDF0;
		} break;

		case PeggleVersion::NightsDeluxe10:
		{
			address = 0x0046E9C0;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, Sexy::Ball*, Sexy::PhysObj*, int, int)>(address)
		(logic_mgr, ball, phys_obj, powerup, a5);
}

void Sexy::LogicMgr::ActivateFreeBallCover(int a2)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x00440700;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, int)>(address)(logic_mgr, a2);
}

void Sexy::LogicMgr::ActivatePowerup(int powerup, int a3)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x004612E0;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, int, int)>(address)(logic_mgr, powerup, a3);
}

std::int64_t Sexy::LogicMgr::DoMultiball(Sexy::Ball* a2, Sexy::PhysObj* a3)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x0046EAD0;
		} break;
	}

	if (!check_exists() || !address) return 0;
	return reinterpret_cast<std::int64_t(__thiscall*)(LogicMgr*, Sexy::Ball*, Sexy::PhysObj*)>(address)(logic_mgr, a2, a3);
}

void Sexy::LogicMgr::PegHit(Sexy::Ball* ball, Sexy::PhysObj* phys_obj, bool a4)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x0046F480;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<std::int64_t(__thiscall*)(LogicMgr*, Sexy::Ball*, Sexy::PhysObj*, bool)>(address)
		(logic_mgr, ball, phys_obj, a4);
}

Sexy::FloatingText* Sexy::LogicMgr::AddStandardText(std::string& string, float x_pos, float y_pos, int type)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x00469EB0;
		} break;

		case PeggleVersion::NightsDeluxe10:
		{
			address = 0x00468DD0;
		} break;
	}

	if (!check_exists() || !address) return 0;
	return reinterpret_cast<Sexy::FloatingText * (__thiscall*)(LogicMgr*, std::string&, float, float, int)>(address)
		(logic_mgr, string, x_pos, y_pos, type);
}

Sexy::FloatingText* Sexy::LogicMgr::AddStandardText(const char* string, float pos_x, float pos_y, int type)
{
	return Sexy::LogicMgr::AddStandardText(std::string(string), pos_x, pos_y, type);
}

void Sexy::LogicMgr::DoExploder(Sexy::Ball* ball, Sexy::PhysObj* phys_obj)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x0045E330;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, Sexy::Ball*, Sexy::PhysObj*)>(address)(logic_mgr, ball, phys_obj);
}

bool Sexy::LogicMgr::BeginTurn2()
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x0044B5B0;
		} break;

		case PeggleVersion::NightsDeluxe10:
		{
			address = 0x0046B950;
		} break;
	}

	if (!check_exists() || !address) return false;
	return reinterpret_cast<bool(__thiscall*)(LogicMgr*)>(address)(logic_mgr);
}

void Sexy::LogicMgr::ActivateFreeBall(bool a4)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x00440580;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, bool)>(address)(logic_mgr, a4);
}

void Sexy::LogicMgr::SetWearHat(int a2)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x0043D4D0;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, int)>(address)(logic_mgr, a2);
}

void Sexy::LogicMgr::SetState(State newState)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x00436FB0;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<int(__thiscall*)(LogicMgr*, State)>(address)(logic_mgr, newState);
}

Sexy::LogicMgr::State Sexy::LogicMgr::GetState(void)
{
	if (!check_exists()) return State::None;

	int* logicState = reinterpret_cast<int*>(logic_mgr + 0x04);

	if (logicState == nullptr)
	{
		return State::None;
	}

	return static_cast<State>(*logicState);
}

void Sexy::LogicMgr::SetGunAngleRadians(float newAngleRadians)
{
	Sexy::LogicMgr::SetGunAngle(newAngleRadians);
}

void Sexy::LogicMgr::SetGunAngleDegrees(float newAngleDegrees)
{
	Sexy::LogicMgr::SetGunAngle(DegreesToRadians(newAngleDegrees));
}

void Sexy::LogicMgr::SetGunAngle(float newAngleDegrees)
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x00436FD0;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*, float)>(address)(logic_mgr, newAngleDegrees);
}

float Sexy::LogicMgr::GetGunAngleRadians(void)
{
	if (!check_exists()) return 0.0f;

	float* gunAnglePtr = reinterpret_cast<float*>(logic_mgr + 0xE0);

	if (gunAnglePtr == nullptr)
	{
		return 0.0f;
	}

	return *gunAnglePtr;
}

float Sexy::LogicMgr::GetGunAngleDegrees(void)
{
	if (!check_exists()) return 0.0f;

	float* gunAnglePtr = reinterpret_cast<float*>(logic_mgr + 0xE0);

	if (gunAnglePtr == nullptr)
	{
		return 0.0f;
	}

	return RadiansToDegrees(*gunAnglePtr);
}

constexpr float DOWN_ROTATION_DEGREES = 270.0f;
float Sexy::LogicMgr::DegreesToRadians(float angleDegrees)
{
	constexpr double PI = 3.141592653589793238;
	constexpr float DEG_TO_RAD_SCALAR = PI / 180.0f;

	return std::fmodf(DOWN_ROTATION_DEGREES + angleDegrees, 360.0f) * DEG_TO_RAD_SCALAR;
}

float Sexy::LogicMgr::RadiansToDegrees(float angleRadians)
{
	constexpr double PI = 3.141592653589793238;
	constexpr float DEG_TO_RAD_SCALAR = PI / 180.0f;
	constexpr float RAD_TO_DEG_SCALAR = 180.0f / PI;

	return std::fmodf(angleRadians * RAD_TO_DEG_SCALAR + DOWN_ROTATION_DEGREES, 360.0f) - 180.0f;
}

void Sexy::LogicMgr::CalcCornerDisplay()
{
	std::uint32_t address = 0x0;

	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			address = 0x00448370;
		} break;
	}

	if (!check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(LogicMgr*)>(address)(logic_mgr);
}
