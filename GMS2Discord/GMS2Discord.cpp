// GMS2Discord.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DiscordIntegration.h"

DiscordIntegration *discord = nullptr;

GMExport double StartUp()
{
	return 1;
}

GMExport double ShutDown()
{
	if (discord)
	{
		discord->PreCleanUp();
		delete discord;
		discord = nullptr;
	}

	return 1;
}

GMExport double InitializeDiscord(const char *applicationId, const char *steamID)
{
	discord = new DiscordIntegration(applicationId, steamID);
	discord->Initialize();

	discord->SetData(DiscordData::LargeImageKey, "default");

	return 1;
}

GMExport double UpdatePresence()
{
	discord->Update();

	return 1;
}

GMExport double SetDiscordData(double key, const char *details)
{
	discord->SetData(key, details);
	return 1;
}
