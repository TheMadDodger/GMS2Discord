#include "stdafx.h"
#include "DiscordIntegration.h"

DiscordIntegration::DiscordIntegration(const std::string &applicationId, const std::string &steamID) :
	m_ApplicationId(applicationId)
{
	memset(&m_RichPresense, 0, sizeof(m_RichPresense));
}

DiscordIntegration::~DiscordIntegration()
{
	m_Data.clear();
}

void DiscordIntegration::Initialize()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = DiscordIntegration::HandleDiscordReady;
	handlers.errored = DiscordIntegration::HandleDiscordError;
	handlers.disconnected = DiscordIntegration::HandleDiscordDisconnected;
	handlers.joinGame = DiscordIntegration::HandleDiscordJoinGame;
	handlers.spectateGame = DiscordIntegration::HandleDiscordSpectateGame;
	handlers.joinRequest = DiscordIntegration::HandleDiscordJoinRequest;

	for (size_t i = 0; i < MAX_DISCORD_DATA; ++i)
	{
		m_Data.push_back("");
	}

	Discord_Initialize(m_ApplicationId.data(), &handlers, 1, m_SteamID.data());
}

void DiscordIntegration::PreCleanUp()
{
	Discord_Shutdown();
}

void DiscordIntegration::Update()
{
	m_RichPresense.details = m_Data[DiscordData::Details].data();
	m_RichPresense.state = m_Data[DiscordData::State].data();
	m_RichPresense.largeImageKey = m_Data[DiscordData::LargeImageKey].data();
	m_RichPresense.largeImageText = m_Data[DiscordData::LargeImageText].data();
	m_RichPresense.smallImageKey = m_Data[DiscordData::SmallImageKey].data();
	m_RichPresense.smallImageText = m_Data[DiscordData::SmallImageText].data();
	Discord_UpdatePresence(&m_RichPresense);
}

void DiscordIntegration::SetData(double key, std::string details)
{
	m_Data[(int unsigned)key] = details;
}

void DiscordIntegration::HandleDiscordReady(const DiscordUser * request)
{
}

void DiscordIntegration::HandleDiscordDisconnected(int errorCode, const char * message)
{
}

void DiscordIntegration::HandleDiscordError(int errorCode, const char * message)
{
}

void DiscordIntegration::HandleDiscordJoinGame(const char * joinSecret)
{
}

void DiscordIntegration::HandleDiscordSpectateGame(const char * spectateSecret)
{
}

void DiscordIntegration::HandleDiscordJoinRequest(const DiscordUser * request)
{
}