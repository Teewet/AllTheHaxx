#include "../menus.h"

#include <engine/textrender.h>

void CMenus::RenderSettingsGeneral(CUIRect MainView)
{
	CALLSTACK_ADD();

	CUIRect Label, Button, Left, Right, Game, Client, AutoReconnect;
	MainView.HSplitTop(180.0f, &Game, &Client);
	Client.HSplitTop(160.0f, &Client, &AutoReconnect);

	// game
	{
		// headline
		Game.HSplitTop(30.0f, &Label, &Game);
		UI()->DoLabelScaled(&Label, Localize("Game"), 20.0f, -1);
		Game.Margin(5.0f, &Game);
		Game.VSplitMid(&Left, &Right);
		Left.VSplitRight(5.0f, &Left, 0);
		Right.VMargin(5.0f, &Right);

		// dynamic camera
		Left.HSplitTop(20.0f, &Button, &Left);
		static CButtonContainer s_DynamicCameraButton;
		if(DoButton_CheckBox(&s_DynamicCameraButton, Localize("Dynamic Camera"), g_Config.m_ClMouseDeadzone != 0, &Button))
		{
			if(g_Config.m_ClMouseDeadzone)
			{
				g_Config.m_ClMouseFollowfactor = 0;
				g_Config.m_ClMouseMaxDistance = 400;
				g_Config.m_ClMouseDeadzone = 0;
			}
			else
			{
				g_Config.m_ClMouseFollowfactor = 60;
				g_Config.m_ClMouseMaxDistance = 1000;
				g_Config.m_ClMouseDeadzone = 300;
			}
		}

		// weapon pickup
		Left.HSplitTop(5.0f, 0, &Left);
		Left.HSplitTop(20.0f, &Button, &Left);
		static CButtonContainer s_CheckboxAutoswitchWeapons;
		if(DoButton_CheckBox(&s_CheckboxAutoswitchWeapons, Localize("Switch weapon on pickup"), g_Config.m_ClAutoswitchWeapons, &Button))
			g_Config.m_ClAutoswitchWeapons ^= 1;

		// weapon out of ammo autoswitch
		Left.HSplitTop(5.0f, 0, &Left);
		Left.HSplitTop(20.0f, &Button, &Left);
		static CButtonContainer s_CheckboxAutoswitchWeaponsOutOfAmmo;
		if(DoButton_CheckBox(&s_CheckboxAutoswitchWeaponsOutOfAmmo, Localize("Switch weapon when out of ammo"), g_Config.m_ClAutoswitchWeaponsOutOfAmmo, &Button))
			g_Config.m_ClAutoswitchWeaponsOutOfAmmo ^= 1;

		// weapon reset on death
		Left.HSplitTop(5.0f, 0, &Left);
		Left.HSplitTop(20.0f, &Button, &Left);
		static CButtonContainer s_CheckboxResetWantedWeaponOnDeath;
		if(DoButton_CheckBox(&s_CheckboxResetWantedWeaponOnDeath, Localize("Reset wanted weapon on death"), g_Config.m_ClResetWantedWeaponOnDeath, &Button))
			g_Config.m_ClResetWantedWeaponOnDeath ^= 1;

	}

	// client
	{
		// headline
		Client.HSplitTop(65.0f, &Label, &Client);	//changed due to Show other ATH user
		UI()->DoLabelScaled(&Label, Localize("Client"), 20.0f, -1);
		Client.Margin(5.0f, &Client);
		Client.VSplitMid(&Left, &Right);
		Left.VSplitRight(5.0f, &Left, 0);
		Right.VMargin(5.0f, &Right);

		// auto demo settings
		{
			Left.HSplitTop(20.0f, &Button, &Left);
			static CButtonContainer s_CheckboxAutoDemoRecord;
			if(DoButton_CheckBox(&s_CheckboxAutoDemoRecord, Localize("Automatically record demos"), g_Config.m_ClAutoDemoRecord, &Button))
				g_Config.m_ClAutoDemoRecord ^= 1;

			Right.HSplitTop(20.0f, &Button, &Right);
			static CButtonContainer s_CheckboxAutoScreenshot;
			if(DoButton_CheckBox(&s_CheckboxAutoScreenshot, Localize("Automatically take game over screenshot"), g_Config.m_ClAutoScreenshot, &Button))
				g_Config.m_ClAutoScreenshot ^= 1;

			Left.HSplitTop(10.0f, 0, &Left);
			Left.HSplitTop(20.0f, &Label, &Left);
			Button.VSplitRight(20.0f, &Button, 0);
			char aBuf[64];
			if(g_Config.m_ClAutoDemoMax)
				str_format(aBuf, sizeof(aBuf), "%s: %i", Localize("Max demos"), g_Config.m_ClAutoDemoMax);
			else
				str_format(aBuf, sizeof(aBuf), "%s: %s", Localize("Max demos"), Localize("no limit"));
			UI()->DoLabelScaled(&Label, aBuf, 13.0f, -1);
			Left.HSplitTop(20.0f, &Button, 0);
			Button.HMargin(2.0f, &Button);
			static CButtonContainer s_ScrollbarAutoDemoMax;
			g_Config.m_ClAutoDemoMax = static_cast<int>(DoScrollbarH(&s_ScrollbarAutoDemoMax, &Button, g_Config.m_ClAutoDemoMax/1000.0f)*1000.0f+0.1f);

			Right.HSplitTop(10.0f, 0, &Right);
			Right.HSplitTop(20.0f, &Label, &Right);
			Button.VSplitRight(20.0f, &Button, 0);
			if(g_Config.m_ClAutoScreenshotMax)
				str_format(aBuf, sizeof(aBuf), "%s: %i", Localize("Max Screenshots"), g_Config.m_ClAutoScreenshotMax);
			else
				str_format(aBuf, sizeof(aBuf), "%s: %s", Localize("Max Screenshots"), Localize("no limit"));
			UI()->DoLabelScaled(&Label, aBuf, 13.0f, -1);
			Right.HSplitTop(20.0f, &Button, 0);
			Button.HMargin(2.0f, &Button);
			static CButtonContainer s_ScrollbarAutoScreenshotMax;
			g_Config.m_ClAutoScreenshotMax = static_cast<int>(DoScrollbarH(&s_ScrollbarAutoScreenshotMax, &Button, g_Config.m_ClAutoScreenshotMax/1000.0f)*1000.0f+0.1f);
		}

		Left.HSplitTop(20.0f, 0, &Left);
		Left.HSplitTop(20.0f, &Label, &Left);
		Button.VSplitRight(20.0f, &Button, 0);
		char aBuf[64];
		if(g_Config.m_ClCpuThrottle)
			str_format(aBuf, sizeof(aBuf), "%s: %i", Localize("CPU Throttle"), g_Config.m_ClCpuThrottle);
		else
		{
			str_format(aBuf, sizeof(aBuf), "%s: %s", Localize("CPU Throttle"), Localize("none"));
			TextRender()->TextColor(0.8f, 0.1f, 0.1f, 1.0f);
		}
		UI()->DoLabelScaled(&Label, aBuf, 13.0f, -1);
		TextRender()->TextColor(1,1,1,1);
		Left.HSplitTop(20.0f, &Button, 0);
		Button.HMargin(2.0f, &Button);
		static CButtonContainer s_ScrollbarCpuThrottle;
		g_Config.m_ClCpuThrottle = round_to_int(
				DoScrollbarH(&s_ScrollbarCpuThrottle, &Button, g_Config.m_ClCpuThrottle/100.0f,
							 "Makes the client use less CPU; too high values result in stuttering\n\n"
									 "WARNING: Setting this to 'none' will rape your CPU like crazy! Recommended value is 1"
				)*100.0f+0.1f);

		{
			CUIRect Checkbox;
			static CButtonContainer s_CheckboxPID[2];
			Left.HSplitTop(20.0f, 0, &Left);
			Left.HSplitTop(20.0f, &Label, &Left);
			Button.VSplitRight(20.0f, &Button, 0);
			str_format(aBuf, sizeof(aBuf), "%s: %i", Localize("Reconnect when server is full"), g_Config.m_ClReconnectFull);
			UI()->DoLabelScaled(&Label, aBuf, 13.0f, -1);
			Left.HSplitTop(20.0f, &Button, 0);
			Button.HMargin(2.0f, &Button);
			Button.VSplitLeft(Button.h, &Checkbox, &Button);
			if(DoButton_CheckBox(&s_CheckboxPID[0], "", g_Config.m_ClReconnectFull, &Checkbox))
				g_Config.m_ClReconnectFull = g_Config.m_ClReconnectFull ? 0 : 5;
			Button.VSplitLeft(Button.h/2, 0, &Button);
			static CButtonContainer s_ScrollbarReconnectFull;
			if(g_Config.m_ClReconnectFull)
				g_Config.m_ClReconnectFull = max(5, round_to_int(DoScrollbarH(&s_ScrollbarReconnectFull, &Button, g_Config.m_ClReconnectFull/180.0f)*180.0f));

			Left.HSplitTop(20.0f, 0, &Left);
			Left.HSplitTop(20.0f, &Label, &Left);
			Button.VSplitRight(20.0f, &Button, 0);
			str_format(aBuf, sizeof(aBuf), "%s: %i", Localize("Reconnect on connection timeout"), g_Config.m_ClReconnectTimeout);
			UI()->DoLabelScaled(&Label, aBuf, 13.0f, -1);
			Left.HSplitTop(20.0f, &Button, 0);
			Button.HMargin(2.0f, &Button);
			Button.VSplitLeft(Button.h, &Checkbox, &Button);
			if(DoButton_CheckBox(&s_CheckboxPID[1], "", g_Config.m_ClReconnectTimeout, &Checkbox))
				g_Config.m_ClReconnectTimeout = g_Config.m_ClReconnectTimeout ? 0 : 10;
			Button.VSplitLeft(Button.h/2, 0, &Button);
			static CButtonContainer s_ScrollbarReconnectTimeout;
			if(g_Config.m_ClReconnectTimeout)
				g_Config.m_ClReconnectTimeout = max(5, round_to_int(DoScrollbarH(&s_ScrollbarReconnectTimeout, &Button, g_Config.m_ClReconnectTimeout/180.0f)*180.0f));
		}

#if defined(CONF_FAMILY_WINDOWS)
		Left.HSplitTop(20.0f, 0, &Left);
		Left.HSplitTop(20.0f, &Button, &Left);
		CButtonContainer s_HideConsoleButton;
		if(DoButton_CheckBox(&s_HideConsoleButton, Localize("Hide console window"), g_Config.m_ClHideConsole, &Button))
			g_Config.m_ClHideConsole ^= 1;
#endif

		// auto statboard screenshot
		{
			Right.HSplitTop(20.0f, 0, &Right); //
			Right.HSplitTop(20.0f, 0, &Right); // Make some distance so it looks more natural
			Right.HSplitTop(20.0f, &Button, &Right);
			static CButtonContainer s_CheckboxAutoStatboardScreenshot;
			if(DoButton_CheckBox(&s_CheckboxAutoStatboardScreenshot,
						Localize("Automatically take statboard screenshot"),
						g_Config.m_ClAutoStatboardScreenshot, &Button))
			{
				g_Config.m_ClAutoStatboardScreenshot ^= 1;
			}

			Right.HSplitTop(10.0f, 0, &Right);
			Right.HSplitTop(20.0f, &Label, &Right);
			Button.VSplitRight(20.0f, &Button, 0);
			if(g_Config.m_ClAutoStatboardScreenshotMax)
				str_format(aBuf, sizeof(aBuf), "%s: %i", Localize("Max Screenshots"), g_Config.m_ClAutoStatboardScreenshotMax);
			else
				str_format(aBuf, sizeof(aBuf), "%s: %s", Localize("Max Screenshots"), Localize("no limit"));
			UI()->DoLabelScaled(&Label, aBuf, 13.0f, -1);
			Right.HSplitTop(20.0f, &Button, 0);
			Button.HMargin(2.0f, &Button);
			static CButtonContainer s_CheckboxAutoStatboardScreenshotMax;
			g_Config.m_ClAutoStatboardScreenshotMax =
				static_cast<int>(DoScrollbarH(&s_CheckboxAutoStatboardScreenshotMax,
							&Button,
							g_Config.m_ClAutoStatboardScreenshotMax/1000.0f)*1000.0f+0.1f);
		}
	}
}
