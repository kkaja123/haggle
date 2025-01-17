#include "StageMgr.hpp"

Sexy::StageMgr* Sexy::StageMgr::stage_mgr;

static char* (__fastcall* Sexy__StageMgr__StageMgr_)(Sexy::StageMgr*, char*);
char* __fastcall Sexy__StageMgr__StageMgr(Sexy::StageMgr* this_, char* edx)
{
	Sexy::StageMgr::stage_mgr = this_;
	return Sexy__StageMgr__StageMgr_(this_, edx);
}

void Sexy::StageMgr::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x00461940, Sexy__StageMgr__StageMgr, (void**)&Sexy__StageMgr__StageMgr_);
		} break;
	}
}

bool Sexy::StageMgr::check_exists()
{
	if (Sexy::StageMgr::stage_mgr == 0x0) return false;
	return true;
}

int Sexy::StageMgr::GetRandomLevel(Sexy::StageMgr* stage_mgr, Sexy::PlayerInfo* a2, int* a3, int* a4, bool a5, int a6)
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x004592B0;
		break;
	}

	if (!stage_mgr) return 0;
	return reinterpret_cast<int(__thiscall*)(Sexy::StageMgr*, Sexy::PlayerInfo*, int*, int*, bool, int)>(address)
		(stage_mgr, a2, a3, a4, a5, a6);
}

int Sexy::StageMgr::GetRandomLevel(Sexy::PlayerInfo* a2, int* a3, int* a4, bool a5, int a6)
{
	return Sexy::StageMgr::GetRandomLevel(Sexy::StageMgr::stage_mgr, a2, a3, a4, a5, a6);
}
