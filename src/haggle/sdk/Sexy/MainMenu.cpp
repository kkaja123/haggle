#include "callbacks/callbacks.hpp"

Sexy::MainMenu* Sexy::MainMenu::main_menu;

static void (__fastcall* Sexy__MainMenu__MainMenu_)(Sexy::MainMenu*, char*, Sexy::ThunderballApp* thunderball);
void __fastcall Sexy__MainMenu__MainMenu(Sexy::MainMenu* this_, char* edx, Sexy::ThunderballApp* thunderball)
{
	Sexy::MainMenu::main_menu = this_;
	Sexy__MainMenu__MainMenu_(this_, edx, thunderball);
}

static void(__fastcall* Sexy__MainMenu__Update_)(Sexy::MainMenu*, char*);
void __fastcall Sexy__MainMenu__Update(Sexy::MainMenu* this_, char* edx)
{
	Sexy__MainMenu__Update_(this_, edx);
	callbacks::run_after_main_menu_update_callbacks(this_);
}

static void(__fastcall* Sexy__MainMenu__StartGame_)(Sexy::MainMenu*, char*);
void __fastcall Sexy__MainMenu__StartGame(Sexy::MainMenu* this_, char* edx)
{
	Sexy__MainMenu__StartGame_(this_, edx);
	callbacks::run_after_start_game_callbacks(this_);
}

void Sexy::MainMenu::setup()
{
	switch (version)
	{
		case PeggleVersion::Deluxe101:
		{
			MH_CreateHook((void*)0x004A79E0, Sexy__MainMenu__MainMenu, (void**)&Sexy__MainMenu__MainMenu_);
			MH_CreateHook((void*)0x004AF680, Sexy__MainMenu__Update, (void**)&Sexy__MainMenu__Update_);
			MH_CreateHook((void*)0x004A9190, Sexy__MainMenu__StartGame, (void**)&Sexy__MainMenu__StartGame_);
		} break;
	}
}

bool Sexy::MainMenu::check_exists()
{
	if (Sexy::MainMenu::main_menu == 0x0) return false;
	return true;
}

void Sexy::MainMenu::StartGame()
{
	std::uint32_t address;

	switch (version)
	{
	case PeggleVersion::Deluxe101:
		address = 0x004A9190;
		break;
	}

	if (!Sexy::MainMenu::check_exists() || !address) return;
	reinterpret_cast<void(__thiscall*)(Sexy::MainMenu*)>(address)(Sexy::MainMenu::main_menu);
}
