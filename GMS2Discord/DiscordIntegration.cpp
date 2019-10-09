#include "stdafx.h"
#include "DiscordIntegration.h"

DiscordIntegration::DiscordIntegration(const std::string &applicationId, const std::string &steamID) : m_pDiscordCore(nullptr), m_CurrentUser(discord::User())
{
	std::istringstream ssAppID(applicationId);
	ssAppID >> m_ApplicationId;

	std::istringstream ssSteamID(steamID);
	ssSteamID >> m_SteamID;
}

DiscordIntegration::~DiscordIntegration()
{
	m_Data.clear();
}

void DiscordIntegration::Initialize()
{
	auto result = discord::Core::Create(m_ApplicationId, DiscordCreateFlags_Default, &m_pDiscordCore);
	if (!m_pDiscordCore) {
		return;
	}

	m_pDiscordCore->UserManager().GetCurrentUser(&m_CurrentUser);

	m_pDiscordCore->UserManager().OnCurrentUserUpdate.Connect([&]() {
		m_pDiscordCore->UserManager().GetCurrentUser(&m_CurrentUser);
		});

	m_pDiscordCore->ActivityManager().RegisterSteam(m_SteamID);

	//discord::Activity activity{};
	//activity.SetDetails("Fruit Tarts");
	//activity.SetState("Pop Snacks");
	//activity.GetAssets().SetSmallImage("the");
	//activity.GetAssets().SetSmallText("i mage");
	//activity.GetAssets().SetLargeImage("the");
	//activity.GetAssets().SetLargeText("u mage");
	//activity.SetType(discord::ActivityType::Playing);
	//m_pDiscordCore->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});


	//DiscordEventHandlers handlers;
	//memset(&handlers, 0, sizeof(handlers));
	//handlers.ready = DiscordIntegration::HandleDiscordReady;
	//handlers.errored = DiscordIntegration::HandleDiscordError;
	//handlers.disconnected = DiscordIntegration::HandleDiscordDisconnected;
	//handlers.joinGame = DiscordIntegration::HandleDiscordJoinGame;
	//handlers.spectateGame = DiscordIntegration::HandleDiscordSpectateGame;
	//handlers.joinRequest = DiscordIntegration::HandleDiscordJoinRequest;

	for (size_t i = 0; i < MAX_DISCORD_DATA; ++i)
	{
		m_Data.push_back("");
	}

	//Discord_Initialize(m_ApplicationId.data(), &handlers, 1, m_SteamID.data());
}

void DiscordIntegration::PreCleanUp()
{
	//Discord_Shutdown();
	delete m_pDiscordCore;
	m_pDiscordCore = nullptr;
}

void DiscordIntegration::Update()
{
	if (!m_pDiscordCore) return;

	ZeroMemory(&m_Activity, sizeof(DiscordActivity));
	m_Activity.SetDetails(m_Data[DiscordData::Details].data());
	m_Activity.SetState(m_Data[DiscordData::State].data());
	m_Activity.GetAssets().SetSmallImage(m_Data[DiscordData::SmallImageKey].data());
	m_Activity.GetAssets().SetSmallText(m_Data[DiscordData::SmallImageText].data());
	m_Activity.GetAssets().SetLargeImage(m_Data[DiscordData::LargeImageKey].data());
	m_Activity.GetAssets().SetLargeText(m_Data[DiscordData::LargeImageText].data());
	m_Activity.SetType(discord::ActivityType::Playing);
	m_pDiscordCore->ActivityManager().UpdateActivity(m_Activity, [](discord::Result result) {});
}

void DiscordIntegration::SetData(double key, std::string details)
{
	m_Data[(int unsigned)key] = details;
}

void DiscordIntegration::RunCallbacks()
{
	if (!m_pDiscordCore) return;
	m_pDiscordCore->RunCallbacks();
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