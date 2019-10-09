// GMS2Discord.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DiscordIntegration.h"

DiscordIntegration *discordIntegration = nullptr;

GMExport double StartUp()
{
	return 1;
}

GMExport double ShutDown()
{
	if (discordIntegration)
	{
		discordIntegration->PreCleanUp();
		delete discordIntegration;
		discordIntegration = nullptr;
	}

	return 1;
}

GMExport double InitializeDiscord(const char *applicationId, const char *steamID)
{
	discordIntegration = new DiscordIntegration(applicationId, steamID);
	discordIntegration->Initialize();

	discordIntegration->SetData(DiscordData::LargeImageKey, "default");

	return 1;
}

GMExport double UpdatePresence()
{
	discordIntegration->Update();
	return 1;
}

GMExport double SetDiscordData(double key, const char *details)
{
	discordIntegration->SetData(key, details);
	return 1;
}

GMExport double RunCallbacks()
{
	discordIntegration->RunCallbacks();
	return 1;
}