#include "InterfaceMgr.hpp"
#include "Graphics.hpp"

Sexy::InterfaceMgr* Sexy::InterfaceMgr::interface_mgr;

static char* (__fastcall* Sexy__InterfaceMgr__InterfaceMgr_)(Sexy::InterfaceMgr*, char*, Sexy::Board*);
char* __fastcall Sexy__InterfaceMgr__InterfaceMgr(Sexy::InterfaceMgr* this_, char* edx, Sexy::Board* board)
{
	Sexy::InterfaceMgr::interface_mgr = this_;
	return Sexy__InterfaceMgr__InterfaceMgr_(this_, edx, board);
}

static void (__fastcall* Sexy__InterfaceMgr__DrawBack_)(Sexy::InterfaceMgr*, char*, Sexy::Graphics*);
void __fastcall Sexy__InterfaceMgr__DrawBack(Sexy::InterfaceMgr* this_, char* edx, Sexy::Graphics* graphics)
{
	return Sexy__InterfaceMgr__DrawBack_(this_, edx, graphics);
}

static void(__fastcall* Sexy__InterfaceMgr__DrawOnePlayer_)(Sexy::InterfaceMgr*, char*, Sexy::Graphics*);
void __fastcall Sexy__InterfaceMgr__DrawOnePlayer(Sexy::InterfaceMgr* this_, char* edx, Sexy::Graphics* graphics)
{
	return Sexy__InterfaceMgr__DrawOnePlayer_(this_, edx, graphics);
}

void Sexy::InterfaceMgr::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x004515A0, Sexy__InterfaceMgr__InterfaceMgr, (void**)&Sexy__InterfaceMgr__InterfaceMgr_);
			MH_CreateHook((void*)0x00447F60, Sexy__InterfaceMgr__DrawBack, (void**)&Sexy__InterfaceMgr__DrawBack_);
			MH_CreateHook((void*)0x004474B0, Sexy__InterfaceMgr__DrawOnePlayer, (void**)&Sexy__InterfaceMgr__DrawOnePlayer_);
		} break;
	}
}

bool Sexy::InterfaceMgr::check_exists()
{
	if (Sexy::InterfaceMgr::interface_mgr == 0x0) return false;
	return true;
}

Sexy::InterfaceMgr* Sexy::InterfaceMgr::UpdateBalls()
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x00443CF0;
		break;
	}

	if (!Sexy::InterfaceMgr::check_exists() || !address) return 0;
	return reinterpret_cast<Sexy::InterfaceMgr*(__thiscall*)(Sexy::InterfaceMgr*)>(address)(Sexy::InterfaceMgr::interface_mgr);
}

Sexy::InterfaceMgr* Sexy::InterfaceMgr::LoadGun()
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x0043C9B0;
		break;
	}

	if (!Sexy::InterfaceMgr::check_exists() || !address) return 0;
	return reinterpret_cast<Sexy::InterfaceMgr*(__thiscall*)(Sexy::InterfaceMgr*)>(address)(Sexy::InterfaceMgr::interface_mgr);
}

Sexy::InterfaceMgr* Sexy::InterfaceMgr::AddTopBalls(Sexy::InterfaceMgr* input, int count)
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x0045C860;
		break;
	}

	return reinterpret_cast<Sexy::InterfaceMgr*(__thiscall*)(Sexy::InterfaceMgr*, int)>(address)(input, count);
}

Sexy::InterfaceMgr* Sexy::InterfaceMgr::AddTopBalls(int count)
{
	return Sexy::InterfaceMgr::AddTopBalls(Sexy::InterfaceMgr::interface_mgr, count);
}

Sexy::InterfaceMgr* Sexy::InterfaceMgr::SetNumBalls(Sexy::InterfaceMgr* input, int count)
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x00457870;
		break;
	}

	return reinterpret_cast<Sexy::InterfaceMgr * (__thiscall*)(Sexy::InterfaceMgr*, int)>(address)(input, count);
}

Sexy::InterfaceMgr* Sexy::InterfaceMgr::SetNumBalls(int count)
{
	return Sexy::InterfaceMgr::SetNumBalls(Sexy::InterfaceMgr::interface_mgr, count);
}
